/*
    module  : symbol.c
    version : 1.27
    date    : 06/21/22
*/
#include "joy.h"

typedef struct Entry {
    char *name, *arity, is_builtin, is_used;
    value_t value;
} Entry;

static vector(Entry) *symtab; /* symbol table */

KHASH_MAP_INIT_STR(Sym, int); /* index in symbol table */

static khash_t(Sym) *theTable; /* name -> index */

KHASH_MAP_INIT_INT64(Prim, int); /* index in symbol table */

static khash_t(Prim) *primTab; /* address -> index */

/*
    symtabmax - return the current maximum size of the symbol table.
*/
int symtabmax(void)
{
    return vec_max(symtab);
}

/*
    symtabindex - return the current fill size of the symbol table.
*/
int symtabindex(void)
{
    return vec_size(symtab);
}

/*
    locate - return the value in the symbol table at the given location.
*/
value_t locate(int location)
{
    Entry ent;

    ent = vec_at(symtab, location);
    return ent.value;
}

/*
    str_locate - return the name of the symbol at the given location.
*/
const char *str_locate(int location)
{
    Entry ent;

    ent = vec_at(symtab, location);
    return ent.name;
}

/*
    get_location - return the location in the symbol table where a name can be
                   found. If the name was not found, 0 is returned. This is a
                   valid location, but the name there is never searched.
*/
int get_location(const char *name)
{
    int rv;
    khiter_t key;

    if ((key = kh_get(Sym, theTable, name)) != kh_end(theTable))
        return kh_value(theTable, key);
    return 0;
}

/*
    set_inuse - mark a builtin name as used. Used in case.c - name used is
                equal.
*/
void set_inuse(const char *str)
{
    Entry *ent;
    int location;

    if ((location = get_location(str)) != 0) {
        ent = &vec_at(symtab, location);
        if (ent->is_builtin)
            ent->is_used = 1;
    }
}

/*
    lookup - return the value assigned to a name.
*/
value_t lookup(const char *str, int *location)
{
    Entry ent;
    value_t value;

    MK_INITIAL(value);
    if ((*location = get_location(str)) != 0) {
        ent = vec_at(symtab, *location);
        value = ent.value;
    }
    return value;
}

/*
    is_builtin - tell whether a name is that of a builtin function. Also set
                 the is_used flag to 1.
*/
int is_builtin(const char *str)
{
    Entry *ent;
    int location;

    if (!strcmp(str, "stop"))
        return 1;
    if ((location = get_location(str)) != 0) {
        ent = &vec_at(symtab, location);
        ent->is_used = 1;
        return ent->is_builtin;
    }
    return 0;
}

/*
    enter - enter the name of a builtin with its procedure in the symbol table.
            The names come from optable.c, genrec.c, treegenrec.c, or treerec.c
            and are static strings, not allocated.
            Also add the builtin in the reverse lookup table. That way, an
            address can be translated to an index in the optable array.
            theTable is the translation from string to address; primTab is the
            translation from address to index in optable.
*/
void enter(char *str, char *arity, void (*proc)(void))
{
    Entry ent;
    khiter_t key;
    int rv, location;

    location = vec_size(symtab);
    ent.name = str;
    ent.arity = arity;
    ent.value = MAKE_ANON_FUNCT(proc);
    ent.is_builtin = 1;
    ent.is_used = 0;
    key = kh_put(Sym, theTable, str, &rv); /* lookup str -> location */
    kh_value(theTable, key) = location;
    key = kh_put(Prim, primTab, (int64_t)proc, &rv); /* find proc -> location */
    kh_value(primTab, key) = location;
    vec_push(symtab, ent);
}

/*
    Initialize the symbol table. Procedures for builtins are read from optable
    and placed in the symbol table. User defined names will be added later.
*/
void initsym(void)
{
    static int init;
    int i;
    char *name;

    if (init)
        return;
    init = 1;
    theTable = kh_init(Sym);
    primTab = kh_init(Prim);
    enter(opername(0), opertype(0), operproc(0));
    for (i = FILE_ + 1; (name = opername(i)) != 0; i++)
        enter(name, opertype(i), operproc(i));
}

/*
    enterdef - enter a name with its definition in the symbol table. The name
               is a user defined symbol and comes from allocated memory.
               The rv value is 1 if this is a new entry; 0 if the entry was
               already there.
*/
void enterdef(char *name, Stack *list)
{
    char *str;
    khiter_t key;
    int rv, location;
    Entry ent, *pent;

    key = kh_put(Sym, theTable, str = classify(name), &rv);
    if (!rv && !list)
        if ((location = get_location(name)) != 0) {
            ent = vec_at(symtab, location);
            if (ent.is_builtin)
                fprintf(stderr, "warning: overwriting inbuilt '%s'\n", name);
        }
    if (rv || !list) {
        location = vec_size(symtab);
        ent.name = str;
        ent.arity = 0;
        MK_INITIAL(ent.value);
        ent.is_builtin = ent.is_used = 0;
        kh_value(theTable, key) = location;
        vec_push(symtab, ent);
    } else if (!rv) {
        location = kh_value(theTable, key);
        pent = &vec_at(symtab, location);
        pent->value = MAKE_LIST(list);
    }
}

/*
    my_strupr - convert the name of an identifier to upper case.
                GC_strdup does not return 0, ever.
*/
static char *my_strupr(const char *str)
{
    int i;
    char *ptr;

    ptr = GC_strdup(str);
    for (i = 0; ptr[i]; i++)
        ptr[i] = toupper(ptr[i]);
    return ptr;
}

/*
    dump - dump the part of the symbol table where builtins are declared and
           also dump preprocessor defines that exclude those builtins that are
           not used.
*/
void dump(int mode)
{
    int i, j;
    Entry ent;
    const char *name;

    for (i = 1, j = vec_size(symtab); i < j; i++) {
        ent = vec_at(symtab, i);
        if (!ent.is_builtin)
            continue;
        name = identifier(ent.name);
        if (!mode && ent.is_used)
            printf("{ do_%s, \"%s\" },", name, ent.name);
        else if (mode && !ent.is_used) {
            name = my_strupr(name);
            printf("#define %s_X\n", name);
            printf("#define %s_C\n", name);
        }
    }
}

/*
    find - return the name of a procedure, or an empty string.
*/
const char *find(void (*proc)(void))
{
    Entry ent;
    khiter_t key;
    int location;

    if ((key = kh_get(Prim, primTab, (int64_t)proc)) != kh_end(primTab)) {
        location = kh_value(primTab, key);
        ent = vec_at(symtab, location);
        return ent.name;
    }
    return "";
}

/*
    get_arity - return the arity of a procedure, or an empty string.
*/
const char *get_arity(void (*proc)(void))
{
    Entry ent;
    int location;
    khiter_t key;

    if ((key = kh_get(Prim, primTab, (int64_t)proc)) != kh_end(primTab)) {
        location = kh_value(primTab, key);
        ent = vec_at(symtab, location);
        return ent.arity;
    }
    return "";
}

/*
    dump_help - iterate over the symbol table, returning names.
*/
const char *dump_help(int start, long *k)
{
    khiter_t key;

    if (start)
        key = kh_begin(theTable);
    else
        key = *k + 1;
    while (key != kh_end(theTable)) {
        if (kh_exist(theTable, key)) {
            *k = key;
            return kh_key(theTable, key);
        }
        key++;
    }
    *k = 0;
    return 0;
}

/*
    dump_table - dump the symbol table, the part of user-defined symbols.
*/
void dump_table(void)
{
    int i, j;
    Entry ent;
    char *ptr;

    for (i = 1, j = vec_size(symtab); i < j; i++) {
        ent = vec_at(symtab, i);
        if (ent.is_builtin)
            continue;
        printf("%s == ", ent.name);
        writeterm((Stack *)GET_AS_LIST(ent.value), -1);
        putchar('\n');
    }
}

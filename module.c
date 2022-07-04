/*
    module  : module.c
    version : 1.21
    date    : 06/21/22
*/
#include "joy.h"

/*
 * hide stack of private sections. The sections are numbered, while keeping the
 * string presentation instead of the number itself.
 */
static char *hide_stack[DISPLAYMAX];

static int hide_index = -1;
static unsigned char inside_hide;

typedef struct module_t {
    char *name; /* name of module */
    int hide;
} module_t;

/*
 * stack of module names and hide numbers. Only one module is active.
 */
static module_t module_stack[DISPLAYMAX];

static int module_index = -1;

/*
 * initmod registers str as module name. Modules within modules are supported.
 * Up to a certain extent, that is.
 */
void initmod(char *str)
{
    if (++module_index >= DISPLAYMAX) {
        module_index = DISPLAYMAX - 1;
        execerror("index", "display");
    }
    module_stack[module_index].name = str;
    module_stack[module_index].hide = hide_index;
}

/*
 * initpriv starts a new local section. Local sections within local sections
 * are supported. Private sections are numbered consecutively. If a module is
 * active then the hide_index is registered in the module. The variable
 * inside_hide tells whether defined names should be registered as private.
 * This is done by the function classify and used in the function enterdef.
 */
void initpriv(void)
{
    static int hide_count;
    char str[MAXNUM];

    if (++hide_index >= DISPLAYMAX) {
        hide_index = DISPLAYMAX - 1;
        execerror("index", "display");
    }
    sprintf(str, "%d", ++hide_count);
    hide_stack[hide_index] = GC_strdup(str);
    inside_hide = 1;
}

/*
 * stoppriv registers the transition from private to public definitions. Names
 * should no longer be prefixed with the name of the private section.
 */
void stoppriv(void)
{
    inside_hide = 0;
}

/*
 * exitpriv lowers the hide_index after reading the public section.
 */
void exitpriv(void)
{
    if (hide_index >= 0)
        hide_index--;
}

/*
 * exitmod deregisters a module. It also ends an outstanding private section.
 */
void exitmod(void)
{
    if (module_index >= 0)
        module_index--;
}

/*
 * classify prepends a name with private section or module name, whichever
 * comes first. Names are stored in the symbol table together with this prefix,
 * allowing the same names to be used in different private sections and modules.
 * The symbol table is flat, in the sense that it has no hierarchy. For that
 * reason names must be made unique with this prefix. For public names it is
 * sufficient that they are preceded by the module name; for private names it
 * is ok to have the private number as a prefix.
 */
char *classify(char *name)
{
    size_t leng;
    char *buf = 0, *str;

    /*
     * inside a private section, names that are to be entered in the symbol
     * table should get the hide number as a prefix.
     */
    if (inside_hide)
        buf = hide_stack[hide_index];
    /*
     * inside a module, public names that are to be entered in the symbol table
     * should get the module name as a prefix. That is also the name used when
     * accessing the symbol.
     */
    else if (module_index >= 0)
        buf = module_stack[module_index].name;
    /*
     * buf, when filled, contains either a module identifier, or a number
     * string.
     */
    if (buf) {
        leng = strlen(buf) + strlen(name) + 2;
        str = GC_malloc_atomic(leng);
        sprintf(str, "%s.%s", buf, name);
    } else
        str = GC_strdup(name);
    /*
     * str will contain either the unadorned name, or a classified name.
     */
    return str;
}

/*
 * qualify does the reverse of classify. A name can be given in full, by
 * prefixing the name with a module, but this only needs to be done outside a
 * module, and only one module name needs to be given. For private sections it
 * is different. If there is a private section active, then the name needs to
 * be searched there and if a module is active then the name needs to be
 * searched there as well. The return value is the result of lookup, or the
 * full name in case the lookup was unsuccesful.
 */
value_t qualify(char *name)
{
    value_t rv;
    size_t leng;
    char *buf, *str;
    int index, limit, location;

    /*
     * if the name has a prefix, it is already a fully qualified name and can be
     * searched in the symbol table right away. The prefix can only be a module
     * name. If the name is not found, there is an error. This is already
     * handled by the lookup function.
     */
    if (strchr(name, '.')) {
        if ((location = get_location(name)) != 0)
            return MAKE_USR_INDEX(location);
        return MAKE_USR_STRING(name);
    }
    /*
     * the hide stack is searched, trying each of the hidden sections. The
     * return value from lookup is returned. This will be a definition.
     */
    if (hide_index >= 0) {
        if (module_index >= 0)
            limit = module_stack[module_index].hide;
        else
            limit = -1;
        for (index = hide_index; index > limit; index--) {
            buf = hide_stack[index];
            leng = strlen(buf) + strlen(name) + 2;
            str = GC_malloc_atomic(leng);
            sprintf(str, "%s.%s", buf, name);
            if ((location = get_location(str)) != 0)
                return MAKE_USR_INDEX(location);
        }
    }
    /*
     * if the name can not be found in the local tables, it should be searched
     * in the currently active module, if there is one.
     */
    if (module_index >= 0) {
        buf = module_stack[module_index].name;
        leng = strlen(buf) + strlen(name) + 2;
        str = GC_malloc_atomic(leng);
        sprintf(str, "%s.%s", buf, name);
        if ((location = get_location(str)) != 0)
            return MAKE_USR_INDEX(location);
    }
    /*
     * if the name is not fully classified, cannot be found in the local tables
     * and also not in the module, it needs to be searched as is. If not found,
     * it is not an error, but simply an undefined name.
     */
    rv = lookup(name, &location);
    if (location)
        return IS_ANON_FUNCT(rv) ? rv : MAKE_USR_INDEX(location);
    return MAKE_USR_STRING(name);
}

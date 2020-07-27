/*
    module  : compile.c
    version : 1.2
    date    : 01/20/20
*/
static FILE *program;

KHASH_MAP_INIT_STR(Decl, char);

/* table with declared symbols */
static khash_t(Decl) *declTab;

typedef struct Node {
    int seqnr, print;
    Stack *node;
} Node;

/* declare vector type */
typedef vector(Node) NodeList;

/* declare node list */
static NodeList *theList;

void printvalue(FILE *fp, intptr_t Value);

void init_decl(void)
{
    declTab = kh_init(Decl);
}

char *identifier(const char *str)
{
    int i;
    char *ptr;

    switch (*str) {
    case '+' : return "add";
    case '*' : return "mul";
    case '-' : return "sub";
    case '/' : return "divide";
    case '=' : return "eql";
    case '<' : if (str[1] == '=')
		   return "leql";
	       return "less";
    case '>' : if (str[1] == '=')
		   return "geql";
	       return "greater";
    case '!' : if (str[1] == '=')
		   return "neql";
	       break;
    case '.' : switch (str[1]) {
	       case '+' : return "fadd";
	       case '*' : return "fmul";
	       case '-' : return "fsub";
	       case '/' : return "fdiv";
	       case '<' : return "fless";
	       case '>' : return "fgreater";
	       default  : return "stop";
	       }
	       break;
    }
    ptr = (char *)str;
    if (strchr(ptr, '-') || strchr(ptr, '.')) {
	ptr = GC_strdup(ptr);
	for (i = 0; ptr[i]; i++)
	    if (ptr[i] == '-' || ptr[i] == '.')
		ptr[i] = '_';
    }
    return ptr;
}

int FindNode(Stack *node)
{
    static int seqnr;
    int i;
    Node cur;

    for (i = vec_size(theList) - 1; i >= 0; i--) {
	cur = vec_at(theList, i);
	if (vec_equal(node, cur.node))
	    return cur.seqnr;
    }
    cur.seqnr = ++seqnr;
    cur.print = 0;
    cur.node = node;
    vec_push(theList, cur);
    printf("void do_list_%d(void);", seqnr);
    return seqnr;
}

unsigned StringLeng(const char *str)
{
    unsigned i;

    for (i = 2; *str; i++, str++)
	if (strchr("\"'\\", *str) || (*str >= 8 && *str <= 13))
	    i++;
	else if (iscntrl((int) *str))
	    i += 3;
    return i;
}

void StringPrint(char *ptr, const char *str)
{
    for ( ; *str; str++)
	if (strchr("\"'\\", *str) || (*str >= 8 && *str <= 13)) {
	    *ptr++ = '\\';
	    switch (*str) {
	    case '"' :
	    case '\'' :
	    case '\\' :
		*ptr++ = *str;
		break;
	    case 8 :
		*ptr++ = 'b';
		break;
	    case 9 :
		*ptr++ = 't';
		break;
	    case 10 :
		*ptr++ = 'n';
		break;
	    case 11 :
		*ptr++ = 'v';
		break;
	    case 12 :
		*ptr++ = 'f';
		break;
	    case 13 :
		*ptr++ = 'r';
		break;
	    }
	} else if (iscntrl((int) *str)) {
	    sprintf(ptr, "\\%03o", *str);
	    ptr += 4;
	} else
	    *ptr++ = *str;
    *ptr = 0;
}

char *PrintString(const char *str)
{
    char *ptr;
    unsigned leng;

    leng = StringLeng(str);
    ptr = GC_malloc_atomic(leng + 1);
    StringPrint(ptr, str);
    return ptr;
}

void printlist(FILE *fp, Stack *List, int seqnr)
{
    char *ptr;
    int i, j, rv;
    khiter_t key;
    intptr_t Value;
    const char *Name;

    fprintf(fp, "void do_list_%d(void)", seqnr);
    fprintf(fp, "{ static Stack *List = 0; if (!List) {");
    for (i = 0, j = vec_size(List); i < j; i++) {
	Value = vec_at(List, i);
	if (Value >= MIN_INT && Value <= MAX_INT)
	    fprintf(fp, "vec_push(List, %" PRIdPTR ");", Value);
	else if ((Value & JLAP_INVALID) == 0) {
	    if ((Value & JLAP_PACKAGE) == 0) {
		fprintf(fp, "do_list_%d();", FindNode((Stack *)Value));
		fprintf(fp, "vec_push(List, do_pop());");
	    } else
		fprintf(fp, "vec_push(List, pack(%g));", unpack(Value));
	} else {
	    Name = (const char *)(Value & ~JLAP_INVALID);
	    if (*Name == '"') {
		ptr = PrintString(Name + 1);
		if (*ptr)
		    fprintf(fp, "vec_push(List, (intptr_t)\"%s\");", ptr);
		else
		    fprintf(fp, "vec_push(List, 0);");
	    } else if ((Value = lookup(Name)) == 0)
		fprintf(fp, "vec_push(List, (intptr_t)\"%s\");", Name);
	    else {
		if ((Value & JLAP_INVALID) == 0) {
		    key = kh_put(Decl, declTab, Name, &rv);
		    if (rv)
			kh_value(declTab, key) = 0;
		}
		fprintf(fp, "vec_push(List, (intptr_t)do_%s | JLAP_INVALID);",
			identifier(Name));
	    }
	}
    }
    fprintf(fp, "} do_push((intptr_t)List); }");
}

int PrintNode(FILE *fp)
{
    Node *cur;
    int i, changed = 0;

    for (i = vec_size(theList) - 1; i >= 0; i--) {
	cur = &vec_at(theList, i);
	if (cur->print)
	    continue;
	changed = cur->print = 1;
	printlist(fp, cur->node, cur->seqnr);
    }
    return changed;
}

void printlib(FILE *fp)
{
    intptr_t Index, Limit;

    Limit = vec_size(theStack);
    for (Index = 0; Index < Limit; Index++)
	printvalue(fp, vec_at(theStack, Index));
    vec_setsize(theStack, 0);
}

void compilelib(void)
{
    khiter_t key;
    intptr_t Value;
    const char *Name;
    char changed, flag;

    library = 1;
    do {
	changed = PrintNode(program);
	for (key = kh_begin(declTab); key != kh_end(declTab); key++) {
	    if (kh_exist(declTab, key)) {
		if ((flag = kh_value(declTab, key)) == 0) {
		    kh_value(declTab, key) = changed = 1;
		    Name = kh_key(declTab, key);
		    if ((Value = lookup(Name)) != 0) {
			if (Value & ~JLAP_INVALID) {
			    fprintf(program, "void do_%s(void) {",
				    identifier(Name));
			    vec_setsize(theStack, 0);
			    execute((Stack *)Value);
			    printlib(program);
			    fprintf(program, "}");
			}
		    }
		}
	    }
	}
    } while (changed);
}

void exitcompile(void)
{
    int ch;
    khiter_t key;
    const char *Name;

    fprintf(program, "return 0; }");
    compilelib();
    for (key = kh_begin(declTab); key != kh_end(declTab); key++)
	if (kh_exist(declTab, key)) {
	    Name = kh_key(declTab, key);
	    printf("void do_%s(void);", identifier(Name));
	}
    printf("int yyparse(void) {");
    rewind(program);
    while ((ch = fgetc(program)) != EOF)
	putchar(ch);
    fclose(program);
    printf("YYTABLE yytable[] = {");
    for (key = kh_begin(declTab); key != kh_end(declTab); key++)
	if (kh_exist(declTab, key)) {
	    Name = kh_key(declTab, key);
#if 0
	    printf("{ \"%s\", do_%s, \"", Name, identifier(Name));
	    writeterm((Stack *)lookup(Name), -1);
	    printf("\"},");
#else
	    printf("{ \"%s\", do_%s },", Name, identifier(Name));
#endif
	}
    dump();
    printf("{ 0 } };\n");
}

void initcompile(void)
{
    static int init;
    time_t t;

    if (init)
	return;
    init = 1;
    atexit(exitcompile);
    t = time(0);
    printf("/*\n * generated %s */\n", ctime(&t));
    printf("#define RUNTIME\n");
    printf("#include \"builtin.c\"\n");
    program = tmpfile();
}

void printvalue(FILE *fp, intptr_t Value)
{
    int rv;
    char *ptr;
    khiter_t key;
    const char *Name;

    if (Value >= MIN_INT && Value <= MAX_INT)
	fprintf(fp, "do_push(%" PRIdPTR ");", Value);
    else if ((Value & JLAP_INVALID) == 0) {
	if ((Value & JLAP_PACKAGE) == 0)
	    fprintf(fp, "do_list_%d();", FindNode((Stack *)Value));
	else
	    fprintf(fp, "do_push(pack(%g));", unpack(Value));
    } else {
	Name = (const char *)(Value & ~JLAP_INVALID);
	if (*Name == '"') {
	    ptr = PrintString(Name + 1);
	    if (*ptr)
		fprintf(fp, "do_push((intptr_t)\"%s\");", ptr);
	    else
		fprintf(fp, "do_push(0);");
	} else if ((Value = lookup(Name)) == 0)
	    fprintf(fp, "do_push((intptr_t)\"%s\");", Name);
	else {
	    if ((Value & JLAP_INVALID) == 0) {
		key = kh_put(Decl, declTab, Name, &rv);
		if (rv)
		    kh_value(declTab, key) = 0;
	    }
	    fprintf(fp, "do_push((intptr_t)\"%s\");", Name);
	}
    }
}

void print(FILE *fp, const char *str)
{
    intptr_t Index, Limit;

    Limit = vec_size(theStack);
    if (!str)
	Limit--;
    for (Index = 0; Index < Limit; Index++)
	printvalue(fp, vec_at(theStack, Index));
    if (str)
	fprintf(fp, "%s();", str);
    else if (!stack_empty())
	fprintf(fp, "do_push(%" PRIdPTR ");", vec_back(theStack));
    vec_setsize(theStack, 0);
}

void print1(FILE *fp, const char *str)
{
    if (!stack_empty())
	printvalue(fp, do_pop());
    if (str)
	fprintf(fp, "%s();", str);
}

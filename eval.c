/*
    module  : eval.c
    version : 1.1
    date    : 08/30/16
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "memory.h"
#include "parse.h"
#include "node.h"
#include "utstring.h"

#define P(x)		utstring_printf(str, x)
#define Q(x,y)		utstring_printf(str, x, y)
#define R(x,y,z)	utstring_printf(str, x, y, z)
#define S(x,y,z,w)	utstring_printf(str, x, y, z, w)

void evaluate(node_t *cur, UT_string *str);

static UT_string *declhdr, *program, *library;

void initcompile()
{
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n");
    printf("#include <string.h>\n");
    printf("#include \"memory.h\"\n");
    printf("#include \"parse.h\"\n");
    printf("#include \"node.h\"\n\n");
    printf("YYSTYPE yylval;\n\n");
    printf("#ifndef MAXSTK\n");
    printf("#define MAXSTK	300\n");
    printf("#endif\n\n");
    printf("int stkptr;\n");
    printf("node_t stktab[MAXSTK];\n\n");
}

char *scramble(char *str)
{
    int i;

    for (i = 0; str[i]; i++)
	if (!isalnum(str[i]) && str[i] != '_')
	    return "op";
    return str;
}

void compilelib()
{
    int sym;
    short changed;
    UT_string *str;

    do
	for (sym = changed = 0; sym < symptr; sym++)
	    if (!symtab[sym].mark && symtab[sym].uniq) {
		symtab[sym].mark = changed = 1;
		utstring_new(str);
		evaluate(symtab[sym].next, str);
		utstring_printf(declhdr, "void %s_%d(void);\n",
				scramble(symtab[sym].str), symtab[sym].uniq);
		utstring_printf(library, "void %s_%d(void) {\n%s}\n\n",
				scramble(symtab[sym].str), symtab[sym].uniq,
				utstring_body(str));
		utstring_free(str);
	    }
    while (changed);
}

void exitcompile()
{
    utstring_new(declhdr);
    utstring_new(library);
    compilelib();
    initcompile();
    printf("%s\n", utstring_body(declhdr));
    printf("int main() {\n%sreturn 0; }\n\n", utstring_body(program));
    printf("%s", utstring_body(library));
}

/*
    Compile a term - instead of being executed, commands are printed.
*/
void compile(node_t *cur)
{
    static short init;

    if (!init) {
	init = 1;
	atexit(exitcompile);
	utstring_new(program);
    }
    evaluate(cur, program);
    utstring_printf(program, "writestack();\n");
}

/*
    Replace occurrences of i, dip, step if possible.
*/
int eval(node_t *cur)
{
    UT_string *str;
    short changed = 0;

    switch (cur->type) {
    case Symbol:
	switch (cur->num) {
	case I:
	    if (cur->next && cur->next->type == List) {
		changed = 1;
		utstring_new(str);
		P("/* I */\n");
		evaluate(cur->next->ptr, str);
		cur->str = utstring_body(str);
		cur->type = 0;
		cur->next = cur->next->next;
	    }
	    break;
	case DIP:
	    if (cur->next && cur->next->type == List) {
		changed = 1;
		utstring_new(str);
		P("/* DIP */ { node_t temp = stktab[--stkptr];\n");
		evaluate(cur->next->ptr, str);
		P("stktab[stkptr++] = temp; }\n");
		cur->str = utstring_body(str);
		cur->type = 0;
		cur->next = cur->next->next;
	    }
	    break;
	case STEP:
	    if (cur->next && cur->next->type == List) {
		changed = 1;
		utstring_new(str);
		P("/* STEP */ { node_t *tmp;\n");
		P("for (tmp = stktab[--stkptr].ptr; tmp; tmp = tmp->next) {\n");
		P("    stktab[stkptr++] = *tmp;\n");
		evaluate(cur->next->ptr, str);
		P("} }\n");
		cur->str = utstring_body(str);
		cur->type = 0;
		cur->next = cur->next->next;
	    }
	    break;
	}
	break;
    case Defined:
	cur->type = changed = 1;
	cur->next = concat(copy(symtab[cur->index].next), cur->next);
	break;
    }
    return changed;
}

void printterm(node_t *cur, UT_string *str);

/*
    Look for replacements until no more replacements can be done
*/
void evaluate(node_t *root, UT_string *str)
{
    short changed;
    node_t *cur, *prev = 0;

    root = copy(root);
    do {
	for (changed = 0, cur = root; cur; cur = cur->next)
	    changed |= eval(cur);
	for (cur = root; cur; prev = cur, cur = cur->next)
	    if (cur->type == 1) {
		if (cur == root)
		    root = root->next;
		else
		    prev->next = cur->next;
	    }
    } while (changed);
    printterm(reverse(root), str);
}

int length(node_t *cur)
{
    int leng;

    for (leng = 0; cur; cur = cur->next) {
	leng++;
	if (cur->type == List)
	    leng += length(cur->ptr);
    }
    return leng;
}

void printfactor(node_t *cur, int list, int *pindex, UT_string *str)
{
    char *type = 0;
    int index = *pindex;

	/* num/str/fun/ptr, type, index, next */
    switch (cur->type) {
    case Symbol:
	R(" [%d].num=%d,", index, cur->num);
	Q(" [%d].type=Symbol,", index);
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index + 1);
	P("\n");
	*pindex = index + 1;
	break;
    case Defined:
	if (!symtab[cur->index].next) {
	    R(" [%d].str=\"%s\",", index, cur->str);
	    Q(" [%d].type=Defined,", index);
	} else {
	    if (!symtab[cur->index].uniq) {
		static short uniq;
		symtab[cur->index].uniq = ++uniq;
	    }
	    S(" [%d].fun=%s_%d,", index, scramble(cur->str),
		symtab[cur->index].uniq);
	    Q(" [%d].type=Function,", index);
	}
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index + 1);
	P("\n");
	*pindex = index + 1;
	break;
    case Boolean:
	type = "Boolean";
    case Char:
	if (!type)
	    type = "Char";
    case Int:
	if (!type)
	    type = "Int";
	R(" [%d].num=%d,", index, cur->num);
	R(" [%d].type=%s,", index, type);
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index + 1);
	P("\n");
	*pindex = index + 1;
	break;
    case List:
	if (cur->ptr)
	    S(" [%d].ptr=L%d+%d,", index, list, index + 1);
	Q(" [%d].type=List,", index);
	if (cur->next)
	    S(" [%d].next=L%d+%d,", index, list, index + 1 + length(cur->ptr));
	P("\n");
	*pindex = index + 1;
	for (cur = reverse(copy(cur->ptr)); cur; cur = cur->next)
	    printfactor(cur, list, pindex, str);
	break;
    }
}

void printlist(node_t *cur, UT_string *str)
{
    if (!cur)
	P("stktab[stkptr].ptr = 0;\n");
    else {
	static int list;
	int index = 0, leng = length(cur);
	R("static node_t L%d[%d] = {\n", ++list, leng);
	for (cur = reverse(copy(cur)); cur; cur = cur->next)
	    printfactor(cur, list, &index, str);
	P("};\n");
	Q("stktab[stkptr].ptr = L%d;\n", list);
    }
    P("stktab[stkptr++].type = List;\n");
}

void printterm(node_t *cur, UT_string *str)
{
    while (cur) {
	char *type = 0;
	switch (cur->type) {
	case 0:
	    Q("%s", cur->str);
	    break;
	case Symbol:
	    switch (cur->num) {
	    case AND:
		P("/* AND */ stkptr--;\n");
		P("stktab[stkptr-1].num &= stktab[stkptr].num;\n");
		P("stktab[stkptr-1].type = Boolean;\n");
		break;
	    case BODY:
		P("/* BODY */ stktab[stkptr-1].ptr = 0;\n");
		P("stktab[stkptr-1].type = List;\n");
		break;
	    case CONS:
		P("/* CONS */ { stkptr--;\n");
		P("if (stktab[stkptr-1].type == Symbol &&\n");
		P("    stktab[stkptr-1].num == NOTHING)\n");
		P("    stktab[stkptr-1] = stktab[stkptr];\n");
		P("else {\n");
		P("    stktab[stkptr-1].next = stktab[stkptr].ptr;\n");
		P("    stktab[stkptr-1].ptr = alloc(&stktab[stkptr-1]);\n");
		P("    stktab[stkptr-1].type = List;\n");
		P("} }\n");
		break;
	    case DIP:
		P("/* DIP-EXE */ { node_t temp; stkptr -= 2;\n");
		P("temp = stktab[stkptr];\n");
		P("exeterm(stktab[stkptr+1].ptr);\n");
		P("stktab[stkptr++] = temp; }\n");
		break;
	    case DUP:
		P("/* DUP */ stktab[stkptr] = stktab[stkptr-1];\n");
		P("stkptr++;\n");
		break;
	    case GET:
		Q("/* GET */ stktab[stkptr].type = %d;\n", yylex());
		Q("stktab[stkptr++].num = %d;\n", yylval.num);
		break;
	    case I:
		P("/* I-EXE */ exeterm(stktab[--stkptr].ptr);\n");
		break;
	    case INDEX:
		P("/* INDEX */ { node_t *tmp = stktab[--stkptr].ptr;\n");
		P("if (stktab[stkptr-1].num)\n");
		P("    tmp = tmp->next;\n");
		P("stktab[stkptr-1] = *tmp; }\n");
		break;
	    case NOT:
		P("/* NOT */ stktab[stkptr-1].num = !stktab[stkptr-1].num;\n");
		P("stktab[stkptr-1].type = Boolean;\n");
		break;
	    case NOTHING:
		P("/* NOTHING */ stktab[stkptr].num = NOTHING;\n");
		P("stktab[stkptr++].type = Symbol;\n");
		break;
	    case OR:
		P("/* OR */ stkptr--;\n");
		P("stktab[stkptr-1].num |= stktab[stkptr].num;\n");
		P("stktab[stkptr-1].type = Boolean;\n");
		break;
	    case POP:
		P("/* POP */ stkptr--;\n");
		break;
	    case PUT:
		P("/* PUT */ writefactor(&stktab[--stkptr]);\n");
		break;
	    case SAMETYPE:
		P("/* SAMETYPE */ stkptr--;\n");
		P("stktab[stkptr-1].num  = stktab[stkptr-1].type ==\n");
		P("	stktab[stkptr].type;\n");
		P("stktab[stkptr-1].type = Boolean;\n");
		break;
	    case SELECT:
		break;
	    case STACK:
		P("/* STACK */ stktab[stkptr].ptr = stk2lst();\n");
		P("stktab[stkptr++].type = List;\n");
		break;
	    case STEP:
		P("/* STEP-EXE */ { node_t *ptr, *tmp;\n");
		P("ptr = stktab[--stkptr].ptr;\n");
		P("for (tmp = stktab[--stkptr].ptr; tmp; tmp = tmp->next) {\n");
		P("    stktab[stkptr++] = *tmp;\n");
		P("    exeterm(ptr); } }\n");
		break;
	    case SWAP:
		P("/* SWAP */ { node_t temp; temp = stktab[stkptr-2];\n");
		P("stktab[stkptr-2] = stktab[stkptr-1];\n");
		P("stktab[stkptr-1] = temp; }\n");
		break;
	    case UNCONS:
		P("/* UNCONS */ { node_t *tmp;\n");
		P("stktab[stkptr] = stktab[stkptr-1];\n");
		P("if (!stktab[stkptr].ptr) {\n");
		P("    stktab[stkptr-1].num = NOTHING;\n");
		P("    stktab[stkptr-1].type = Symbol;\n");
		P("} else {\n");
		P("    tmp = stktab[stkptr].ptr;\n");
		P("    stktab[stkptr-1] = *tmp;\n");
		P("    stktab[stkptr].ptr = tmp->next;\n");
		P("} }\n");
		P("stkptr++;\n");
		break;
	    case UNSTACK:
		P("/* UNSTACK */ lst2stk(stktab[stkptr-1].ptr);\n");
		break;
	    case '*':
		P("/* * */ stkptr--;\n");
		P("stktab[stkptr-1].num *= stktab[stkptr].num;\n");
		break;
	    case '+':
		P("/* + */ stkptr--;\n");
		P("stktab[stkptr-1].num += stktab[stkptr].num;\n");
		break;
	    case '-':
		P("/* - */ stkptr--;\n");
		P("stktab[stkptr-1].num -= stktab[stkptr].num;\n");
		break;
	    case '/':
		P("/* / */ stkptr--;\n");
		P("stktab[stkptr-1].num /= stktab[stkptr].num;\n");
		break;
	    case '<':
		P("/* < */ stkptr--;\n");
		P("if (stktab[stkptr-1].type == Defined)\n");
		P("    stktab[stkptr-1].num = strcmp(stktab[stkptr-1].str,\n");
		P("	stktab[stkptr].str) < 0;\n");
		P("else\n");
		P("    stktab[stkptr-1].num = stktab[stkptr-1].num <\n");
		P("	stktab[stkptr].num;\n");
		P("stktab[stkptr-1].type = Boolean;\n");
		break;
	    case '=':
		P("/* = */ stkptr--;\n");
		P("stktab[stkptr-1].num  = stktab[stkptr-1].num ==\n");
		P("	stktab[stkptr].num;\n");
		P("stktab[stkptr-1].type = Boolean;\n");
		break;
	    default:
		printf("ERROR");
		break;
	    }
	    break;
	case Defined:
	    break;
	case Boolean:
	    type = "Boolean";
	case Char:
	    if (!type)
		type = "Char";
	case Int:
	    if (!type)
		type = "Int";
	    Q("stktab[stkptr].num = %d;\n", cur->num);
	    Q("stktab[stkptr++].type = %s;\n", type);
	    break;
	case List:
	    printlist(cur->ptr, str);
	    break;
	default:
	    printf("ERROR");
	    break;
	}
	cur = cur->next;
    }
}

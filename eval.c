/*
    module  : eval.c
    version : 1.1
    date    : 10/23/16
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "memory.h"
#include "parse.h"
#include "node.h"

#define D(x)		PrintDouble(str, x)
#define L(x)		PrintLong(str, x)
#define P(x)		PrintString(str, x)

void evaluate(node_t *cur, String *str);

static String *declhdr, *program, *library;

void PrintString(String *str, char *tmp)
{
    while (*tmp) {
	char *ptr = vec_push(str);
	*ptr = *tmp++;
    }
}

void PrintDouble(String *str, double dbl)
{
    char tmp[30];

    sprintf(tmp, "%g", dbl);
    PrintString(str, tmp);
}

void PrintLong(String *str, long_t num)
{
    char tmp[30];

    sprintf(tmp, PRINT_NUM, num);
    PrintString(str, tmp);
}

void initcompile()
{
    time_t t = time(0);
    printf("/*\n * generated %s */\n", ctime(&t));
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n");
    printf("#include <string.h>\n\n");
    printf("#include \"memory.h\"\n");
    printf("#include \"parse.h\"\n");
    printf("#include \"node.h\"\n\n");
    printf("YYSTYPE yylval;\n");
    printf("Stack *theStack;\n");
    printf("Table *theTable;\n\n");
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
    char *ptr;
    node_t *cur;
    String *str;
    int changed;

    do {
	changed = 0;
	int maxsym = vec_size(theTable);
	for (int sym = 0; sym < maxsym; sym++) {
	    cur = vec_index(theTable, sym);
	    if (!cur->mark && cur->uniq) {
		cur->mark = changed = 1;
		vec_init(str);
		evaluate(cur->next, str);
		ptr = vec_push(str);
		*ptr = 0;
		ptr = scramble(cur->str);
		PrintString(declhdr, "void ");
		PrintString(declhdr, ptr);
		PrintString(declhdr, "_");
		PrintLong(declhdr, cur->uniq);
		PrintString(declhdr, "(void);\n");
		PrintString(library, "void ");
		PrintString(library, ptr);
		PrintString(library, "_");
		PrintLong(library, cur->uniq);
		PrintString(library, "(void) {\n");
		PrintString(library, vec_index(str, 0));
		PrintString(library, "}\n\n");
	    }
	}
    } while (changed);
}

void exitcompile()
{
    char *ptr;

    compilelib();
    initcompile();
    ptr = vec_push(declhdr);
    *ptr = 0;
    ptr = vec_push(program);
    *ptr = 0;
    ptr = vec_push(library);
    *ptr = 0;
    printf("%s\n", vec_index(declhdr, 0));
    printf("int main() {\nvec_init(theStack);\n");
    printf("%sreturn 0; }\n\n", vec_index(program, 0));
    printf("%s", vec_index(library, 0));
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
	vec_init(declhdr);
	vec_init(program);
	vec_init(library);
    }
    evaluate(cur, program);
    PrintString(program, "writestack();\n");
}

/*
    Replace occurrences of i, dip, step if possible.
*/
int eval(node_t *cur)
{
#ifdef BENCHMARK
    static short uniq;

    node_t *first, *second, *third, *fourth;
#endif
    char *ptr;
    node_t *tmp;
    String *str;
    int changed = 0;

    switch (cur->type) {
    case Symbol:
	switch (cur->num) {
#ifdef BENCHMARK
	case BINREC:
	    if ((fourth = cur->next) == 0)
		break;
	    if ((third = fourth->next) == 0)
		break;
	    if ((second = third->next) == 0)
		break;
	    if ((first = second->next) == 0)
		break;
	    if (fourth->type != List)
		break;
	    if (third->type != List)
		break;
	    if (second->type != List)
		break;
	    if (first->type != List)
		break;

	    changed = 1;
	    vec_init(str);
	    P("void binrec_");
	    L(++uniq);
	    P("();\nbinrec_");
	    L(uniq);
	    P("();\n");
	    ptr = vec_push(str);
	    *ptr = 0;
	    cur->str = vec_index(str, 0);
	    cur->type = 0;
	    cur->next = first->next;

	    vec_init(str);
	    P("void binrec_");
	    L(uniq);
	    P("()\n{ value_t temp, *top;\n");
	    evaluate(first->ptr, str);
	    P("top = vec_pop(theStack);\n");
	    P("if (top->num) {\n");
	    evaluate(second->ptr, str);
	    P("} else {\n");
	    evaluate(third->ptr, str);
	    P("top = vec_pop(theStack);\n");
	    P("temp = *top;\n");
	    P("binrec_");
	    L(uniq);
	    P("();\ntop = vec_push(theStack);\n");
	    P("*top = temp;\n");
	    P("binrec_");
	    L(uniq);
	    P("();\n");
	    evaluate(fourth->ptr, str);
	    P("} }\n\n");

	    ptr = vec_push(str);
	    *ptr = 0;
	    PrintString(library, vec_index(str, 0));
	    break;
#endif
	case I:
	    if (cur->next && cur->next->type == List) {
		changed = 1;
		vec_init(str);
		P("/* I */\n");
		evaluate(cur->next->ptr, str);
		ptr = vec_push(str);
		*ptr = 0;
		cur->str = vec_index(str, 0);
		cur->type = 0;
		cur->next = cur->next->next;
	    }
	    break;
	case DIP:
	    if (cur->next && cur->next->type == List) {
		changed = 1;
		vec_init(str);
		P("/* DIP */ { value_t temp, *top;\n");
		P("top = vec_pop(theStack);\n");
		P("temp = *top;\n");
		evaluate(cur->next->ptr, str);
		P("top = vec_push(theStack);\n");
		P("*top = temp; }\n");
		ptr = vec_push(str);
		*ptr = 0;
		cur->str = vec_index(str, 0);
		cur->type = 0;
		cur->next = cur->next->next;
	    }
	    break;
	case STEP:
	    if (cur->next && cur->next->type == List) {
		changed = 1;
		vec_init(str);
		P("/* STEP */ { value_t *top; node_t *tmp;\n");
		P("top = vec_pop(theStack);\n");
		P("for (tmp = top->ptr; tmp; tmp = tmp->next) {\n");
		P("top = vec_push(theStack);\n");
		P("memcpy(top, tmp, sizeof(value_t));\n");
		evaluate(cur->next->ptr, str);
		P("} }\n");
		ptr = vec_push(str);
		*ptr = 0;
		cur->str = vec_index(str, 0);
		cur->type = 0;
		cur->next = cur->next->next;
	    }
	    break;
	}
	break;
    case Defined:
	cur->type = changed = 1;
	tmp = vec_index(theTable, cur->index);
	cur->next = concat(copy(tmp->next), cur->next);
	break;
    }
    return changed;
}

void printterm(node_t *cur, String *str);

/*
    Look for replacements until no more replacements can be done
*/
void evaluate(node_t *root, String *str)
{
    int changed;
    node_t *cur;

    root = copy(root);
    do {
	for (changed = 0, cur = root; cur; cur = cur->next)
	    changed |= eval(cur);
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

void printfactor(node_t *cur, int list, int *pindex, String *str)
{
    node_t *tmp;
    char *type = 0;
    int index = *pindex;

    switch (cur->type) {
    case Symbol:
	P("[");
	L(index);
	P("].num=");
	L(cur->num);
	P(",");
	P("[");
	L(index);
	P("].type=Symbol,");
	if (cur->next) {
	    P("[");
	    L(index);
	    P("].next=L");
	    L(list);
	    P("+");
	    L(index + 1);
	    P(",");
	}
	P("\n");
	*pindex = index + 1;
	break;
    case Defined:
	tmp = vec_index(theTable, cur->index);
	if (!tmp->next) {
	    P("[");
	    L(index);
	    P("].str=\"");
	    P(cur->str);
	    P("\",[");
	    L(index);
	    P("].type=Defined,");
	} else {
	    if (!tmp->uniq) {
		static short uniq;
		tmp->uniq = ++uniq;
	    }
	    P("[");
	    L(index);
	    P("].fun=");
	    P(scramble(cur->str));
	    P("_");
	    L(tmp->uniq);
	    P(",[");
	    L(index);
	    P("].type=Function,");
	}
	if (cur->next) {
	    P("[");
	    L(index);
	    P("].next=L");
	    L(list);
	    P("+");
	    L(index + 1);
	    P(",");
	}
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
	P("[");
	L(index);
	P("].num=");
	L(cur->num);
	P(",[");
	L(index);
	P("].type=");
	P(type);
	P(",");
	if (cur->next) {
	    P("[");
	    L(index);
	    P("].next=L");
	    L(list);
	    P("+");
	    L(index + 1);
	    P(",");
	}
	P("\n");
	*pindex = index + 1;
	break;
    case List:
	if (cur->ptr) {
	    P("[");
	    L(index);
	    P("].ptr=L");
	    L(list);
	    P("+");
	    L(index + 1);
	    P(",");
	}
	P("[");
	L(index);
	P("].type=List,");
	if (cur->next) {
	    P("[");
	    L(index);
	    P("].next=L");
	    L(list);
	    P("+");
	    L(index + 1 + length(cur->ptr));
	    P(",");
	}
	P("\n");
	*pindex = index + 1;
	for (cur = reverse(copy(cur->ptr)); cur; cur = cur->next)
	    printfactor(cur, list, pindex, str);
	break;
    }
}

void printlist(node_t *cur, String *str)
{
    P("{ value_t *top; top = vec_push(theStack);\n");
    if (!cur)
	P("top->ptr = 0;\n");
    else {
	static int list;
	int index = 0, leng = length(cur);
	P("static node_t L");
	L(++list);
	P("[");
	L(leng);
	P("] = {\n");
	for (cur = reverse(copy(cur)); cur; cur = cur->next)
	    printfactor(cur, list, &index, str);
	P("};\ntop->ptr = L");
	L(list);
	P(";\n");
    }
    P("top->type = List; }\n");
}

void printterm(node_t *cur, String *str)
{
    while (cur) {
	char *type = 0;
	switch (cur->type) {
	case 0:
	    P(cur->str);
	case 1:
	    break;
	case Symbol:
	    switch (cur->num) {
	    case AND:
		P("/* AND */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num &= top->num;\n");
		P("sub->type = Boolean; }\n");
		break;
	    case BODY:
		P("/* BODY */ { value_t *top;\n");
		P("top = vec_top(theStack);\n");
		P("top->ptr = 0;\n");
		P("top->type = List; }\n");
		break;
	    case CONS:
		P("/* CONS */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("if (sub->type == Symbol && sub->num == NOTHING)\n");
		P("*sub = *top;\n");
		P("else {\n");
		P("sub->ptr = cons(sub, top->ptr);\n");
		P("sub->type = List;\n");
		P("} }\n");
		break;
	    case DIP:
		P("/* DIP-EXE */ { value_t temp, *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_pop(theStack);\n");
		P("temp = *sub;\n");
		P("exeterm(top->ptr);\n");
		P("top = vec_push(theStack);\n");
		P("*top = temp; }\n");
		break;
	    case DUP:
		P("/* DUP */ { value_t *top, *sub;\n");
		P("sub = vec_top(theStack);\n");
		P("top = vec_push(theStack);\n");
		P("*top = *sub; }\n");
		break;
	    case GET:
		P("/* GET */ { value_t *top;\n");
		P("top = vec_push(theStack);\n");
		P("top->type =");
		L(yylex());
		P(";\ntop->num = ");
		L(yylval.num);
		P(";\n }");
		break;
	    case I:
		P("/* I-EXE */ { value_t *top;\n");
		P("top = vec_pop(theStack);\n");
		P("exeterm(top->ptr); }\n");
		break;
	    case INDEX:
		P("/* INDEX */ { value_t *top, *sub; node_t *tmp;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("tmp = top->ptr;\n");
		P("if (sub->num)\n");
		P("tmp = tmp->next;\n");
		P("memcpy(sub, tmp, sizeof(value_t)); }\n");
		break;
	    case NOT:
		P("/* NOT */ { value_t *top;\n");
		P("top = vec_top(theStack);\n");
		P("top->num = !top->num;\n");
		P("top->type = Boolean; }\n");
		break;
	    case NOTHING:
		P("/* NOTHING */ { value_t *top;\n");
		P("top = vec_push(theStack);\n");
		P("top->num = NOTHING; top->type = Symbol; }\n");
		break;
	    case OR:
		P("/* OR */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num |= top->num;\n");
		P("sub->type = Boolean; }\n");
		break;
	    case POP:
		P("/* POP */ (void)vec_pop(theStack);\n");
		break;
	    case PUT:
		P("/* PUT */ { value_t *top;\n");
		P("top = vec_pop(theStack);\n");
		P("writefactor(top); }\n");
		break;
	    case SAMETYPE:
		P("/* SAMETYPE */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num = sub->type == top->type;\n");
		P("sub->type = Boolean; }\n");
		break;
#ifdef BENCHMARK
	    case SMALL:
		P("/* SMALL */ { value_t *top;\n");
		P("top = vec_top(theStack);\n");
		P("top->num = top->num < 2;\n");
		P("top->type = Boolean; }\n");
		break;
	    case PRED:
		P("/* PRED */ { value_t *top;\n");
		P("top = vec_top(theStack);\n");
		P("top->num--; }\n");
		break;
	    case BINREC:
		P("/* BINREC-EXE */ { value_t *deep, *down, *sub, *top;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_pop(theStack);\n");
		P("down = vec_pop(theStack);\n");
		P("deep = vec_pop(theStack);\n");
		P("binrec(deep->ptr, down->ptr, sub->ptr, top->ptr); }\n");
		break;
#endif
	    case SELECT:
		break;
	    case STACK:
		P("/* STACK */ { node_t *tmp; value_t *top;\n");
		P("tmp = stk2lst();\n");
		P("top = vec_push(theStack);\n");
		P("top->ptr = tmp;\n");
		P("top->type = List; }\n");
		break;
	    case STEP:
		P("/* STEP-EXE */ { value_t *top, *sub; node_t *ptr, *tmp;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_pop(theStack);\n");
		P("ptr = top->ptr;\n");
		P("for (tmp = sub->ptr; tmp; tmp = tmp->next) {\n");
		P("top = vec_push(theStack);\n");
		P("memcpy(top, tmp, sizeof(value_t));\n");
		P("exeterm(ptr); } }\n");
		break;
	    case SWAP:
		P("/* SWAP */ { value_t temp, *top, *sub;\n");
		P("top = vec_top(theStack);\n");
		P("sub = vec_subtop(theStack);\n");
		P("temp = *sub;\n");
		P("*sub = *top;\n");
		P("*top = temp; }\n");
		break;
	    case UNCONS:
		P("/* UNCONS */ { value_t *top, *sub; node_t *tmp;\n");
		P("sub = vec_top(theStack);\n");
		P("top = vec_push(theStack);\n");
		P("*top = *sub;\n");
		P("if ((tmp = top->ptr) == 0) {\n");
		P("sub->num = NOTHING;\n");
		P("sub->type = Symbol;\n");
		P("} else {\n");
		P("memcpy(sub, tmp, sizeof(value_t));\n");
		P("top->ptr = tmp->next;\n");
		P("} }\n");
		break;
	    case UNSTACK:
		P("/* UNSTACK */ { value_t *top;\n");
		P("top = vec_top(theStack);\n");
		P("lst2stk(top->ptr); }\n");
		break;
	    case '*':
		P("/* * */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num *= top->num; }\n");
		break;
	    case '+':
		P("/* + */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num += top->num; }\n");
		break;
	    case '-':
		P("/* - */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num -= top->num; }\n");
		break;
	    case '/':
		P("/* / */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num /= top->num; }\n");
		break;
	    case '<':
		P("/* < */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("if (sub->type == Defined)\n");
		P("sub->num = strcmp(sub->str, top->str) < 0;\n");
		P("else\n");
		P("sub->num = sub->num < top->num;\n");
		P("sub->type = Boolean; }\n");
		break;
	    case '=':
		P("/* = */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num = sub->num == top->num;\n");
		P("sub->type = Boolean; }\n");
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
	    P("{ value_t *top;\n");
	    P("top = vec_push(theStack);\n");
	    P("top->num = ");
	    L(cur->num);
	    P(";\ntop->type = ");
	    P(type);
	    P("; }\n");
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

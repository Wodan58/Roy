/*
    module  : eval.c
    version : 1.3
    date    : 12/12/17
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "joygc.h"
#include "parse.h"
#include "node.h"

// #define DEBUG
#define MAXNUM		30

#define D(x)		PrintDouble(str, x)
#define L(x)		PrintLong(str, x)
#define P(x)		PrintString(str, x)

void printstack(String *str);
void printterm(node_t *cur, String *str);

static int uniq;
static String *declhdr, *program, *library, *symbols;

char *lookup(void (*fun)(void))
{
    return "";
}

void PrintString(String *str, char *tmp)
{
    char *ptr;

    while (*tmp) {
	ptr = vec_push(str);
	*ptr = *tmp++;
    }
}

void PrintDouble(String *str, double dbl)
{
    char tmp[MAXNUM];

    sprintf(tmp, "%g", dbl);
    PrintString(str, tmp);
}

void PrintLong(String *str, long_t num)
{
    char tmp[MAXNUM];

    sprintf(tmp, PRINT_NUM, num);
    PrintString(str, tmp);
}

/*
    Start the output file.
*/
void initcompile()
{
    time_t t = time(0);
    printf("/*\n * generated %s */\n", ctime(&t));
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n");
    printf("#include <string.h>\n");
    printf("#include \"joygc.h\"\n");
    printf("#include \"parse.h\"\n");
    printf("#include \"node.h\"\n\n");
    printf("YYSTYPE yylval;\n");
    printf("Stack *theStack;\n\n");
}

/*
    Check that a name consists of alphanumerics or underscore and
    if not, return "op".
*/
char *scramble(char *str)
{
    int i;

    for (i = 0; str[i]; i++)
	if (!isalnum(str[i]) && str[i] != '_')
	    return "op";
    return str;
}

/*
    Compile the library.
*/
void compilelib()
{
    char *ptr;
    node_t *cur;
    String *str;
    int changed, maxsym, sym, first = 1;

    do {
	changed = 0;
	maxsym = vec_size(theTable);
	for (sym = 0; sym < maxsym; sym++) {
	    cur = vec_index(theTable, sym);
	    if (!cur->mark && cur->uniq) {
		cur->mark = changed = 1;
		vec_init(str);
		printterm(cur->next, str);
		ptr = vec_push(str);
		*ptr = 0;
		ptr = scramble(cur->str);
		PrintString(declhdr, "void ");
		PrintString(declhdr, ptr);
		PrintString(declhdr, "_");
		PrintLong(declhdr, cur->uniq);
		PrintString(declhdr, "(void);\n");
		if (first) {
		    first = 0;
		    PrintString(symbols, "struct {\nvoid (*fun)(void);\n");
		    PrintString(symbols, "char *str;\n} funTable[] = {\n");
		}
		PrintString(symbols, "{ ");
		PrintString(symbols, ptr);
		PrintString(symbols, "_");
		PrintLong(symbols, cur->uniq);
		PrintString(symbols, ", \"");
		PrintString(symbols, cur->str);
		PrintString(symbols, "\" },\n");
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
    if (!first) {
	PrintString(symbols, "{ 0, \"\" } };\n\n");
	PrintString(symbols, "char *lookup(void (*fun)(void)) {\nint i;\n");
	PrintString(symbols, "for (i = 0; funTable[i].fun; i++)\n");
	PrintString(symbols, "if (fun == funTable[i].fun) break;\n");
	PrintString(symbols, "return funTable[i].str;\n}\n");
    } else {
	PrintString(symbols, "char *lookup(void (*fun)(void)) {\n");
	PrintString(symbols, "return \"\";\n}\n");
    }
}

/*
    Compile the library, start the output file, terminate the 3 strings and
    print them.
*/
void exitcompile(void)
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
    ptr = vec_push(symbols);
    *ptr = 0;
    ptr = vec_index(declhdr, 0);
    if (*ptr)
	printf("%s\n", ptr);
    ptr = vec_index(symbols, 0);
    printf("%s\n", ptr);
    printf("int main() {\nvec_init(theStack);\n");
    printf("vec_init(theTable);\n%sreturn 0; }\n",
	   vec_index(program, 0));
    ptr = vec_index(library, 0);
    if (*ptr)
	printf("\n%s", ptr);
}

#ifdef DEBUG
void dumpstack()
{
    value_t *top;
    int stk, max_stk;

    max_stk = vec_size(theStack);
    for (stk = 0; stk < max_stk; stk++) {
	top = vec_index(theStack, stk);
	writefactor(top);
	putchar(' ');
    }
}
#endif

/*
    Compile a term - instead of being executed, commands are printed.
*/
void compile(node_t *cur)
{
    static unsigned char init;

    if (!init) {
	init = 1;
	atexit(exitcompile);
	vec_init(declhdr);
	vec_init(program);
	vec_init(library);
	vec_init(symbols);
    }
    printterm(cur, program);
#ifdef DEBUG
    debugging = 1;
    printf("// ");
    dumpstack();
    printf("\n");
    debugging = 0;
#endif
    printstack(program);
    PrintString(program, "writestack();\n");
}

void put_binrec(int ident, node_t *first, node_t *second, node_t *third,
		node_t *fourth)
{
    String *str;

    vec_init(str);
    P("value_t temp, *top;\n");
    printterm(first, str);
    P("top = vec_pop(theStack);\n");
    P("if (top->num) {\n");
    printterm(second, str);
    P("} else {\n");
    printterm(third, str);
    P("top = vec_pop(theStack);\n");
    P("temp = *top;\n");
    P("binrec_");
    L(ident);
    P("();\ntop = vec_push(theStack);\n");
    P("*top = temp;\n");
    P("binrec_");
    L(ident);
    P("();\n");
    printterm(fourth, str);
    P("}");
    PrintString(library, vec_index(str, 0));
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
	P("{.num=");
	L(cur->num);
	P(",.type=Symbol");
	if (cur->next) {
	    P(",.next=L");
	    L(list);
	    P("+");
	    L(index + 1);
	}
	P("},\n");
	*pindex = index + 1;
	break;
    case Defined:
	tmp = vec_index(theTable, cur->index);
	if (!tmp->next) {
	    P("{.str=\"");
	    P(cur->str);
	    P("\",.type=Defined");
	} else {
	    if (!tmp->uniq)
		tmp->uniq = ++uniq;
	    P("{.fun=");
	    P(scramble(cur->str));
	    P("_");
	    L(tmp->uniq);
	    P(",.type=Function");
	}
	if (cur->next) {
	    P(",.next=L");
	    L(list);
	    P("+");
	    L(index + 1);
	}
	P("},\n");
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
	P("{.num=");
	L(cur->num);
	P(",.type=");
	P(type);
	if (cur->next) {
	    P(",.next=L");
	    L(list);
	    P("+");
	    L(index + 1);
	}
	P("},\n");
	*pindex = index + 1;
	break;
    case List:
	P("{");
	if (cur->ptr) {
	    P(".ptr=L");
	    L(list);
	    P("+");
	    L(index + 1);
	    P(",");
	}
	P(".type=List");
	if (cur->next) {
	    P(",.next=L");
	    L(list);
	    P("+");
	    L(index + 1 + length(cur->ptr));
	}
	P("},\n");
	*pindex = index + 1;
	for (cur = cur->ptr; cur; cur = cur->next)
	    printfactor(cur, list, pindex, str);
	break;
    default:
	fprintf(stderr, "ERROR #0\n");
	break;
    }
}

void printlist(node_t *cur, String *str)
{
    static int list;
    int index = 0, leng;

    P("{ value_t *top; top = vec_push(theStack);\n");
    if (!cur)
	P("top->ptr = 0;\n");
    else {
	leng = length(cur);
	P("static node_t L");
	L(++list);
	P("[");
	L(leng);
	P("] = {\n");
	for (; cur; cur = cur->next)
	    printfactor(cur, list, &index, str);
	P("};\ntop->ptr = L");
	L(list);
	P(";\n");
    }
    P("top->type = List; }\n");
}

void printterm(node_t *cur, String *str)
{
    value_t *deep, *down;
    value_t temp, *sub, *top;
    node_t *tmp /* list */,
	   *ptr /* program */;

    while (cur) {
#ifdef DEBUG
	debugging = 1;
	printf("// ");
	dumpstack();
	printf(". ");
	writeterm(cur);
	printf("\n");
	debugging = 0;
#endif
	switch (cur->type) {
	case Symbol:
	    switch (cur->num) {
	    case AND:
		if (vec_size(theStack) >= 2) {
		    top = vec_pop(theStack);
		    sub = vec_top(theStack);
		    sub->num &= top->num;
		    sub->type = Boolean;
		    break;
		}
		printstack(str);
		P("/* AND */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num &= top->num;\n");
		P("sub->type = Boolean; }\n");
		break;
	    case BODY:
		top = vec_top(theStack);
		tmp = vec_index(theTable, top->index);
		top->ptr = tmp->next;
		top->type = List;
		break;
	    case CONS:
		if (vec_size(theStack) >= 2) {
		    top = vec_top(theStack);
		    if (top->type == List) {
			vec_pop(theStack);
			sub = vec_top(theStack);
			if (sub->type == Symbol && sub->num == NOTHING)
			    *sub = *top;
			else {
			    sub->ptr = cons(sub, top->ptr);
			    sub->type = List;
			}
			break;
		    }
		}
		printstack(str);
		P("/* CONS */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("if (sub->type == Symbol && sub->num == NOTHING)\n");
		P("*sub = *top;\n");
		P("else {\n");
		P("sub->ptr = cons(sub, top->ptr);\n");
		P("sub->type = List; } }\n");
		break;
	    case DIP:
		if (vec_size(theStack) >= 2) {
		    top = vec_top(theStack);
		    if (top->type == List) {
			vec_pop(theStack);
			sub = vec_pop(theStack);
			temp = *sub;
			printterm(top->ptr, str);
			top = vec_push(theStack);
			*top = temp;
			break;
		    }
		}
		printstack(str);
		P("/* DIP-2 */ { value_t temp, *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_pop(theStack);\n");
		P("temp = *sub;\n");
		P("exeterm(top->ptr);\n");
		P("top = vec_push(theStack);\n");
		P("*top = temp; }\n");
		break;
	    case DUP:
		if (vec_size(theStack) >= 1) {
		    top = vec_push(theStack);
		    sub = vec_subtop(theStack);
		    *top = *sub;
		    break;
		}
		printstack(str);
		P("/* DUP */ { value_t *top, *sub;\n");
		P("top = vec_push(theStack);\n");
		P("sub = vec_subtop(theStack);\n");
		P("*top = *sub; }\n");
		break;
	    case GET:
		printstack(str);
		P("/* GET */ { value_t *top;\n");
		P("top = vec_push(theStack);\n");
		P("top->type =");
		L(yylex());
		P(";\ntop->num = ");
		L(yylval.num);
		P(";\n }");
		break;
	    case I:
		if (vec_size(theStack) >= 1) {
		    top = vec_top(theStack);
		    if (top->type == List) {
			vec_pop(theStack);
			printterm(top->ptr, str);
			break;
		    }
		}
		printstack(str);
		P("/* I-EXE */ { value_t *top;\n");
		P("top = vec_pop(theStack);\n");
		P("exeterm(top->ptr); }\n");
		break;
	    case INDEX:
		if (vec_size(theStack) >= 2) {
		    top = vec_top(theStack);
		    if (top->type == List) {
			vec_pop(theStack);
			sub = vec_top(theStack);
			tmp = top->ptr;
			if (sub->num)
			    tmp = tmp->next;
			memcpy(sub, tmp, sizeof(value_t));
			break;
		    }
		}
		printstack(str);
		P("/* INDEX */ { value_t *top, *sub; node_t *tmp;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("tmp = top->ptr;\n");
		P("if (sub->num)\n");
		P("tmp = tmp->next;\n");
		P("memcpy(sub, tmp, sizeof(value_t)); }\n");
		break;
	    case NOT:
		if (vec_size(theStack) >= 1) {
		    top = vec_top(theStack);
		    top->num = !top->num;
		    top->type = Boolean;
		    break;
		}
		printstack(str);
		P("/* NOT */ { value_t *top;\n");
		P("top = vec_top(theStack);\n");
		P("top->num = !top->num;\n");
		P("top->type = Boolean; }\n");
		break;
	    case NOTHING:
		top = vec_push(theStack);
		memcpy(top, cur, sizeof(value_t));
		break;
	    case OR:
		if (vec_size(theStack) >= 2) {
		    top = vec_pop(theStack);
		    sub = vec_top(theStack);
		    sub->num |= top->num;
		    sub->type = Boolean;
		    break;
		}
		printstack(str);
		P("/* OR */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num |= top->num;\n");
		P("sub->type = Boolean; }\n");
		break;
	    case POP:
		if (vec_size(theStack) >= 1) {
		    vec_pop(theStack);
		    break;
		}
		printstack(str);
		P("/* POP */ (void)vec_pop(theStack);\n");
		break;
	    case PUT:
		printstack(str);
		P("/* PUT */ { value_t *top;\n");
		P("top = vec_pop(theStack);\n");
		P("writefactor(top); }\n");
		break;
	    case SAMETYPE:
		if (vec_size(theStack) >= 2) {
		    top = vec_pop(theStack);
		    sub = vec_top(theStack);
		    sub->num = sub->type == top->type;
		    sub->type = Boolean;
		    break;
		}
		printstack(str);
		P("/* SAMETYPE */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num = sub->type == top->type;\n");
		P("sub->type = Boolean; }\n");
		break;
	    case SMALL:
		if (vec_size(theStack) >= 1) {
		    top = vec_top(theStack);
		    top->num = top->num < 2;
		    top->type = Boolean;
		    break;
		}
		printstack(str);
		P("/* SMALL */ { value_t *top;\n");
		P("top = vec_top(theStack);\n");
		P("top->num = top->num < 2;\n");
		P("top->type = Boolean; }\n");
		break;
	    case PRED:
		if (vec_size(theStack) >= 1) {
		    top = vec_top(theStack);
		    top->num--;
		    break;
		}
		printstack(str);
		P("/* PRED */ { value_t *top;\n");
		P("top = vec_top(theStack);\n");
		P("top->num--; }\n");
		break;
	    case BINREC:
		if (vec_size(theStack) >= 4) {
		    top = vec_top(theStack);
		    sub = vec_subtop(theStack);
		    down = vec_index(theStack, vec_size(theStack) - 3);
		    deep = vec_index(theStack, vec_size(theStack) - 4);
		    if (top->type == List && sub->type == List &&
			down->type == List && deep->type == List) {
			vec_pop(theStack);
			vec_pop(theStack);
			vec_pop(theStack);
			vec_pop(theStack);
			printstack(str);
			P("binrec_");
			L(++uniq);
			P("();\n");
			PrintString(declhdr, "void binrec_");
			PrintLong(declhdr, uniq);
			PrintString(declhdr, "(void);\n");
			PrintString(library, "void binrec_");
			PrintLong(library, uniq);
			PrintString(library, "(void) {\n");
			put_binrec(uniq, deep->ptr, down->ptr, sub->ptr,
				   top->ptr);
			PrintString(library, "}\n\n");
			break;
		    }
		}
		printstack(str);
		P("/* BINREC-EXE */ { value_t *deep, *down, *sub, *top;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_pop(theStack);\n");
		P("down = vec_pop(theStack);\n");
		P("deep = vec_pop(theStack);\n");
		P("binrec(deep->ptr, down->ptr, sub->ptr, top->ptr); }\n");
		break;
	    case SELECT:
		break;
	    case STACK:
		printstack(str);
		P("/* STACK */ { node_t *tmp; value_t *top;\n");
		P("tmp = stk2lst();\n");
		P("top = vec_push(theStack);\n");
		P("top->ptr = tmp;\n");
		P("top->type = List; }\n");
		break;
	    case STEP:
		if (vec_size(theStack) >= 2) {
		    top = vec_top(theStack);
		    sub = vec_subtop(theStack);
		    if (top->type == List && sub->type == List) {
			vec_pop(theStack);
			vec_pop(theStack);
			ptr = top->ptr;
			for (tmp = sub->ptr; tmp; tmp = tmp->next) {
			    top = vec_push(theStack);
			    memcpy(top, tmp, sizeof(value_t));
			    printterm(ptr, str);
			}
			break;
		    }
		} else if (vec_size(theStack) >= 1) {
		    top = vec_top(theStack);
		    if (top->type == List) {
			vec_pop(theStack);
			ptr = top->ptr;
			P("/* STEP-1 */ { value_t *top, *sub; node_t *tmp;\n");
			P("sub = vec_pop(theStack);\n");
			P("for (tmp = sub->ptr; tmp; tmp = tmp->next) {\n");
			P("top = vec_push(theStack);\n");
			P("memcpy(top, tmp, sizeof(value_t));\n");
			printterm(ptr, str);
			P("} }\n");
			break;
		    }
		}
		printstack(str);
		P("/* STEP-2 */ { value_t *top, *sub; node_t *ptr, *tmp;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_pop(theStack);\n");
		P("ptr = top->ptr;\n");
		P("for (tmp = sub->ptr; tmp; tmp = tmp->next) {\n");
		P("top = vec_push(theStack);\n");
		P("memcpy(top, tmp, sizeof(value_t));\n");
		P("exeterm(ptr);\n");
		P("} }\n");
		break;
	    case SWAP:
		if (vec_size(theStack) >= 2) {
		    top = vec_top(theStack);
		    sub = vec_subtop(theStack);
		    temp = *sub;
		    *sub = *top;
		    *top = temp;
		    break;
		}
		printstack(str);
		P("/* SWAP */ { value_t temp, *top, *sub;\n");
		P("top = vec_top(theStack);\n");
		P("sub = vec_subtop(theStack);\n");
		P("temp = *sub;\n");
		P("*sub = *top;\n");
		P("*top = temp; }\n");
		break;
	    case UNCONS:
		if (vec_size(theStack) >= 1) {
		    sub = vec_top(theStack);
		    if (sub->type == List) {
			top = vec_push(theStack);
			sub = vec_subtop(theStack);
			*top = *sub;
			if ((tmp = top->ptr) == 0) {
			    sub->num = NOTHING;
			    sub->type = Symbol;
			} else {
			    memcpy(sub, tmp, sizeof(value_t));
			    top->ptr = tmp->next;
			}
			break;
		    }
		}
		printstack(str);
		P("/* UNCONS */ { value_t *top, *sub; node_t *tmp;\n");
		P("top = vec_push(theStack);\n");
		P("sub = vec_subtop(theStack);\n");
		P("*top = *sub;\n");
		P("if ((tmp = top->ptr) == 0) {\n");
		P("sub->num = NOTHING;\n");
		P("sub->type = Symbol;\n");
		P("} else {\n");
		P("memcpy(sub, tmp, sizeof(value_t));\n");
		P("top->ptr = tmp->next; } }\n");
		break;
	    case UNSTACK:
		printstack(str);
		P("/* UNSTACK */ { value_t *top;\n");
		P("top = vec_top(theStack);\n");
		P("lst2stk(top->ptr); }\n");
		break;
	    case '*':
		if (vec_size(theStack) >= 2) {
		    top = vec_pop(theStack);
		    sub = vec_top(theStack);
		    sub->num *= top->num;
		    break;
		}
		printstack(str);
		P("/* * */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num *= top->num; }\n");
		break;
	    case '+':
		if (vec_size(theStack) >= 2) {
		    top = vec_pop(theStack);
		    sub = vec_top(theStack);
		    sub->num += top->num;
		    break;
		}
		printstack(str);
		P("/* + */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num += top->num; }\n");
		break;
	    case '-':
		if (vec_size(theStack) >= 2) {
		    top = vec_pop(theStack);
		    sub = vec_top(theStack);
		    sub->num -= top->num;
		    break;
		}
		printstack(str);
		P("/* - */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num -= top->num; }\n");
		break;
	    case '/':
		if (vec_size(theStack) >= 2) {
		    top = vec_pop(theStack);
		    sub = vec_top(theStack);
		    sub->num /= top->num;
		    break;
		}
		printstack(str);
		P("/* / */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num /= top->num; }\n");
		break;
	    case '<':
		if (vec_size(theStack) >= 2) {
		    top = vec_pop(theStack);
		    sub = vec_top(theStack);
		    if (sub->type == Defined)
			sub->num = strcmp(sub->str, top->str) < 0;
		    else
			sub->num = sub->num < top->num;
		    sub->type = Boolean;
		    break;
		}
		printstack(str);
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
		if (vec_size(theStack) >= 2) {
		    top = vec_pop(theStack);
		    sub = vec_top(theStack);
		    sub->num = sub->num == top->num;
		    sub->type = Boolean;
		    break;
		}
		printstack(str);
		P("/* = */ { value_t *top, *sub;\n");
		P("top = vec_pop(theStack);\n");
		P("sub = vec_top(theStack);\n");
		P("sub->num = sub->num == top->num;\n");
		P("sub->type = Boolean; }\n");
		break;
	    default:
		fprintf(stderr, "ERROR #1\n");
		break;
	    }
	    break;
	case Defined:
	    tmp = vec_index(theTable, cur->index);
	    if (tmp->recur) {
		printstack(str);
		if (!tmp->uniq)
		    tmp->uniq = ++uniq;
		P(scramble(cur->str));
		P("_");
		L(tmp->uniq);
		P("();\n");
	    } else {
		tmp->recur = 1;
		printterm(tmp->next, str);
		tmp->recur = 0;
	    }
	    break;
	case Boolean:
	case Char:
	case Int:
	case List:
	    top = vec_push(theStack);
	    memcpy(top, cur, sizeof(value_t));
	    break;
	default:
	    fprintf(stderr, "ERROR #2\n");
	    break;
	}
	cur = cur->next;
    }
}

void printnode(value_t *cur, String *str)
{
    node_t *tmp;
    char *type = 0;

    switch (cur->type) {
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
    case Symbol:
	switch (cur->num) {
	case NOTHING:
	    P("{ value_t *top;\n");
	    P("top = vec_push(theStack);\n");
	    P("top->num = NOTHING;\n");
	    P("top->type = Symbol; }\n");
	    break;
	case DUP:
	    P("{ value_t *top;\n");
	    P("top = vec_push(theStack);\n");
	    P("top->num = DUP;\n");
	    P("top->type = Symbol; }\n");
	    break;
	default:
	    fprintf(stderr, "ERROR #3\n");
	    break;
	}
	break;
    case Defined:
	tmp = vec_index(theTable, cur->index);
	if (!tmp->uniq)
	    tmp->uniq = ++uniq;
	P("{ value_t *top;\n");
	P("top = vec_push(theStack);\n");
	P("top->fun =");
	P(scramble(cur->str));
	P("_");
	L(tmp->uniq);
	P(";\n");
	P("top->type = Function; }\n");
	break;
    default:
	fprintf(stderr, "ERROR #4\n");
	break;
    }
}

void printstack(String *str)
{
    value_t *top;
    int stk, max_stk;

    max_stk = vec_size(theStack);
    for (stk = 0; stk < max_stk; stk++) {
	top = vec_index(theStack, stk);
	printnode(top, str);
    }
    vec_clear(theStack);
}

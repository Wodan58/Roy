/*
 *  module  : ersatz.c
 *  version : 1.8
 *  date    : 05/28/24
 */
#include "globals.h"

extern table_t yytable[];	/* present in generated code */

/*
 * yyin - normally defined in lexr.c
 */
FILE *yyin;

/*
 * inilinebuffer - remember the filename parameter.
 */
void inilinebuffer(pEnv env)
{
    /* compiled programs do not read source code */
}

/*
 * include - read another source file.
 */
int include(pEnv env, char *name)
{
    /* compiled programs do not include source files */
    return 0;
}

void yyerror(pEnv env, char *str)
{
    /* compiled programs do not error on source */
}

void trace(pEnv env, FILE *fp)
{
    /* no trace in compiled programs */
}

/*
 * inisymboltable - initialize the symbol table.
 */
void inisymboltable(pEnv env)
{
    /* compiled programs use an empty symbol table */
    env->hash = symtab_init();
    env->prim = funtab_init();
}

/*
 * cmpname - return the name of an operator, used in Compare.
 */
char *cmpname(pEnv env, proc_t proc)
{
    int i;

    for (i = 0; yytable[i].proc; i++)
	if (yytable[i].proc == proc)
	    return yytable[i].name;
    return "ANON_FUNCT_";
}

/*
 * opername - return the name of an operator, used in writefactor.
 */
char *opername(pEnv env, proc_t proc)
{
    return cmpname(env, proc);
}

/*
 * arity - the compiler should only accept arities that are ok.
 */
int arity(pEnv env, NodeList *quot, int num)
{
    /* compiled programs do not check the arity */
    return 1;	/* arity is ok */
}

/*
 * Execute a program and print the result according to the autoput settings,
 * if there is anything to be printed. This one uses exeterm instead of
 * evaluate.
 */
void execute(pEnv env, NodeList *list)
{
    Node node;

    exeterm(env, list);
    if (pvec_cnt(env->stck)) {
	if (env->autoput == 2)
	    writeterm(env, env->stck, stdout);
	else if (env->autoput == 1) {
	    env->stck = pvec_pop(env->stck, &node);
	    if (node.op == LIST_) {
		putchar('[');
		writeterm(env, node.u.lis, stdout);
		putchar(']');
	    } else
		writefactor(env, node, stdout);
	}
	if (env->autoput)
	    putchar('\n');
    }
}

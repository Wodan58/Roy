/*
 *  module  : ersatz.c
 *  version : 1.3
 *  date    : 09/19/23
 */
#include "globals.h"

extern table_t yytable[]; /* present in generated code */

/*
    yyin - normally defined in lexr.c
*/
FILE *yyin;

/*
    mustinclude - determine whether usrlib.joy needs to be read, from scan.c
*/
unsigned char mustinclude;

/*
    inilinebuffer - remember the filename parameter.
*/
void inilinebuffer(char *str)
{
    /* compiled programs do not read their own source code */
}

/*
    inisymboltable - initialize the symbol table.
*/
void inisymboltable(pEnv env)
{
    /* compiled programs do not use a symbol table */
}

/*
    include - read another source file.
*/
int include(pEnv env, char *name, int error)
{
    /* compiled programs do not include source files */
    return 0;
}

/*
    cmpname - return the name of an operator, used in writefactor and Compare.
*/
PUBLIC char *cmpname(proc_t proc)
{
    int i;

    for (i = 0; yytable[i].proc; i++)
	if (yytable[i].proc == proc)
	    return yytable[i].name;
    return "ANON_FUNCT_";
}

/*
    arity - the compiler should only accept arities that are ok.
*/
PUBLIC int arity(pEnv env, NodeList *quot, int num)
{
    /* compiled programs do not check the arity */
    return 1;	/* arity is ok */
}

/*
    get_char - read a character, first skip spaces.
*/
PUBLIC int get_char(void)
{
    int ch;

    do
	ch = getchar();
    while (isspace(ch));
    return ch;
}

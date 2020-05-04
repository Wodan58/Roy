/*
    module  : factor.c
    version : 1.2
    date    : 01/20/20
*/
#include <stdio.h>
#include "stack.h"
#include "parse.h"
#include "builtin.h"
#include "yylex.h"
#include "module.h"

void do_push(intptr_t Value);		/* stack.c */

intptr_t pack(real_t dbl);		/* builtin.c */

void readterm(int sym);			/* factor.c */

void readfactor(int sym)
{
    intptr_t set = 0;

    switch (sym) {
    case '{' :
	while ((sym = yylex()) != '}')
	    if (sym == CHAR_ || sym == INTEGER_)
		set |= (intptr_t)1 << yylval.num;
	    else
		execerror("numeric", "set");
	do_push(set);
	break;
    case '[' :
	readterm(yylex());
	break;
    case USR_ :
	do_push((intptr_t)qualify(yylval.str));
	break;
    case FLOAT_ :
	yylval.num = pack(yylval.dbl);
	/* continue */
    default :
	do_push(yylval.num);
	break;
    }
}

void readterm(int sym)
{
    Stack *List = 0;

    if (sym != ']') {
	do {
	    readfactor(sym);
	    vec_push(List, do_pop());
	} while ((sym = yylex()) != ']');
	vec_push(List, 0);
	vec_reverse(List);
    }
    do_push((intptr_t)List);
}

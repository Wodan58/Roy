/*
    module  : setecho.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef SETECHO_C
#define SETECHO_C

/**
3020  setecho  :  D	I  ->
Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
void do_setecho(void)
{
#ifdef COMPILING
    value_t temp;

    ONEPARAM;
    NUMERICTYPE;
    temp = stack_pop();
    if (IS_INTEGER(temp))
	setechoflag(GET_AS_INTEGER(temp));
    else if (IS_CHAR(temp))
	setechoflag(GET_AS_CHAR(temp));
    else if (IS_BOOLEAN(temp))
	setechoflag(GET_AS_BOOLEAN(temp));
#endif
}
#endif

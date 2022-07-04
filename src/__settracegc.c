/*
    module  : __settracegc.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef _LOWBAR__LOWBAR_SETTRACEGC_C
#define _LOWBAR__LOWBAR_SETTRACEGC_C

/**
2990  __settracegc  :  D	I  ->
Sets value of flag for tracing garbage collection to I (= 0..2).
*/
void do__lowbar__lowbar_settracegc(void)
{
    value_t temp;

    COMPILE;
    ONEPARAM;
    NUMERICTYPE;
    temp = stack_pop();
    if (IS_INTEGER(temp))
	tracegc = GET_AS_INTEGER(temp);
    else if (IS_CHAR(temp))
	tracegc = GET_AS_CHAR(temp);
    else if (IS_BOOLEAN(temp))
	tracegc = GET_AS_BOOLEAN(temp);
}
#endif

/*
    module  : setautoput.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef SETAUTOPUT_C
#define SETAUTOPUT_C

/**
3000  setautoput  :  D	I  ->
Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
void do_setautoput(void)
{
    value_t temp;

    COMPILE;
    ONEPARAM;
    NUMERICTYPE;
    temp = stack_pop();
    if (IS_INTEGER(temp))
	autoput = GET_AS_INTEGER(temp);
    else if (IS_CHAR(temp))
	autoput = GET_AS_CHAR(temp);
    else if (IS_BOOLEAN(temp))
	autoput = GET_AS_BOOLEAN(temp);
}
#endif

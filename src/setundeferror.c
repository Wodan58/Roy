/*
    module  : setundeferror.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef SETUNDEFERROR_C
#define SETUNDEFERROR_C

/**
3010  setundeferror  :  D	I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
void do_setundeferror(void)
{
    value_t temp;

    ONEPARAM;
    NUMERICTYPE;
    temp = stack_pop();
    if (IS_INTEGER(temp))
	undeferror = GET_AS_INTEGER(temp);
    else if (IS_CHAR(temp))
	undeferror = GET_AS_CHAR(temp);
    else if (IS_BOOLEAN(temp))
	undeferror = GET_AS_BOOLEAN(temp);
}
#endif

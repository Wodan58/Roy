/*
    module  : div.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef DIV_C
#define DIV_C

/**
1430  div  :  DDAA	I J  ->  K L
Integers K and L are the quotient and remainder of dividing I by J.
*/
void do_div(void)
{
    ldiv_t result;

    TWOPARAMS;
    INTEGERS2;
    CHECKZERO;
    result = ldiv(GET_AS_INTEGER(stack[-2]), GET_AS_INTEGER(stack[-1]));
    stack[-2] = MAKE_INTEGER(result.quot);
    stack[-1] = MAKE_INTEGER(result.rem);
}
#endif

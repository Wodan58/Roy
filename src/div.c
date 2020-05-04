/*
    module  : div.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef DIV_C
#define DIV_C

/**
div  :  I J  ->  K L
Integers K and L are the quotient and remainder of dividing I by J.
*/
void do_div(void)
{
    lldiv_t result;

    BINARY;
    result = lldiv(stack[-2], stack[-1]);
    stack[-2] = result.quot;
    stack[-1] = result.rem;
}
#endif

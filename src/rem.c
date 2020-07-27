/*
    module  : rem.c
    version : 1.11
    date    : 07/23/20
*/
#ifndef REM_C
#define REM_C

/**
rem  :  I J  ->  K
Integer K is the remainder of dividing I by J.
*/
void do_rem(void)
{
    BINARY;
    stack[-2] %= stack[-1];
    do_pop();
}
#endif

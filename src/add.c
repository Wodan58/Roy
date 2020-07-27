/*
    module  : add.c
    version : 1.9
    date    : 07/23/20
*/
#ifndef ADD_C
#define ADD_C

/**
+  :  M I  ->  N
Numeric N is the result of adding integer I to numeric M.
*/
void do_add(void)
{
    BINARY;
    stack[-2] += stack[-1];
    do_pop();
    CHECK2;
}
#endif

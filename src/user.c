/*
    module  : user.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef USER_C
#define USER_C

/**
user  :  X  ->  B
Tests whether X is a user-defined symbol.
*/
void do_user(void)
{
    UNARY;
    stack[-1] = is_string(stack[-1]);
}
#endif

/*
    module  : string.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef STRING_C
#define STRING_C

/**
2370  string  :  DA	X  ->  B
Tests whether X is a string.
*/
void do_string(void)
{
    char *str;

    ONEPARAM;
    if (!IS_USR_STRING(stack[-1]))
        stack[-1] = MAKE_BOOLEAN(0);
    else {
        str = GET_AS_USR_STRING(stack[-1]);
        stack[-1] = MAKE_BOOLEAN(*str == '"');
    }
}
#endif

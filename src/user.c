/*
    module  : user.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef USER_C
#define USER_C

/**
2400  user  :  DA	X  ->  B
Tests whether X is a user-defined symbol.
*/
void do_user(void)
{
    char *str;

    ONEPARAM;
    if (IS_USR_INDEX(stack[-1]))
        stack[-1] = MAKE_BOOLEAN(1);
    else if (IS_USR_STRING(stack[-1])) {
        str = GET_AS_USR_STRING(stack[-1]);
        stack[-1] = MAKE_BOOLEAN(*str != 0 && *str != '"');
    } else
        stack[-1] = MAKE_BOOLEAN(0);
}
#endif

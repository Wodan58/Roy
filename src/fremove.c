/*
    module  : fremove.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef FREMOVE_C
#define FREMOVE_C

/**
1930  fremove  :  DA	P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
void do_fremove(void)
{
    COMPILE;
    ONEPARAM;
    STRING;
    stack[-1] = MAKE_BOOLEAN(!remove(get_string(stack[-1])));
}
#endif

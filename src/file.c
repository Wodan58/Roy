/*
    module  : file.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef FILE_C
#define FILE_C

/**
2420  file  :  DA	F  ->  B
Tests whether F is a file.
*/
void do_file(void)
{
    COMPILE;
    ONEPARAM;
    stack[-1] = MAKE_BOOLEAN(IS_FILE(stack[-1]));
}
#endif

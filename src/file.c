/*
    module  : file.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef FILE_C
#define FILE_C

/**
file  :  F  ->  B
Tests whether F is a file.
*/
void do_file(void)
{
    COMPILE;
    stack[-1] = is_file(stack[-1]);
}
#endif

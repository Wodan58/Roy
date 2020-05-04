/*
    module  : in_str.c
    version : 1.1
    date    : 03/15/20
*/
#ifndef IN_STR_C
#define IN_STR_C

/**
in_str  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
void do_in_str(void)
{
    char *str;

    BINARY;
    for (str = (char *)stack[-1]; str && *str && *str != stack[-2]; str++)
	;
    stack[-2] = str && *str != 0;
    do_zap();
}
#endif

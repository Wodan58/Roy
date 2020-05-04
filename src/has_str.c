/*
    module  : has_str.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef HAS_STR_C
#define HAS_STR_C

/**
has_str  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
void do_has_str(void)
{
    char *str;

    BINARY;
    for (str = (char *)stack[-2]; str && *str && *str != stack[-1]; str++)
	;
    stack[-2] = str && *str != 0;
    do_zap();
}
#endif

/*
    module  : ftell.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef FTELL_C
#define FTELL_C

/**
2000  ftell  :  A	S  ->  S I
I is the current position of stream S.
*/
void do_ftell(void)
{
    FILE *fp;

    COMPILE;
    ONEPARAM;
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    do_push(MAKE_INTEGER(ftell(fp)));
}
#endif

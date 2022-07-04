/*
    module  : ferror.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef FERROR_C
#define FERROR_C

/**
1850  ferror  :  A	S  ->  S B
B is the error status of stream S.
*/
void do_ferror(void)
{
    FILE *fp;

    COMPILE;
    ONEPARAM;
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    do_push(MAKE_BOOLEAN(ferror(fp) != 0));
}
#endif

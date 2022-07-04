/*
    module  : feof.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef FEOF_C
#define FEOF_C

/**
1840  feof  :  A	S  ->  S B
B is the end-of-file status of stream S.
*/
void do_feof(void)
{
    FILE *fp;

    COMPILE;
    ONEPARAM;
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    do_push(MAKE_BOOLEAN(feof(fp) != 0));
}
#endif

/*
    module  : fflush.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef FFLUSH_C
#define FFLUSH_C

/**
1860  fflush  :  N	S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
void do_fflush(void)
{
    FILE *fp;

    COMPILE;
    ONEPARAM;
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    fflush(fp);
}
#endif

/*
    module  : fgetch.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef FGETCH_C
#define FGETCH_C

/**
1880  fgetch  :  A	S  ->  S C
C is the next available character from stream S.
*/
void do_fgetch(void)
{
    FILE *fp;

    COMPILE;
    ONEPARAM;
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    do_push(MAKE_CHAR(fgetc(fp)));
}
#endif

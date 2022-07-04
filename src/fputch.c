/*
    module  : fputch.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef FPUTCH_C
#define FPUTCH_C

/**
1960  fputch  :  D	S C  ->  S
The character C is written to the current position of stream S.
*/
void do_fputch(void)
{
    int ch;
    FILE *fp;

    COMPILE;
    TWOPARAMS;
    INTEGER;
    ch = GET_AS_INTEGER(stack_pop());
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    fputc(ch, fp);
}
#endif

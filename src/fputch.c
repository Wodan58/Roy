/*
    module  : fputch.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef FPUTCH_C
#define FPUTCH_C

/**
fputch  :  S C  ->  S
The character C is written to the current position of stream S.
*/
void do_fputch(void)
{
    int ch;

    COMPILE;
    ch = do_pop();
    putc(ch, (FILE *)stack[-1]);
}
#endif

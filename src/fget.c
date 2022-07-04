/*
    module  : fget.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef FGET_C
#define FGET_C

/**
1870  fget  :  A	S  ->  S F
Reads a factor from stream S and pushes it onto stack.
*/
void do_fget(void)
{
    FILE *fp;
    int stdin_dup;

    COMPILE;
    ONEPARAM;
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    if ((stdin_dup = dup(0)) != -1)
        dup2(fileno(fp), 0);
    readfactor(yylex());
    if (stdin_dup != -1) {
        dup2(stdin_dup, 0);
        close(stdin_dup);
    }
}
#endif

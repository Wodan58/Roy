/*
    module  : fput.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef FPUT_C
#define FPUT_C

/**
1950  fput  :  D	S X  ->  S
Writes X to stream S, pops X off stack.
*/
void do_fput(void)
{
    FILE *fp;
    value_t temp;
    int stdout_dup;

    COMPILE;
    TWOPARAMS;
    temp = stack_pop();
    FILE1;
    fp = GET_AS_FILE(stack[-1]);
    if ((stdout_dup = dup(1)) != -1)
        dup2(fileno(fp), 1);
    writefactor(temp);
    putchar(' ');
    fflush(stdout);
    if (stdout_dup != -1) {
        dup2(stdout_dup, 1);
        close(stdout_dup);
    }
}
#endif

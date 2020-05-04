/*
    module  : fput.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef FPUT_C
#define FPUT_C

/**
fput  :  S X  ->  S
Writes X to stream S, pops X off stack.
*/
void do_fput(void)
{
    FILE *fp;
    intptr_t temp;
    int stdout_dup;

    COMPILE;
    temp = do_pop();
    fp = (FILE *)stack[-1];
    stdout_dup = dup(1);
    dup2(fileno(fp), 1);
    writefactor(temp);
    dup2(stdout_dup, 1);
    close(stdout_dup);
}
#endif

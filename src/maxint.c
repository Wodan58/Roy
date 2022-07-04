/*
    module  : maxint.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef MAXINT_C
#define MAXINT_C

/**
1020  maxint  :  A	->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
void do_maxint(void)
{
    do_push(MAKE_INTEGER(MAXINT_));
}
/* maxint.c */
#endif

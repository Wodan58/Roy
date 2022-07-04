/*
    module  : true.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef TRUE_C
#define TRUE_C

/**
1010  true  :  A	->  true
Pushes the value true.
*/
void do_true(void)
{
    do_push(MAKE_BOOLEAN(1));
}
/* true.c */
#endif

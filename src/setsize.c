/*
    module  : setsize.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef SETSIZE_C
#define SETSIZE_C

/**
1030  setsize  :  A	->  setsize
Pushes the maximum number of elements in a set (platform dependent).
Typically it is 32, and set members are in the range 0..31.
*/
void do_setsize(void)
{
    do_push(MAKE_INTEGER(SETSIZE_));
}
#endif

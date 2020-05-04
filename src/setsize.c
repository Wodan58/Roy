/*
    module  : setsize.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef SETSIZE_C
#define SETSIZE_C

/**
setsize  :  ->  setsize
Pushes the maximum number of elements in a set (platform dependent).
Typically it is 32, and set members are in the range 0..31.
*/
void do_setsize(void)
{
    do_push(SETSIZE_);
}
#endif

/*
    module  : __dump.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef __DUMP_C
#define __DUMP_C

/**
__dump  :  ->  [..]
debugging only: pushes the dump as a list.
*/
void do___dump(void)
{
    COMPILE;
    do_push(0);
}
#endif

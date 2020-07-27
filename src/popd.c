/*
    module  : popd.c
    version : 1.10
    date    : 07/23/20
*/
#ifndef POPD_C
#define POPD_C

/**
popd  :  Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
void do_popd(void)
{
    BINARY;
    stack[-2] = stack[-1];
    do_pop();
}
#endif

/*
    module  : popd.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef POPD_C
#define POPD_C

/**
1260  popd  :  DDA	Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
void do_popd(void)
{
    TWOPARAMS;
    stack[-2] = stack[-1];
    stack_pop();
}
#endif

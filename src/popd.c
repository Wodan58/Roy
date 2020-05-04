/*
    module  : popd.c
    version : 1.9
    date    : 01/19/20
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
    do_zap();
}
#endif

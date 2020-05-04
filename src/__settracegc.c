/*
    module  : __settracegc.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef __SETTRACEGC_C
#define __SETTRACEGC_C

/**
__settracegc  :  I  ->
Sets value of flag for tracing garbage collection to I (= 0..2).
*/
void do___settracegc(void)
{
    COMPILE;
    tracegc = do_pop();
}
#endif

/*
    module  : jsetblockinc.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETBLOCKINC_C
#define JSETBLOCKINC_C

/**
jsetblockinc  :  obj val  ->
Changes the block increment amount for the component to val.
*/
void do_jsetblockinc(void)
{
    int obj, val;

    COMPILE;
    val = do_pop();
    obj = do_pop();
    j_setblockinc(obj, val);
}
#endif

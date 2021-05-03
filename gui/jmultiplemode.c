/*
    module  : jmultiplemode.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JMULTIPLEMODE_C
#define JMULTIPLEMODE_C

/**
jmultiplemode  :  obj bool  ->
If bool is J_TRUE, selection mode is turned to multiple mode.
*/
void do_jmultiplemode(void)
{
    int obj, bool;

    COMPILE;
    bool = do_pop();
    obj = do_pop();
    j_multiplemode(obj, bool);
}
#endif

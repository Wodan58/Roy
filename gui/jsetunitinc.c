/*
    module  : jsetunitinc.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETUNITINC_C
#define JSETUNITINC_C

/**
jsetunitinc  :  obj val  ->
Changed the unit increment amount for the component to val.
*/
void do_jsetunitinc(void)
{
    int obj, val;

    COMPILE;
    val = do_pop();
    obj = do_pop();
    j_setunitinc(obj, val);
}
#endif

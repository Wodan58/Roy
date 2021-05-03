/*
    module  : jsetmin.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETMIN_C
#define JSETMIN_C

/**
jsetmin  :  obj val  ->
Changes the minimum value for the component to val.
*/
void do_jsetmin(void)
{
    int obj, val;

    COMPILE;
    val = do_pop();
    obj = do_pop();
    j_setmin(obj, val);
}
#endif

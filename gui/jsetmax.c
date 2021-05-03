/*
    module  : jsetmax.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETMAX_C
#define JSETMAX_C

/**
jsetmax  :  obj val  ->
Changes the maximum value for the component to val.
*/
void do_jsetmax(void)
{
    int obj, val;

    COMPILE;
    val = do_pop();
    obj = do_pop();
    j_setmax(obj, val);
}
#endif

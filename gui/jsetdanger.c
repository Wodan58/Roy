/*
    module  : jsetdanger.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETDANGER_C
#define JSETDANGER_C

/**
jsetdanger  :  obj val  ->
Changes the danger value of component obj to val.
*/
void do_jsetdanger(void)
{
    int obj, val;

    COMPILE;
    val = do_pop();
    obj = do_pop();
    j_setdanger(obj, val);
}
#endif

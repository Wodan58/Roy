/*
    module  : jsetflowfill.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETFLOWFILL_C
#define JSETFLOWFILL_C

/**
jsetflowfill  :  obj bool  ->
Resizes all contained components to the height (width) of component obj. Needs
a flowlayout manager.
*/
void do_jsetflowfill(void)
{
    int obj, bool;

    COMPILE;
    bool = do_pop();
    obj = do_pop();
    j_setflowfill(obj, bool);
}
#endif

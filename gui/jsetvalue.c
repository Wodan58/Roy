/*
    module  : jsetvalue.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETVALUE_C
#define JSETVALUE_C

/**
jsetvalue  :  obj val  ->
Changes the current value of the component to val.
*/
void do_jsetvalue(void)
{
    int obj, val;

    COMPILE;
    val = do_pop();
    obj = do_pop();
    j_setvalue(obj, val);
}
#endif

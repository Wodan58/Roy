/*
    module  : jgetstate.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETSTATE_C
#define JGETSTATE_C

/**
jgetstate  :  obj  ->  state
Returns J_TRUE, if component is selected, J_FALSE otherwise.
*/
void do_jgetstate(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getstate(obj);
    do_push(temp);
}
#endif

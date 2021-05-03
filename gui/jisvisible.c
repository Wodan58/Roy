/*
    module  : jisvisible.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JISVISIBLE_C
#define JISVISIBLE_C

/**
jisvisible  :  obj  ->  status
Returns J_TRUE if obj is visible, J_FALSE otherwise.
*/
void do_jisvisible(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_isvisible(obj);
    do_push(temp);
}
#endif

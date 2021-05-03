/*
    module  : jisselect.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JISSELECT_C
#define JISSELECT_C

/**
jisselect  :  obj item  ->  status
Returns J_TRUE if the particular item is currently selected, J_FALSE otherwise.
*/
void do_jisselect(void)
{
    int obj, item, temp;

    COMPILE;
    item = do_pop();
    obj = do_pop();
    temp = j_isselect(obj, item);
    do_push(temp);
}
#endif

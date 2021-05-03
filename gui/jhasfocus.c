/*
    module  : jhasfocus.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JHASFOCUS_C
#define JHASFOCUS_C

/**
jhasfocus  :  obj  ->  status
Returns J_TRUE if the component has the focus, J_FALSE otherwise.
*/
void do_jhasfocus(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_hasfocus(obj);
    do_push(temp);
}
#endif

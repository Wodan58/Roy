/*
    module  : jisresizable.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JISRESIZABLE_C
#define JISRESIZABLE_C

/**
jisresizable  :  obj  ->  status
Returns true if component is resizable, false otherwise.
*/
void do_jisresizable(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_isresizable(obj);
    do_push(temp);
}
#endif

/*
    module  : jenable.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JENABLE_C
#define JENABLE_C

/**
jenable  :  obj  ->
Enables the component obj.
*/
void do_jenable(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_enable(obj);
}
#endif

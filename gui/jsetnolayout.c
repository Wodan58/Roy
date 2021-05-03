/*
    module  : jsetnolayout.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETNOLAYOUT_C
#define JSETNOLAYOUT_C

/**
jsetnolayout  :  obj  ->
Removes the current layout manager from component obj.
*/
void do_jsetnolayout(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_setnolayout(obj);
}
#endif

/*
    module  : jgetwidth.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETWIDTH_C
#define JGETWIDTH_C

/**
jgetwidth  :  obj  ->  width
Returns the width of component obj.
*/
void do_jgetwidth(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getwidth(obj);
    do_push(temp);
}
#endif

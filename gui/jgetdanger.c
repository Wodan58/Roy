/*
    module  : jgetdanger.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETDANGER_C
#define JGETDANGER_C

/**
jgetdanger  :  obj  ->  danger
Returns the danger value of component obj.
*/
void do_jgetdanger(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getdanger(obj);
    do_push(temp);
}
#endif

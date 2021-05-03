/*
    module  : jgetitemcount.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETITEMCOUNT_C
#define JGETITEMCOUNT_C

/**
jgetitemcount  :  obj  ->  count
Returns the number of items of component obj.
*/
void do_jgetitemcount(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getitemcount(obj);
    do_push(temp);
}
#endif

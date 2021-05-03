/*
    module  : jgetvalue.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETVALUE_C
#define JGETVALUE_C

/**
jgetvalue  :  obj  ->  value
Returns the current setting of the scrollbar.
*/
void do_jgetvalue(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getvalue(obj);
    do_push(temp);
}
#endif

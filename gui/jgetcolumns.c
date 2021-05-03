/*
    module  : jgetcolumns.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETCOLUMNS_C
#define JGETCOLUMNS_C

/**
jgetcolumns  :  obj  ->  columns
Gets the number of columns in obj.
*/
void do_jgetcolumns(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getstate(obj);
    do_push(temp);
}
#endif

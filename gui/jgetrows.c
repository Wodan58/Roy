/*
    module  : jgetrows.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETROWS_C
#define JGETROWS_C

/**
jgetrows  :  obj  ->  rows
Gets the number of rows in obj.
*/
void do_jgetrows(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getrows(obj);
    do_push(temp);
}
#endif

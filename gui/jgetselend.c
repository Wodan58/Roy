/*
    module  : jgetselend.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETSELEND_C
#define JGETSELEND_C

/**
jgetselend  :  obj  ->  position
Returns the ending position of any selected text.
*/
void do_jgetselend(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getselend(obj);
    do_push(temp);
}
#endif

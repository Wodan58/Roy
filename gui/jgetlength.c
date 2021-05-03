/*
    module  : jgetlength.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETLENGTH_C
#define JGETLENGTH_C

/**
jgetlength  :  obj  ->  length
Returns the length of component's label or text.
*/
void do_jgetlength(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getlength(obj);
    do_push(temp);
}
#endif

/*
    module  : jgetlayoutid.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETLAYOUTID_C
#define JGETLAYOUTID_C

/**
jgetlayoutid  :  obj  ->  event
Returns the event number of the layoutmanager for container obj.
*/
void do_jgetlayoutid(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getlayoutid(obj);
    do_push(temp);
}
#endif

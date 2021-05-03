/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETFONTHEIGHT_C
#define JGETFONTHEIGHT_C

/**
jgetfontheight  :  obj  ->  height
Returns the total pixel height of the actual font of component obj.
*/
void do_jgetfontheight(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getfontheight(obj);
    do_push(temp);
}
#endif

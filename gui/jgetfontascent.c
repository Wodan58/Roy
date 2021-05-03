/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETFONTASCENT_C
#define JGETFONTASCENT_C

/**
jfontascent  :  obj  ->  ascent
Returns the ascent (space above the baseline) of the actual font of component
obj.
*/
void do_jgetfontascent(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getfontascent(obj);
    do_push(temp);
}
#endif

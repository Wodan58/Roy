/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETVIEWPORTHEIGHT_C
#define JGETVIEWPORTHEIGHT_C

/**
jgetviewportheight  :  obj  ->  height
Returns the height of the component's obj port (the area that is shown).
*/
void do_jgetviewportheight(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getviewportheight(obj);
    do_push(temp);
}
#endif

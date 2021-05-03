/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETVIEWPORTWIDTH_C
#define JGETVIEWPORTWIDTH_C

/**
jgetviewportwidth  :  obj  ->  width
Returns the width of the component's obj port (the area that is shown).
*/
void do_jgetviewportwidth(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getviewportwidth(obj);
    do_push(temp);
}
#endif

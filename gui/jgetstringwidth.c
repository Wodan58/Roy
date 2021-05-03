/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETSTRINGWIDTH_C
#define JGETSTRINGWIDTH_C

/**
jgetstringwidth  :  obj str  ->  length
Returns the length of str of the actual font of component obj.
*/
void do_jgetstringwidth(void)
{
    char *str;
    int obj, temp;

    COMPILE;
    str = (char *)do_pop();
    obj = do_pop();
    temp = j_getstringwidth(obj, str);
    do_push(temp);
}
#endif

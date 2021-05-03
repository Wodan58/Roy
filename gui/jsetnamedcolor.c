/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETNAMEDCOLOR_C
#define JSETNAMEDCOLOR_C

/**
jsetnamedcolor  :  obj color  ->
Sets the foreground color to a predefined color.
*/
void do_jsetnamedcolor(void)
{
    int obj, color;

    COMPILE;
    color = do_pop();
    obj = do_pop();
    j_setnamedcolor(obj, color);
}
#endif

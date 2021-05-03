/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETNAMEDCOLORBG_C
#define JSETNAMEDCOLORBG_C

/**
jsetnamedcolorbg  :  obj color  ->
Sets the background color to a predefined color.
*/
void do_jsetnamedcolorbg(void)
{
    int obj, color;

    COMPILE;
    color = do_pop();
    obj = do_pop();
    j_setnamedcolorbg(obj, color);
}
#endif

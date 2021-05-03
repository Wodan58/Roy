/*
    module  : jsetcolorbg.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETCOLORBG_C
#define JSETCOLORBG_C

/**
jsetcolorbg  :  obj r g b  ->
Sets the background color to the (r, g, b) values.
*/
void do_jsetcolorbg(void)
{
    int obj, r, g, b;

    COMPILE;
    b = do_pop();
    g = do_pop();
    r = do_pop();
    obj = do_pop();
    j_setcolorbg(obj, r, g, b);
}
#endif

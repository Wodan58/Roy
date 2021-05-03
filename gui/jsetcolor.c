/*
    module  : jsetcolor.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETCOLOR_C
#define JSETCOLOR_C

/**
jsetcolor  :  obj r g b  ->
Sets the foreground color to the (r, g, b) values.
*/
void do_jsetcolor(void)
{
    int obj, r, g, b;

    COMPILE;
    b = do_pop();
    g = do_pop();
    r = do_pop();
    obj = do_pop();
    j_setcolor(obj, r, g, b);
}
#endif

/*
    module  : jdrawcircle.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWCIRCLE_C
#define JDRAWCIRCLE_C

/**
jdrawcircle  :  obj x y r  ->
Draws an unfilled circle with center (x, y) and radius x.
*/
void do_jdrawcircle(void)
{
    int obj, x, y, r;

    COMPILE;
    r = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_drawcircle(obj, x, y, r);
}
#endif

/*
    module  : jfillcircle.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFILLCIRCLE_C
#define JFILLCIRCLE_C

/**
jfillcircle  :  obj x y r  ->
Draws a filled circle with center (x, y) and radius r.
*/
void do_jfillcircle(void)
{
    int obj, x, y, r;

    COMPILE;
    r = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_fillcircle(obj, x, y, r);
}
#endif

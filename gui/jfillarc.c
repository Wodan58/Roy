/*
    module  : jfillarc.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFILLARC_C
#define JFILLARC_C

/**
jfillarc  :  obj x y rx ry arc1 arc2  ->
Draws an filled arc from angle arc11 to angle arc2 with the center (x, y) and
the horizontal radius rx and the vertical radius ry.
*/
void do_jfillarc(void)
{
    int obj, x, y, rx, ry, arc1, arc2;

    COMPILE;
    arc2 = do_pop();
    arc1 = do_pop();
    ry = do_pop();
    rx = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_fillarc(obj, x, y, rx, ry, arc1, arc2);
}
#endif

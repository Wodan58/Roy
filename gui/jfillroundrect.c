/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFILLROUNDRECT_C
#define JFILLROUNDRECT_C

/**
jfillroundrect  :  obj x y width height arcx arcy  ->
Draws a filled rectangle from (x, y) of size width x height with rounded
corners; arcx and arcy specify the radius of rectangle corners.
*/
void do_jfillroundrect(void)
{
    int obj, x, y, width, height, arcx, arcy;

    COMPILE;
    arcy = do_pop();
    arcx = do_pop();
    height = do_pop();
    width = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_fillroundrect(obj, x, y, width, height, arcx, arcy);
}
#endif

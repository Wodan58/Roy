/*
    module  : jtranslate.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JTRANSLATE_C
#define JTRANSLATE_C

/**
jtranslate  :  obj x y ->
Moves the origin of drawing operations to (x, y).
*/
PRIVATE void do_jtranslate(void)
{
    int obj, x, y;

    COMPILE;
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_translate(obj, x, y);
}
#endif

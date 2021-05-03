/*
    module  : jdrawstring.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWSTRING_C
#define JDRAWSTRING_C

/**
jdrawstring  :  obj x y str  ->
Draws text on screen at position (x, y).
*/
void do_jdrawstring(void)
{
    char *str;
    int obj, x, y;

    COMPILE;
    str = (char *)do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_drawstring(obj, x, y, str);
}
#endif

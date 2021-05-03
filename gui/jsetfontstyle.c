/*
    module  : jsetfontstyle.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETFONTSTYLE_C
#define JSETFONTSTYLE_C

/**
jsetfontstyle  :  obj style  ->
Changes the font to the given style.
*/
void do_jsetfontstyle(void)
{
    int obj, style;

    COMPILE;
    style = do_pop();
    obj = do_pop();
    j_setfontstyle(obj, style);
}
#endif

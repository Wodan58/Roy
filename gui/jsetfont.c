/*
    module  : jsetfont.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETFONT_C
#define JSETFONT_C

/**
jsetfont  :  obj name style size  ->
Changes the font to the given characteristics name, style, and size.
*/
void do_jsetfont(void)
{
    int obj, name, style, size;

    COMPILE;
    size = do_pop();
    style = do_pop();
    name = do_pop();
    obj = do_pop();
    j_setfont(obj, name, style, size);
}
#endif

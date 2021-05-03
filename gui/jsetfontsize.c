/*
    module  : jsetfontsize.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETFONTSIZE_C
#define JSETFONTSIZE_C

/**
jsetfontsize  :  obj size  ->
Changes the font to the given size.
*/
void do_jsetfontsize(void)
{
    int obj, size;

    COMPILE;
    size = do_pop();
    obj = do_pop();
    j_setfontsize(obj, size);
}
#endif

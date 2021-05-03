/*
    module  : jsetfontname.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETFONTNAME_C
#define JSETFONTNAME_C

/**
jsetfontname  :  obj name  ->
Changes the font to the given name.
*/
void do_jsetfontname(void)
{
    int obj, name;

    COMPILE;
    name = do_pop();
    obj = do_pop();
    j_setfontname(obj, name);
}
#endif

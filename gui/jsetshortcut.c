/*
    module  : jsetshortcut.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETSHORTCUT_C
#define JSETSHORTCUT_C

/**
jsetshortcut  :  obj chr  ->
Changed the shortcut chr of the component.
*/
void do_jsetshortcut(void)
{
    int obj, chr;

    COMPILE;
    chr = do_pop();
    obj = do_pop();
    j_setshortcut(obj, chr);
}
#endif

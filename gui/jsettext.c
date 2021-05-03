/*
    module  : jsettext.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETTEXT_C
#define JSETTEXT_C

/**
jsettext  :  obj str  ->
Sets the content or the label of the component obj to str.
*/
void do_jsettext(void)
{
    int obj;
    char *title;

    COMPILE;
    title = (char *)do_pop();
    obj = do_pop();
    j_settext(obj, title);
}
#endif

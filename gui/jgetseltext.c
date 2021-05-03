/*
    module  : jgetseltext.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETSELTEXT_C
#define JGETSELTEXT_C

/**
jgetseltext  :  obj  ->  text
Returns the currently selected text of component obj.
*/
void do_jgetseltext(void)
{
    int obj;
    char text[MAXSTR];

    COMPILE;
    obj = do_pop();
    j_getseltext(obj, text);
    do_push((intptr_t)GC_strdup(text) | JLAP_INVALID);
}
#endif

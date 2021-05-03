/*
    module  : jgettext.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETTEXT_C
#define JGETTEXT_C

/**
jgettext  :  obj  ->  text
Returns the component's text or label.
*/
void do_jgettext(void)
{
    int obj;
    char text[MAXSTR];

    COMPILE;
    obj = do_pop();
    j_gettext(obj, text);
    do_push((intptr_t)GC_strdup(text) | JLAP_INVALID);
}
#endif

/*
    module  : jinserttext.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JINSERTTEXT_C
#define JINSERTTEXT_C

/**
jinserttext  :  obj text pos  ->
Places additional text within the component at the given position pos.
*/
void do_jinserttext(void)
{
    char *text;
    int obj, pos;

    COMPILE;
    pos = do_pop();
    text = (char *)do_pop();
    obj = do_pop();
    j_inserttext(obj, text, pos);
}
#endif

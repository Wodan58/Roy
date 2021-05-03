/*
    module  : jreplacetext.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JREPLACETEXT_C
#define JREPLACETEXT_C

/**
jreplacetext  :  obj text start end  ->
Replaces the text from starting position start to ending position end with the
given text.
*/
void do_jreplacetext(void)
{
    char *text;
    int obj, start, end;

    COMPILE;
    end = do_pop();
    start = do_pop();
    text = (char *)do_pop();
    obj = do_pop();
    j_replacetext(obj, text, start, end);
}
#endif

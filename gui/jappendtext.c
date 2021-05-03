/*
    module  : jappendtext.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JAPPENDTEXT_C
#define JAPPENDTEXT_C

/**
jappendtext  :  obj text  ->
Appends the given text to the obj current text.
*/
void do_jappendtext(void)
{
    int obj;
    char *text;

    COMPILE;
    text = (char *)do_pop();
    obj = do_pop();
    j_appendtext(obj, text);
}
#endif

/*
    module  : jsetechochar.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETECHOCHAR_C
#define JSETECHOCHAR_C

/**
jsetechochar  :  obj chr  ->
Changes the character chr that is used to echo all user input in the component.
*/
void do_jsetechochar(void)
{
    int obj, chr;

    COMPILE;
    chr = do_pop();
    obj = do_pop();
    j_setechochar(obj, chr);
}
#endif

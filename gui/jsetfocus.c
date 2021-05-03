/*
    module  : jsetfocus.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETFOCUS_C
#define JSETFOCUS_C

/**
jsetfocus  :  obj  ->
Directs the input focus to component obj.
*/
void do_jsetfocus(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_setfocus(obj);
}
#endif

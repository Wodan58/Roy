/*
    module  : jsetfixlayout.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETFIXLAYOUT_C
#define JSETFIXLAYOUT_C

/**
jsetfixlayout  :  obj  ->
Adds a fixlayout manager to component obj (default layout manager).
*/
void do_jsetfixlayout(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_setfixlayout(obj);
}
#endif

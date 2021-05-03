/*
    module  : jseparator.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSEPARATOR_C
#define JSEPARATOR_C

/**
jseparator  :  obj  ->
Adds a separator bar to the component obj.
*/
void do_jseparator(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_separator(obj);
}
#endif

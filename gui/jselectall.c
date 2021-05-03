/*
    module  : jselectall.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSELECTALL_C
#define JSELECTALL_C

/**
jselectall  :  obj  ->
Selects all the text in the component obj.
*/
void do_jselectall(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_selectall(obj);
}
#endif

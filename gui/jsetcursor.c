/*
    module  : jsetcursor.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETCURSOR_C
#define JSETCURSOR_C

/**
jsetcursor  :  obj cursor  ->
Changes the component's obj cursor to the specified cursor.
*/
void do_jsetcursor(void)
{
    int obj, cursor;

    COMPILE;
    cursor = do_pop();
    obj = do_pop();
    j_setcursor(obj, cursor);
}
#endif

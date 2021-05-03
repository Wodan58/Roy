/*
    module  : jlist.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JLIST_C
#define JLIST_C

/**
jlist  :  obj rows  ->  event
Creates a new list component with the specified number of rows and returns its
event number.
*/
void do_jlist(void)
{
    int obj, rows, temp;

    COMPILE;
    rows = do_pop();
    obj = do_pop();
    temp = j_list(obj, rows);
    do_push(temp);
}
#endif

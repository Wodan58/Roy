/*
    module  : jtextarea.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JTEXTAREA_C
#define JTEXTAREA_C

/**
jtextarea  :  obj rows columns  ->  event
Creates a new textarea component with the specified number of rows ans columns
and returns its event number.
*/
void do_jtextarea(void)
{
    int obj, rows, columns, temp;

    COMPILE;
    columns = do_pop();
    rows = do_pop();
    obj = do_pop();
    temp = j_textarea(obj, rows, columns);
    do_push(temp);
}
#endif

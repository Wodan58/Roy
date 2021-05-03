/*
    module  : jsetcolumns.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETCOLUMNS_C
#define JSETCOLUMNS_C

/**
jsetcolumns  :  obj columns  ->
Sets the number of columns for obj to columns.
*/
void do_jsetcolumns(void)
{
    int obj, columns;

    COMPILE;
    columns = do_pop();
    obj = do_pop();
    j_setcolumns(obj, columns);
}
#endif

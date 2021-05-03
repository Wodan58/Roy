/*
    module  : jsetrows.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETROWS_C
#define JSETROWS_C

/**
jsetrows  :  obj rows  ->
Sets the number of rows for obj to rows.
*/
void do_jsetrows(void)
{
    int obj, rows;

    COMPILE;
    rows = do_pop();
    obj = do_pop();
    j_setrows(obj, rows);
}
#endif

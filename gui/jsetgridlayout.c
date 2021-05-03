/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETGRIDLAYOUT_C
#define JSETGRIDLAYOUT_C

/**
jsetgridlayout  :  obj row col  ->
Adds a gridlayout manager to component obj with the specified rows and columns.
*/
void do_jsetgridlayout(void)
{
    int obj, row, col;

    COMPILE;
    col = do_pop();
    row = do_pop();
    obj = do_pop();
    j_setgridlayout(obj, row, col);
}
#endif

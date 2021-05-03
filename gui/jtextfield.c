/*
    module  : jtextfield.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JTEXTFIELD_C
#define JTEXTFIELD_C

/**
jtextfield  :  obj columns  ->  event
Creates a new textfield component with the specified number of columns and
returns its event number.
*/
void do_jtextfield(void)
{
    int obj, columns, temp;

    COMPILE;
    columns = do_pop();
    obj = do_pop();
    temp = j_textfield(obj, columns);
    do_push(temp);
}
#endif

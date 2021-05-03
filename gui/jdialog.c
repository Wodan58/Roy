/*
    module  : jdialog.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDIALOG_C
#define JDIALOG_C

/**
jdialog  :  obj label  ->  event
Creates a new dialog window with the specified label and returns its event
number.
*/
void do_jdialog(void)
{
    char *label;
    int obj, temp;

    COMPILE;
    label = (char *)do_pop();
    obj = do_pop();
    temp = j_dialog(obj, label);
    do_push(temp);
}
#endif

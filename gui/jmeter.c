/*
    module  : jmeter.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JMETER_C
#define JMETER_C

/**
jmeter  :  obj title  ->  event
Creates a new pointer-instrument with the specified label title and returns its
event number. The meter has predefined values from 0 to 100. This can be
changed via jsetmin and jsetmax. A danger value is set to 80 and can be
justified with jsetdanger.
*/
void do_jmeter(void)
{
    char *title;
    int obj, temp;

    COMPILE;
    title = (char *)do_pop();
    obj = do_pop();
    temp = j_meter(obj, title);
    do_push(temp);
}
#endif

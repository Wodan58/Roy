/*
    module  : jprinter.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JPRINTER_C
#define JPRINTER_C

/**
jprinter  :  frame  ->  event
Creates a new object, representing a paper of the printer and returns its
event number. On error -1 will be returned. A printer object can be used like a
canvas where all drawing functions will be passed to the printer instead of a
window. A printer generates no event.
*/
void do_jprinter(void)
{
    int frame, temp;

    COMPILE;
    frame = do_pop();
    temp = j_printer(frame);
    do_push(temp);
}
#endif

/*
    module  : jprint.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JPRINT_C
#define JPRINT_C

/**
jprint  :  obj  ->
Prints the component. With X-Windows all components have Motif-look. If
component is a printer, the actual page will be closed, and a new page will be
opened. The pages are not yet printed. To print all pages call jdispose.
*/
void do_jprint(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_print(obj);
}
#endif

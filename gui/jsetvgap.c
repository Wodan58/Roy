/*
    module  : jsetvgap.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETVGAP_C
#define JSETVGAP_C

/**
jsetvgap  :  obj vgap  ->
Sets the vertical gap between components to hgap pixels.
*/
void do_jsetvgap(void)
{
    int obj, vgap;

    COMPILE;
    vgap = do_pop();
    obj = do_pop();
    j_setvgap(obj, vgap);
}
#endif

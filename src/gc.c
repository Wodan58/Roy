/*
    module  : gc.c
    version : 1.6
    date    : 01/19/20
*/
#ifndef GC_C
#define GC_C

/**
gc  :  ->
Initiates garbage collection.
*/
void do_gc(void)
{
    COMPILE;
    GC_gcollect();
}
#endif

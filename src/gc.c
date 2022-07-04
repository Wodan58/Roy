/*
    module  : gc.c
    version : 1.7
    date    : 06/21/22
*/
#ifndef GC_C
#define GC_C

/**
3030  gc  :  N	->
Initiates garbage collection.
*/
void do_gc(void)
{
    COMPILE;
    GC_gcollect();
}
#endif

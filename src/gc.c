/*
    module  : gc.c
    version : 1.8
    date    : 09/19/23
*/
#ifndef GC_C
#define GC_C

/**
OK 3010  gc  :  N	->
Initiates garbage collection.
*/
void gc_(pEnv env)
{
    GC_gcollect();
    /* nothing */
}
#endif

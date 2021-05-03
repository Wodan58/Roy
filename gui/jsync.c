/*
    module  : jsync.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSYNC_C
#define JSYNC_C

/**
jsync  :  ->
Synchronizes the application with the JAPI kernel.
*/
PRIVATE void do_jsync(void)
{
    COMPILE;
    j_sync();
}
#endif

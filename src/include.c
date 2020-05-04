/*
    module  : include.c
    version : 1.10
    date    : 03/15/20
*/
#ifndef INCLUDE_C
#define INCLUDE_C

/**
include  :  "filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
void do_include(void)
{
    UNARY;
    include((char *)do_pop());
}
#endif

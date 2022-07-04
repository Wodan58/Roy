/*
    module  : include.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef INCLUDE_C
#define INCLUDE_C

/**
3140  include  :  D	"filnam.ext"  ->
Transfers input to file whose name is "filnam.ext".
On end-of-file returns to previous input file.
*/
void do_include(void)
{
    ONEPARAM;
    STRING;
    include(get_string(stack_pop()), 1);
}
#endif

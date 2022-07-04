/*
    module  : filetime.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef FILETIME_C
#define FILETIME_C

#ifndef COSMO
#include <sys/stat.h>
#endif

/**
3180  filetime  :  DA 	F  ->  T
T is the modification time of file F.
*/
void do_filetime(void)
{
    struct stat buf;

    COMPILE;
    ONEPARAM;
    STRING;
    if (stat(get_string(stack[-1]), &buf) == -1)
        buf.st_mtime = 0;
    stack[-1] = MAKE_INTEGER(buf.st_mtime);
}
#endif

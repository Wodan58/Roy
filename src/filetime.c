/*
    module  : filetime.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef FILETIME_C
#define FILETIME_C

#include <sys/stat.h>

/**
filetime  :  F  ->  T
T is the modification time of file F.
*/
void do_filetime(void)
{
    struct stat buf;

    COMPILE;
    if (stat((char *)stack[-1], &buf) == -1)
	buf.st_mtime = 0;
    stack[-1] = buf.st_mtime;
}
#endif

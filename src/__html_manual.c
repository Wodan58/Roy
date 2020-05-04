/*
    module  : __html_manual.c
    version : 1.5
    date    : 01/19/20
*/
#ifndef __HTML_MANUAL_C
#define __HTML_MANUAL_C

void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);

/**
__html_manual  :  ->
Writes this manual of all Joy primitives to output file in HTML style.
*/
void do___html_manual(void)
{
#ifdef COMPILING
    make_manual(1);
#endif
}
#endif

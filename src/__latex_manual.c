/*
    module  : 
    version : 1.5
    date    : 01/19/20
*/
#ifndef __LATEX_MANUAL_C
#define __LATEX_MANUAL_C

void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);

/**
__latex_manual  :  ->
Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
void do___latex_manual(void)
{
#ifdef COMPILING
    make_manual(2);
#endif
}
#endif

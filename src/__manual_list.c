/*
    module  : __manual_list.c
    version : 1.9
    date    : 01/20/20
*/
#ifndef __MANUAL_LIST_C
#define __MANUAL_LIST_C

/**
__manual_list  :  ->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
void do___manual_list(void)
{
#ifdef COMPILING
    int i;
    Stack *List = 0, *Quot;

    for (i = 0; optable[i].name; i++)
	;
    while (--i) {
	Quot = 0;
	vec_push(Quot, (intptr_t)optable[i].messg2);
	vec_push(Quot, (intptr_t)optable[i].messg1);
	vec_push(Quot, (intptr_t)optable[i].name);
	vec_push(List, (intptr_t)Quot);
    }
    do_push((intptr_t)List);
#endif
}
#endif

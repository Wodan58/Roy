/*
    module  : jfileselect.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFILESELECT_C
#define JFILESELECT_C

/**
jfileselect  :  frame title filter filename  ->  filename
Opens a fileselector box with the preselected filename and the specified title
and returns the selected filename. filter specifies the Filename Filter. A
Fileselector can be used with output redirections via jconnect.
*/
void do_jfileselect(void)
{
    int frame;
    char *title, *filter, filename[MAXSTR];

    COMPILE;
    strcpy(filename, (char *)do_pop());
    filter = (char *)do_pop();
    title = (char *)do_pop();
    frame = do_pop();
    j_fileselect(frame, title, filter, filename);
    do_push((intptr_t)GC_strdup(filename) | JLAP_INVALID);
}
#endif

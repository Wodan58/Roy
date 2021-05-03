/*
    module  : jfiledialog.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFILEDIALOG_C
#define JFILEDIALOG_C

/**
jfiledialog  :  frame title directory  ->  filename
Opens a filedialog box in the specified directory with the specified title and
returns the selected filename. If title contains "/S" the SAVE-filedialog will
be called. The substring "/S" will be removed.
*/
void do_jfiledialog(void)
{
    int frame;
    char *title, *directory, filename[MAXSTR];

    COMPILE;
    directory = (char *)do_pop();
    title = (char *)do_pop();
    frame = do_pop();
    j_filedialog(frame, title, directory, filename);
    do_push((intptr_t)GC_strdup(filename) | JLAP_INVALID);
}
#endif

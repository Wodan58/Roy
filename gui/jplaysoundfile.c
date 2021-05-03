/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JPLAYSOUNDFILE_C
#define JPLAYSOUNDFILE_C

/**
jplaysoundfile  :  filename  ->
Play a sound file.
*/
void do_jplaysoundfile(void)
{
    char *filename;

    COMPILE;
    filename = (char *)do_pop();
    j_playsoundfile(filename);
}
#endif

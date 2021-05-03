/*
    module  : jloadimage.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JLOADIMAGE_C
#define JLOADIMAGE_C

/**
jloadimage  :  filename  ->  event
Loads the image from file filename and returns its event number. The file
could be of the following format: GIF, JPEG, BMP, PPM.
*/
void do_jloadimage(void)
{
    int temp;
    char *filename;

    COMPILE;
    filename = (char *)do_pop();
    temp = j_loadimage(filename);
    do_push(temp);
}
#endif

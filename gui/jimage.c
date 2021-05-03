/*
    module  : jimage.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JIMAGE_C
#define JIMAGE_C

/**
jimage  :  width height  ->  event
Creates a new (memory) image component with the given width and height and
returns its event number. On error -1 will be returned.
*/
void do_jimage(void)
{
    int width, height, temp;

    COMPILE;
    height = do_pop();
    width = do_pop();
    temp = j_image(width, height);
    do_push(temp);
}
#endif

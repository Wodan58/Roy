/*
    module  : jsetimage.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETIMAGE_C
#define JSETIMAGE_C

/**
jsetimage  :  obj image  ->
Sets the image to be displayed in obj.
*/
void do_jsetimage(void)
{
    int obj, image;

    COMPILE;
    image = do_pop();
    obj = do_pop();
    j_setimage(obj, image);
}
#endif

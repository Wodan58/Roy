/*
    module  : jdrawimage.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWIMAGE_C
#define JDRAWIMAGE_C

/**
jdrawimage  :  obj image x y  ->
Copies the image, given by its eventnumber image, to position (x, y).
*/
void do_jdrawimage(void)
{
    int obj, image, x, y;

    COMPILE;
    y = do_pop();
    x = do_pop();
    image = do_pop();
    obj = do_pop();
    j_drawimage(obj, image, x, y);
}
#endif

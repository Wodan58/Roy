/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETSCALEDIMAGE_C
#define JGETSCALEDIMAGE_C

/**
jgetscaledimage  :  obj x y sw sh tw th  ->  status
Copy the contents of the rectangular area defined by x, y, width sw, and height
sh into an image and return its event number. The image will be scaled to
target width tw and target height th.
*/
void do_jgetscaledimage(void)
{
    int obj, x, y, sw, sh, tw, th, temp;

    COMPILE;
    th = do_pop();
    tw = do_pop();
    sh = do_pop();
    sw = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    temp = j_getscaledimage(obj, x, y, sw, sh, tw, th);
    do_push(temp);
}
#endif

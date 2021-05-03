/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWSCALEDIMAGE_C
#define JDRAWSCALEDIMAGE_C

/**
jdrawscaledimage  :  obj image sx sy sw sh tx ty tw th  ->
Copy the contents of the rectangular area defined by x, y, width sw and height
sh of the image to position (tx, ty). The area will be scaled to target width
tw and target height th.
*/
void do_jdrawscaledimage(void)
{
    int obj, image, sx, sy, sw, sh, tx, ty, tw, th;

    COMPILE;
    th = do_pop();
    tw = do_pop();
    ty = do_pop();
    tx = do_pop();
    sh = do_pop();
    sw = do_pop();
    sy = do_pop();
    sx = do_pop();
    image = do_pop();
    obj = do_pop();
    j_drawscaledimage(obj, image, sx, sy, sw, sh, tx, ty, tw, th);
}
#endif

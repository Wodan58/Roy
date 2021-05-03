/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETIMAGESOURCE_C
#define JGETIMAGESOURCE_C

/**
jgetimagesource  :  obj x y w h  ->  r g b
Returns an image of the specified size (x, y, width, height) of component. The
red, green, and blue values of each picture will be stored in r, g, b.
*/
PRIVATE void do_jgetimagesource(void)
{
    int obj, x, y, w, h, *r, *g, *b;

    COMPILE;
    h = do_pop();
    w = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    r = GC_malloc_atomic(w * h * sizeof(int));
    g = GC_malloc_atomic(w * h * sizeof(int));
    b = GC_malloc_atomic(w * h * sizeof(int));
    j_getimagesource(obj, x, y, w, h, r, g, b);
    do_push((intptr_t)r);
    do_push((intptr_t)g);
    do_push((intptr_t)b);
}
#endif

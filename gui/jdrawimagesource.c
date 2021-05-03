/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWIMAGESOURCE_C
#define JDRAWIMAGESOURCE_C

int *VectorToArray(Stack *cur)
{
    int *ptr;
    int i, leng;

    leng = vec_size(cur);
    ptr = GC_malloc_atomic(leng * sizeof(int));
    for (i = 0; i < leng; i++)
	ptr[i] = vec_at(cur, i);
    return ptr;
}

/**
jdrawimagesource  :  obj x y w h r g b  ->
Paints an image at Position (x, y), with width and height. The red, green, and
blue values of each pixel are given by the arrays r, g, b.
*/
PRIVATE void do_jdrawimagesource(void)
{
    Stack *temp;
    int obj, x, y, w, h, *r, *g, *b;

    COMPILE;
    temp = (Stack *)do_pop();
    b = VectorToArray(temp);
    temp = (Stack *)do_pop();
    g = VectorToArray(temp);
    temp = (Stack *)do_pop();
    r = VectorToArray(temp);
    h = do_pop();
    w = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_drawimagesource(obj, x, y, w, h, r, g, b);
}
#endif

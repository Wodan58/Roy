/*
    module  : jgetimage.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETIMAGE_C
#define JGETIMAGE_C

/**
jgetimage  :  obj  ->  event
Copy the contents of component obj into an image and return its event number.
*/
void do_jgetimage(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getimage(obj);
    do_push(temp);
}
#endif

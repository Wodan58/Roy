/*
    module  : jsaveimage.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSAVEIMAGE_C
#define JSAVEIMAGE_C

/**
jsaveimage  :  obj filename image  ->  status
Save the components image to file filename. The specified file format can be:
J_BMP: Win32 Bitmap Format; J_PPM: Portable pixmap.
*/
void do_jsaveimage(void)
{
    char *filename;
    int obj, image, temp;

    COMPILE;
    image = do_pop();
    filename = (char *)do_pop();
    obj = do_pop();
    temp = j_saveimage(obj, filename, image);
    do_push(temp);
}
#endif

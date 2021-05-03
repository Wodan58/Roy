/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGRAPHICBUTTON_C
#define JGRAPHICBUTTON_C

/**
jgraphicbutton  :  obj filename  ->  event
Creates a new graphicbutton component with the image loaded from filename and
returns its event number.
*/
void do_jgraphicbutton(void)
{
    int obj, temp;
    char *filename;

    COMPILE;
    filename = (char *)do_pop();
    obj = do_pop();
    temp = j_graphicbutton(obj, filename);
    do_push(temp);
}
#endif

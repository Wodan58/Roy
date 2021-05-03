/*
    module  : jgraphiclabel.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGRAPHICLABEL_C
#define JGRAPHICLABEL_C

/**
jgraphiclabel  :  obj filename  ->  event
Creates a new graphic label component with the image loaded from filename and
returns its event number.
*/
void do_jgraphiclabel(void)
{
    int obj, temp;
    char *filename;

    COMPILE;
    filename = (char *)do_pop();
    obj = do_pop();
    temp = j_graphiclabel(obj, filename);
    do_push(temp);
}
#endif

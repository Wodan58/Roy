/*
    module  : jline.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JLINE_C
#define JLINE_C

/**
jline  :  obj orient style length  ->  event
Creates a new line component with the specified length and returns its event
number. A line may be used to separate groups of components. On error -1 will
be returned. The parameter orient specifies the orientation of the line:
J_HORIZONTAL: horizontal line; J_VERTICAL: vertical line. The parameter style
specifies the line style: J_LINEDOWN: etched-in line style; J_LINEUP:
etched-out line style.
*/
void do_jline(void)
{
    int obj, orient, style, length, temp;

    COMPILE;
    length = do_pop();
    style = do_pop();
    orient = do_pop();
    obj = do_pop();
    temp = j_line(obj, orient, style, length);
    do_push(temp);
}
#endif

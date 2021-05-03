/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETMOUSEBUTTON_C
#define JGETMOUSEBUTTON_C

/**
jgetmousebutton  :  mouselistener  ->  button
Return the mousebutton that was last used. The return value is: J_LEFT: left
mousebutton; J_CENTER: middle mousebutton; J_RIGHT: right mousebutton.
*/
void do_jgetmousebutton(void)
{
    int mouselistener, temp;

    COMPILE;
    mouselistener = do_pop();
    temp = j_getmousebutton(mouselistener);
    do_push(temp);
}
#endif

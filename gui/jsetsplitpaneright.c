/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETSPLITPANERIGHT_C
#define JSETSPLITPANERIGHT_C

/**
jsetsplitpaneright  :  frame text  ->
Create a split pane with title text.
*/
void do_jsetsplitpaneright(void)
{
    int frame, text;

    COMPILE;
    text = do_pop();
    frame = do_pop();
    j_setsplitpaneright(frame, text);
}
#endif

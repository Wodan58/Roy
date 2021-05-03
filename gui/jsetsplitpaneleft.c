/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETSPLITPANELEFT_C
#define JSETSPLITPANELEFT_C

/**
jsetsplitpaneleft  :  frame title  ->
Create a split pane with title text.
*/
void do_jsetsplitpaneleft(void)
{
    int frame, title;

    COMPILE;
    title = do_pop();
    frame = do_pop();
    j_setsplitpaneleft(frame, title);
}
#endif

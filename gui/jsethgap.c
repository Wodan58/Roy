/*
    module  : jsethgap.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETHGAP_C
#define JSETHGAP_C

/**
jsethgap  :  obj hgap  ->
Sets the horizontal gap between components to hgap pixels.
*/
void do_jsethgap(void)
{
    int obj, hgap;

    COMPILE;
    hgap = do_pop();
    obj = do_pop();
    j_sethgap(obj, hgap);
}
#endif

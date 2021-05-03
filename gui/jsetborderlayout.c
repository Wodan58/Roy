/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETBORDERLAYOUT_C
#define JSETBORDERLAYOUT_C

/**
jsetborderlayout  :  obj  ->
Adds a borderlayout manager to component obj.
*/
void do_jsetborderlayout(void)
{
    int obj;

    COMPILE;
    j_setborderlayout(obj);
}
#endif

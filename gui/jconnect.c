/*
    module  : jconnect.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JCONNECT_C
#define JCONNECT_C

/**
jconnect  :  hostname  ->  status
Connects a running JAPI kernel on host hostname.
*/
PRIVATE void do_jconnect(void)
{
    int temp;
    char *hostname;

    COMPILE;
    hostname = (char *)do_pop();
    temp = j_connect(hostname);
    do_push(temp);
}
#endif

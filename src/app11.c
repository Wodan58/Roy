/*
    module  : app11.c
    version : 1.11
    date    : 09/19/23
*/
#ifndef APP11_C
#define APP11_C

/**
OK 2450  app11  :  DDDA	X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
void app11_(pEnv env)
{
    PARM(3, DIP);
    app1_(env);
    popd_(env);
}
#endif

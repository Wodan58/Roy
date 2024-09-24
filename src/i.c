/*
    module  : i.c
    version : 1.14
    date    : 09/18/24
*/
#ifndef I_C
#define I_C

/**
OK  2410  i  :  DP  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
void i_(pEnv env)
{
    Node node;

    PARM(1, DIP);
    node = vec_pop(env->stck);
    exeterm(env, node.u.lis);
}
#endif

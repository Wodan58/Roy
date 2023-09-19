/*
    module  : i.c
    version : 1.12
    date    : 09/19/23
*/
#ifndef I_C
#define I_C

/**
OK 2410  i  :  DP	[P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
PRIVATE void i_(pEnv env)
{
    Node node;

    PARM(1, DIP);
    node = lst_pop(env->stck);
    exeterm(env, node.u.lis);
}
#endif

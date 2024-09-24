/*
    module  : x.c
    version : 1.13
    date    : 09/18/24
*/
#ifndef X_C
#define X_C

/**
OK  2420  x  :  P  [P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
void x_(pEnv env)
{
    Node node;

    PARM(1, DIP);
    node = vec_back(env->stck);
    exeterm(env, node.u.lis);
}
#endif

/*
    module  : string.c
    version : 1.12
    date    : 10/02/23
*/
#ifndef STRING_C
#define STRING_C

/**
OK 2350  string  :  DA	X  ->  B
Tests whether X is a string.
*/
void string_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op == STRING_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif

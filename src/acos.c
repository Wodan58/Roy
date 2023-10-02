/*
    module  : acos.c
    version : 1.10
    date    : 10/02/23
*/
#ifndef ACOS_C
#define ACOS_C

/**
OK 1490  acos  :  DA	F  ->  G
G is the arc cosine of F.
*/
void acos_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = acos(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif

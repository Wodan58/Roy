/*
    module  : neg.c
    version : 1.11
    date    : 10/02/23
*/
#ifndef NEG_C
#define NEG_C

/**
OK 1450  neg  :  DA	I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
void neg_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    if (node.op == FLOAT_)
	node.u.dbl = -node.u.dbl;
    else
	node.u.num = -node.u.num;
    env->stck = pvec_add(env->stck, node);
}
#endif

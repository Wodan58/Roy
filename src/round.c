/*
    module  : round.c
    version : 1.11
    date    : 10/02/23
*/
#ifndef ROUND_C
#define ROUND_C

/**
OK 3230  round  :  DA	F  ->  G
[EXT] G is F rounded to the nearest integer.
*/
double round2(double num)
{
    if (num < 0)
	return -floor(-num + 0.5);
    return floor(num + 0.5);
}

void round_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = round2(node.op == FLOAT_ ? node.u.dbl : node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif

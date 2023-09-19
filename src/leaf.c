/*
    module  : leaf.c
    version : 1.10
    date    : 09/19/23
*/
#ifndef LEAF_C
#define LEAF_C

/**
OK 2370  leaf  :  DA	X  ->  B
Tests whether X is not a list.
*/
void leaf_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    node.u.num = node.op != LIST_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif

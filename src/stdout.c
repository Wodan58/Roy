/*
    module  : stdout.c
    version : 1.10
    date    : 09/19/23
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
OK 1180  stdout  :  A	->  S
Pushes the standard output stream.
*/
void stdout_(pEnv env)
{
    Node node;

    node.u.fil = stdout;
    node.op = FILE_;
    lst_push(env->stck, node);
}
#endif

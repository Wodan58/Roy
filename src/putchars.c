/*
    module  : putchars.c
    version : 1.13
    date    : 09/19/23
*/
#ifndef PUTCHARS_C
#define PUTCHARS_C

/**
OK 3100  putchars  :  D	"abc.."  ->
Writes abc.. (without quotes)
*/
void putchars_(pEnv env)
{
    Node node;

    PARM(1, STRTOD);
    node = lst_pop(env->stck);
    printf("%s", node.u.str);
}
#endif

/*
    module  : fputchars.c
    version : 1.12
    date    : 10/02/23
*/
#ifndef FPUTCHARS_C
#define FPUTCHARS_C

/**
OK 1960  fputchars  :  D 	S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
void fputchars_(pEnv env) /* suggested by Heiko Kuhrt, as "fputstring_" */
{
    Node node, elem;

    PARM(2, FPUTCHARS);
    env->stck = pvec_pop(env->stck, &elem);
    node = pvec_lst(env->stck);
    fprintf(node.u.fil, "%s", elem.u.str);
}
#endif

/*
 * generated Thu Sep 19 13:21:28 2024
 */
#include "globals.h"
#include "prim.h"

#define PARM(n, m)

Node N2[] = {
    { .u.proc=plus_, .op=ANON_FUNCT_ },
};

Node N3[] = {
    { .u.proc=pred_, .op=ANON_FUNCT_ },
    { .u.proc=dup_, .op=ANON_FUNCT_ },
    { .u.proc=pred_, .op=ANON_FUNCT_ },
};

Node N5[] = {
    { .u.proc=small_, .op=ANON_FUNCT_ },
    { .u.proc=dup_, .op=ANON_FUNCT_ },
};

void L1(pEnv env)
{
    Node node;
    NodeList list;

    vec_init(list);
    list->n = 2;
    list->c = N5;
    node.u.lis=list;
    node.op=LIST_;
    vec_push(env->stck, node);

    vec_init(list);
    node.u.lis=list;
    node.op=LIST_;
    vec_push(env->stck, node);

    vec_init(list);
    list->n = 3;
    list->c = N3;
    node.u.lis=list;
    node.op=LIST_;
    vec_push(env->stck, node);

    vec_init(list);
    list->n = 1;
    list->c = N2;
    node.u.lis=list;
    node.op=LIST_;
    vec_push(env->stck, node);

    binrec_(env);
}

void joy(pEnv env)
{
    Node node;

    node.u.num=10;
    node.op=INTEGER_;
    vec_push(env->stck, node);
    L1(env);
}

#include "defs.h"

#undef SMALL_C
#undef PRED_C
#undef PLUS_C
#undef DUP_C
#undef BINREC_C
#undef POP_C

table_t yytable[] = {
    { small_, "small_" },
    { pred_, "pred_" },
    { plus_, "plus_" },
    { dup_, "dup_" },
    { binrec_, "binrec_" },
    { 0 }
};

#include "deps.h"
#include "prim.c"

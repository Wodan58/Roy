/*
 * generated Thu Apr  4 10:53:48 2024
 */
#include "globals.h"
#include "prim.h"

#define PARM(n, m)

Operator L2_b[] = {
    ANON_FUNCT_,
};
YYSTYPE L2_a[] = {
    { .proc=plus_ },
};
NodeList L2 = { .n=1, .a=L2_a, .b=L2_b };
Operator L3_b[] = {
    ANON_FUNCT_,
    ANON_FUNCT_,
    ANON_FUNCT_,
};
YYSTYPE L3_a[] = {
    { .proc=pred_ },
    { .proc=dup_ },
    { .proc=pred_ },
};
NodeList L3 = { .n=3, .a=L3_a, .b=L3_b };
Operator L4_b[] = {
    ANON_FUNCT_,
    ANON_FUNCT_,
};
YYSTYPE L4_a[] = {
    { .proc=small_ },
    { .proc=dup_ },
};
NodeList L4 = { .n=2, .a=L4_a, .b=L4_b };

int yyparse(pEnv env)
{
    Node node;
    node.u.num=40;
    node.op=INTEGER_;
    env->stck = pvec_add(env->stck, node);
    node.u.lis=&L4;
    node.op=LIST_;
    env->stck = pvec_add(env->stck, node);
    node.u.lis=0;
    node.op=LIST_;
    env->stck = pvec_add(env->stck, node);
    node.u.lis=&L3;
    node.op=LIST_;
    env->stck = pvec_add(env->stck, node);
    node.u.lis=&L2;
    node.op=LIST_;
    env->stck = pvec_add(env->stck, node);
    binrec_(env);
    execute(env, 0);
    return 0;
}

#include "defs.h"

#undef SMALL_C
#undef PRED_C
#undef PLUS_C
#undef DUP_C
#undef BINREC_C

table_t yytable[] = {
{ small_, "small_" },
{ pred_, "pred_" },
{ plus_, "plus_" },
{ dup_, "dup_" },
{ binrec_, "binrec_" },
{ 0 } };

#include "deps.h"
#include "prim.c"

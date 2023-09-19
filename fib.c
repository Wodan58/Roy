/*
 * generated Tue Sep 19 18:03:14 2023
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
Operator L1_b[] = {
    ANON_FUNCT_,
    LIST_,
    LIST_,
    LIST_,
    LIST_,
    INTEGER_,
};
YYSTYPE L1_a[] = {
    { .proc=binrec_ },
    { .lis=&L2 },
    { .lis=&L3 },
    { .lis=0 },
    { .lis=&L4 },
    { .num=40 },
};
NodeList L1 = { .n=6, .a=L1_a, .b=L1_b };

int yyparse(pEnv env)
{
    static unsigned char init;
    if (init) return 0; init = 1;
    execute(env, &L1);
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

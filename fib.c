/*
 * generated Fri Oct 11 15:34:10 2024
 */
#include "globals.h"
#define PARM(n, m)
#include "builtin.h"

void binrec_1(pEnv env);
void joy(pEnv env)
{
NULLARY(INTEGER_NEWNODE, 10);
binrec_1(env);
/* JOY */
}

void binrec_1(pEnv env)
{	/* BINREC */
    Node node;

dup_(env);
small_(env);
    node = vec_pop(env->stck);
    if (node.u.num) {
    } else {
pred_(env);
dup_(env);
pred_(env);
	node = vec_pop(env->stck);
	binrec_1(env);
	vec_push(env->stck, node);
	binrec_1(env);
plus_(env);
    }
}	/* BINREC */
#include "defines.h"

#undef DUP_C
#undef PLUS_C
#undef PRED_C
#undef SMALL_C

table_t yytable[] = {
{ dup_, "dup" },
{ plus_, "+" },
{ pred_, "pred" },
{ small_, "small" },
{ 0 }
};

#include "builtin.c"

/*
    module  : pred.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef PRED_C
#define PRED_C

/**
pred  :  M  ->  N
Numeric N is the predecessor of numeric M.
*/
void do_pred(void)
{
    UNARY;
    --stack[-1];
}
#endif

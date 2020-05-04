/*
    module  : sametype.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef SAMETYPE_C
#define SAMETYPE_C

#define IS_LIST		1
#define IS_FLOAT	2
#define IS_STRING	3
#define IS_INTEGER	4

/**
sametype  :  X Y  ->  B
Tests whether X and Y have the same type.
*/
void do_sametype(void)
{
    intptr_t temp;
    int type1, type2;

    BINARY;
    temp = do_pop();
    if (is_list(temp))
	type2 = IS_LIST;
    else if (is_float(temp))
	type2 = IS_FLOAT;
    else if (is_string(temp))
	type2 = IS_STRING;
    else
	type2 = IS_INTEGER;
    if (is_list(stack[-1]))
	type1 = IS_LIST;
    else if (is_float(stack[-1]))
	type1 = IS_FLOAT;
    else if (is_string(stack[-1]))
	type1 = IS_STRING;
    else
	type1 = IS_INTEGER;
    stack[-1] = type1 == type2;
}
#endif

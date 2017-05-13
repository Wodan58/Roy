/*
    module  : memory.c
    version : 1.2
    date    : 05/13/17
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gc.h"
#include "parse.h"
#include "node.h"

#ifndef MAXMEM
#define MAXMEM	500
#endif

int definition;

static int memptr;
static node_t memory[MAXMEM];

node_t *mem_alloc()
{
    node_t *cur;

    if (!definition && memptr < MAXMEM)
	return &memory[memptr++];
    cur = malloc(sizeof(node_t));
    memset(cur, 0, sizeof(node_t));
    return cur;
}

void mem_free()
{
    memset(memory, 0, memptr * sizeof(node_t));
    memptr = 0;
}

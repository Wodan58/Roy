/*
    module  : memory.c
    version : 1.4
    date    : 07/22/18
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "parse.h"

#ifndef MAXMEM
#define MAXMEM		500
#endif

int definition;

static int memptr;
static node_t memory[MAXMEM];

node_t *mem_alloc(void)
{
    if (!definition && memptr < MAXMEM)
	return &memory[memptr++];
    return calloc(1, sizeof(node_t));
}

void mem_free(void)
{
    memset(memory, 0, memptr * sizeof(node_t));
    memptr = 0;
}

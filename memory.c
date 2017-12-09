/*
    module  : memory.c
    version : 1.2
    date    : 12/09/17
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "joygc.h"
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
    if (!definition && memptr < MAXMEM)
	return &memory[memptr++];
    return GC_malloc(sizeof(node_t));
}

void mem_free()
{
    memset(memory, 0, memptr * sizeof(node_t));
    memptr = 0;
}

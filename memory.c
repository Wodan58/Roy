/*
    module  : memory.c
    version : 1.1
    date    : 08/30/16
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"
#include "parse.h"
#include "node.h"

#ifndef MAXMEM
#define MAXMEM	500
#endif

int definition;

int memptr;
node_t memory[MAXMEM];

node_t *mem_alloc()
{
    if (!definition && memptr < MAXMEM)
	return &memory[memptr++];
    return calloc(sizeof(node_t), 1);    
}

void mem_free()
{
    memset(memory, 0, memptr * sizeof(node_t));
    memptr = 0;
}

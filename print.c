/*
    module  : print.c
    version : 1.10
    date    : 07/19/19
*/
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <mach-o/getsect.h>
#endif
#include <inttypes.h>
#include "stack.h"

#ifdef _MSC_VER
#define DOWN_64K	~0xFFFF
#define PEPOINTER	15
#define IMAGE_BASE	13
#define BASE_OF_CODE	11
#define SIZE_OF_CODE	7
#define SIZE_OF_DATA	8
#define SIZE_OF_BSS	9
#endif

extern int g_argc;
extern char **g_argv;

void writefactor(intptr_t Value);

static intptr_t start_of_text,
	        start_of_data,
		start_of_bss,
		start_of_heap;

int is_boolean(intptr_t Value)
{
    return !Value || Value == 1;
}

int is_char(intptr_t Value)
{
    return Value >= ' ' && Value <= '~';
}

int is_integer(intptr_t Value)
{
    return Value >= 0 && Value <= SMALLINT;
}

int is_code(intptr_t Value)
{
    return Value > start_of_text && Value < start_of_data;
}

int is_string(intptr_t Value)
{
    int i;

    for (i = 0; i < g_argc; i++)
	if (Value == (intptr_t)g_argv[i])
	    return 1;
    return (Value > start_of_data && Value < start_of_bss) ||
	   (Value > start_of_heap && (Value & ~JLAP_INVALID));
}

int is_list(intptr_t Value)
{
    return Value > start_of_heap && !(Value & ~JLAP_INVALID);
}

void init_heap(void)
{
    int *ptr;
    extern int main();

#ifdef __linux__
    extern char etext, edata, end;

    start_of_data = (intptr_t)&etext;
    start_of_bss  = (intptr_t)&edata;
    start_of_heap = (intptr_t)&end;
#endif
#ifdef __APPLE__
    start_of_data = (intptr_t)get_etext();
    start_of_bss  = (intptr_t)get_edata();
    start_of_heap = (intptr_t)get_end();
#endif
#if !defined(__linux__) && !defined(__APPLE__) && !defined(_MSC_VER)
    start_of_text = (intptr_t)main;
    if ((ptr = malloc(1)) != 0)
	start_of_data = start_of_bss = start_of_heap = (intptr_t)ptr;
#endif
#ifdef _MSC_VER
    start_of_text &= DOWN_64K;
    ptr = (int *)start;
    ptr += ptr[PEPOINTER] / 4;
    start_of_text = ptr[IMAGE_BASE] + ptr[BASE_OF_CODE];
    start_of_data = start_of_text + ptr[SIZE_OF_CODE];
    start_of_bss  = start_of_data + ptr[SIZE_OF_DATA];
    start_of_heap = start_of_bss + ptr[SIZE_OF_BSS];
#endif
    setbuf(stdout, 0);
}

void writeterm(Stack *List, int i)
{
    if (!List)
	return;
    if (i == -1)
	i += vec_size(List);
    for (; i >= 0; i--) {
	writefactor(vec_at(List, i));
	if (i)
	    putchar(' ');
    }
}

int writeproc(intptr_t Value)
{
    int i;
    void (*proc)(void);

    proc = (void (*)(void))(Value & ~JLAP_INVALID);
    for (i = 0; table[i].proc; i++)
	if (proc == table[i].proc) {
	    printf("%s", table[i].name);
	    return 1;
	}
    return 0;
}

void writefactor(intptr_t Value)
{
    int i;

    for (i = 0; i < g_argc; i++)
	if (Value == (intptr_t)g_argv[i]) {
	    printf("%s", g_argv[i]);
	    return;
	}
    if (Value >= 0 && Value <= SMALLINT)
	printf("%" PRIdPTR, Value);
#if !defined(__linux__) && !defined(__APPLE__) && !defined(_MSC_VER)
    else if (Value > start_of_text && Value < start_of_heap) {
	if (!writeproc(Value))
	    printf("%s", (char *)Value);
#else
    else if (Value > start_of_data && Value < start_of_bss)
	printf("%s", (char *)Value);
    else if (Value > start_of_text && Value < start_of_data) {
	if (!writeproc(Value))
	    printf("%" PRIdPTR, Value);
#endif
    } else if ((Value & JLAP_INVALID) == 0) {
	printf("[");
	writeterm((Stack *)Value, -1);
	printf("]");
    } else
	printf("%s", (char *)(Value & ~JLAP_INVALID));
}

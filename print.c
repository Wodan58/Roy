/*
    module  : print.c
    version : 1.15
    date    : 01/19/20
*/
#include <stdio.h>
#include <string.h>
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

extern YYTABLE yytable[];

real_t unpack(intptr_t num);		/* builtin.c */

void writefactor(intptr_t Value);	/* print.c */

static intptr_t start_of_text,
	        start_of_data,
		start_of_bss,
		start_of_heap;

int is_set(intptr_t Value)
{
    return Value >= MIN_INT && Value <= MAX_INT;
}

int is_boolean(intptr_t Value)
{
    return !Value || Value == 1;
}

int is_char(intptr_t Value)
{
    return (Value >= ' ' && Value <= '~') || Value == '\t' || Value == '\n';
}

int is_integer(intptr_t Value)
{
    return Value >= MIN_INT && Value <= MAX_INT;
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
	   (Value > start_of_heap && (Value & JLAP_INVALID));
}

int is_float(intptr_t Value)
{
    return Value > start_of_heap && !(Value & JLAP_INVALID) &&
				     (Value & JLAP_PACKAGE);
}

int is_list(intptr_t Value)
{
    return Value > start_of_heap && !(Value & (JLAP_INVALID | JLAP_PACKAGE));
}

int is_file(intptr_t Value)
{
    return Value >= (intptr_t)stdin && Value < (intptr_t)(stdin + MAXFIL);
}

void init_heap(void)
{
    int *ptr;
    extern int main();

    start_of_text = (intptr_t)main;
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
    for (i = 0; yytable[i].proc; i++)
	if (proc == yytable[i].proc) {
	    printf("%s", yytable[i].name);
	    return 1;
	}
    return 0;
}

void (*findproc(char *name))(void)
{
    int i;

    for (i = 0; yytable[i].proc; i++)
	if (!strcmp(name, yytable[i].name))
	    return yytable[i].proc;
    return 0;
}

void writestring(char *str)
{
    putchar('"');
    while (*++str) {
	if (*str == '"' || *str == '\\' || *str == '\n')
	    putchar('\\');
	if (*str == '\n')
	    putchar('n');
	else
	    putchar(*str);
    }
    putchar('"');
}

void writefactor(intptr_t Value)
{
    int i;
    char *str;

    for (i = 0; i < g_argc; i++)
	if (Value == (intptr_t)g_argv[i]) {
	    printf("\"%s\"", g_argv[i]);
	    return;
	}
    if (Value >= MIN_INT && Value <= MAX_INT)
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
    } else if (Value & JLAP_INVALID) {
	str = (char *)(Value & ~JLAP_INVALID);
	if (*str == '"')
	    writestring(str);
	else
	    printf("%s", str);
    } else if (Value & JLAP_PACKAGE)
	printf("%g", unpack(Value));
    else if (is_file(Value)) {
	if (Value == (intptr_t)stdin)
	    printf("file:stdin");
	else if (Value == (intptr_t)stdout)
	    printf("file:stdout");
	else if (Value == (intptr_t)stderr)
	    printf("file:stderr");
	else
	    printf("file:%p", (void *)Value);
    } else {
	printf("[");
	writeterm((Stack *)Value, -1);
	printf("]");
    }
}

/*
    module  : print.c
    version : 1.19
    date    : 11/30/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <mach-o/getsect.h>
#endif
#include <inttypes.h>
#include "stack.h"
#include "parse.h"

#ifdef _MSC_VER
#define DOWN_64K	~0xFFFF
#define PEPOINTER	15
#define IMAGE_BASE	13
#define BASE_OF_CODE	11
#define SIZE_OF_CODE	7
#define SIZE_OF_DATA	8
#define SIZE_OF_BSS	9
#endif

real_t unpack(intptr_t num);		/* builtin.c */
char *procname(intptr_t Value);

int main();				/* main.c */

void writefactor(intptr_t Value);	/* print.c */

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
    return (Value >= ' ' && Value <= '~') || Value == '\t' || Value == '\n';
}

int is_integer(intptr_t Value)
{
    return Value >= MIN_INT && Value <= MAX_INT;
}

int is_set(intptr_t Value)
{
    return Value >= MIN_INT && Value <= MAX_INT;
}

int is_file(intptr_t Value)
{
    return Value >= (intptr_t)stdin && Value < (intptr_t)(stdin + MAXFIL);
}

int is_code(intptr_t Value)
{
    return Value > start_of_text && Value < start_of_data;
}

int is_usr(intptr_t Value)
{
    int i;

    for (i = 0; i < g_argc; i++)
	if (Value == (intptr_t)g_argv[i])
	    return 1;
    return Value > start_of_data && Value < start_of_bss;
}

int is_string(intptr_t Value)
{
    return Value > start_of_heap && (Value & JLAP_INVALID);
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

int get_type(intptr_t temp)
{
    int type;

    if (is_boolean(temp))
	type = BOOLEAN_;	// 4
    else if (is_char(temp))
	type = CHAR_;		// 5
    else if (is_integer(temp))
	type = INTEGER_;	// 6, or SET_, 7
    else if (is_file(temp))
	type = FILE_;		// 11
    else if (is_code(temp))
	type = ANON_FUNCT_;	// 3
    else if (is_usr(temp))
	type = USR_;		// 2
    else if (is_string(temp))
	type = STRING_;		// 8
    else if (is_float(temp))
	type = FLOAT_;		// 10
    else if (is_list(temp))
	type = LIST_;		// 9
    else
	type = UNKNOWN_;	// 1
    return type;
}

void init_heap(void)
{
    int *ptr;

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
    ptr = (int *)start_of_text;
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
    char *name;

    if ((name = procname(Value)) != 0) {
	printf("%s", name);
	return 1;
    }
    return 0;
}

void writestring(FILE *fp, char *str)
{
    fputc('"', fp);
    while (*++str) {
	if (*str == '"' || *str == '\\' || *str == '\n')
	    fputc('\\', fp);
	if (*str == '\n')
	    fputc('n', fp);
	else
	    fputc(*str, fp);
    }
    fputc('"', fp);
}

void writefactor(intptr_t Value)
{
    char *str;

    switch (get_type(Value)) {
    case USR_:
	printf("%s", (char *)Value);
	break;
    case ANON_FUNCT_:
	if (writeproc(Value))
	    return;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	printf("%" PRIdPTR, Value);
	break;
    case FILE_:
	if (Value == (intptr_t)stdin)
	    printf("file:stdin");
	else if (Value == (intptr_t)stdout)
	    printf("file:stdout");
	else if (Value == (intptr_t)stderr)
	    printf("file:stderr");
	else
	    printf("file:%p", (void *)Value);
	break;
    case STRING_:
	str = (char *)(Value & ~JLAP_INVALID);
	if (*str == '"')
	    writestring(stdout, str);
	else
	    printf("%s", str);
	break;
    case FLOAT_:
	printf("%g", unpack(Value));
	break;
    case LIST_:
	printf("[");
	writeterm((Stack *)Value, -1);
	printf("]");
	break;
    default:
	break;
    }
}

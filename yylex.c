/*
    module  : yylex.c
    version : 1.9
    date    : 07/08/19
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"
#include "parse.h"

int getch(void)
{
    int ch;

    if ((ch = getchar()) == EOF)
	exit(0);
    return ch;
}

int yylex(void)
{
    int ch, i = 0;
    char str[MAXSTR];

start:
    while ((ch = getch()) <= ' ')
	;
    switch (ch) {
    case '#':
	while ((ch = getch()) != '\n')
	    ;
	goto start;
    case '.':
    case ';':
    case '[':
    case ']':
	return ch;
    case '\'':
	if ((ch = getch()) == '\\') {
	    ch = 10 * (getch() - '0');
	    ch += getch() - '0';
	    ch *= 10;
	    ch += getch() - '0';
	}
	yylval.num = ch;
	return Char;
    case '-':
	str[i++] = ch;
	if ((ch = getch()) == '_' || isalpha(ch))
	    goto symbol1;
	if (!isdigit(ch))
	    goto symbol2;
	/* continue */
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
	do {
	    if (i < MAXSTR - 1)
		str[i++] = ch;
	    ch = getch();
	} while (isdigit(ch));
	ungetc(ch, stdin);
	str[i] = '\0';
	yylval.num = atoi(str);
	return Int;
    default:
symbol1:
	do {
	    if (i < MAXSTR - 1)
		str[i++] = ch;
	    ch = getch();
	} while (isalnum(ch) || ch == '_' || (i == 1 && strchr("=>", ch)));
symbol2:
	ungetc(ch, stdin);
	str[i] = '\0';
	if (!strcmp(str, "=="))
	    return EQUAL;
	if (!strcmp(str, "DEFINE"))
	    return PUBLIC;
	if (!strcmp(str, "true")) {
	    yylval.num = 1;
	    return Boolean;
	}
	if (!strcmp(str, "false")) {
	    yylval.num = 0;
	    return Boolean;
	}
	yylval.str = (char *)((intptr_t)GC_strdup(str) | JLAP_INVALID);
	return Symbol;
    }
}

void yyerror(char *str)
{
    fprintf(stderr, "ERROR: %s\n", str);
    exit(1);
}

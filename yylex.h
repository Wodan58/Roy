/*
    module  : yylex.h
    version : 1.3
    date    : 06/21/22
*/
#ifndef YYLEX_H
#define YYLEX_H

void include(char *filnam, int err);
int yywrap(void);
int yylex(void);
int getechoflag(void);
void setechoflag(int flag);
int yyerror(char *str);
#endif

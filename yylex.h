/*
    module  : yylex.h
    version : 1.2
    date    : 11/30/20
*/
#ifndef YYLEX_H
#define YYLEX_H

void inilinebuffer(char *str);
void redirect(FILE *fp);
void include(char *filnam);
int yywrap(void);
int yylex(void);
int getechoflag(void);
void setechoflag(int flag);
int yyerror(char *str);
#endif

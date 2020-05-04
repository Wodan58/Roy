/*
    module  : yylex.h
    version : 1.1
    date    : 01/19/20
*/
void inilinebuffer(char *str);
void redirect(FILE *fp);
void include(char *filnam);
int yywrap(void);
int yylex(void);
int getechoflag(void);
void setechoflag(int flag);
int yyerror(char *str);

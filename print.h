/*
    module  : print.h
    version : 1.3
    date    : 06/21/22
*/
#ifndef PRINT_H
#define PRINT_H

int raw_type(value_t v);
int64_t raw_value(value_t v);
int get_type(value_t Value);
char *get_string(value_t Value);
char *stringify(const char *str);
void writestring(FILE *fp, char *str);
void writeterm(Stack *List, int i);
void writefactor(value_t Value);
#endif

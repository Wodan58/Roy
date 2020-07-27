/*
    module  : print.h
    version : 1.2
    date    : 06/21/20
*/
int is_boolean(intptr_t Value);
int is_char(intptr_t Value);
int is_integer(intptr_t Value);
int is_set(intptr_t Value);
int is_file(intptr_t Value);
int is_code(intptr_t Value);
int is_usr(intptr_t Value);
int is_string(intptr_t Value);
int is_float(intptr_t Value);
int is_list(intptr_t Value);
void init_heap(void);
void writeterm(Stack *List, int i);
int writeproc(intptr_t Value);
void (*findproc(char *name))(void);
void writestring(FILE *fp, char *str);
void writefactor(intptr_t Value);

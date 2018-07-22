/*
    module  : node.h
    version : 1.5
    date    : 07/22/18
*/
#include "joygc.h"
#include "vector.h"

void debug1(const char *str);

#ifdef DEBUG
#ifdef _MSC_VER
#define __func__	__FUNCTION__
#endif
#define TRACE		if (debugging) debug1(__func__)
#else
#define TRACE
#endif

#ifdef BIT_32
typedef long long_t;
#define PRINT_NUM	"%ld"
#define NUM_MAX		INT_MAX
#endif

#ifdef BIT_64
typedef long long long_t;
#define PRINT_NUM	"%lld"
#define NUM_MAX		LONG_MAX
#endif

/* symbol table structure (array) */
typedef struct symbol_t {
    char *str, *print;
    union {
	void (*proc)(void);
	struct node_t *ptr;
    };
    short type, uniq, mark, recur;
} symbol_t;

/* list structure (linked list) */
typedef struct node_t {
    union {
	int num;
	char *str;
	void (*proc)(void);
	struct node_t *ptr;
    };
    short type;
    struct node_t *next;
} node_t;

/* stack structure (array) */
typedef struct value_t {
    union {
	int num;
	char *str;
	void (*proc)(void);
	struct node_t *ptr;
    };
    short type;
} value_t;

/* declare global variables */
extern int compiling, definition, debugging;

/* declare vector type */
typedef vector(symbol_t) Table;

/* declare symbol table */
extern Table *theTable;

/* declare vector type */
typedef vector(value_t) Stack;

/* declare data stack */
extern Stack *theStack;

/* lexer.l, parse.y */
int yylex(), yyparse(), yyerror(char *str);

/* node.c */
int enterdef(char *str, node_t *ptr);
node_t *newlist(node_t *ptr);
node_t *newnode(int type, int value);
node_t *copy(node_t *ptr);
node_t *cons(value_t *node, node_t *next);
node_t *stk2lst(void);
void lst2stk(node_t *root);
node_t *reverse(node_t *cur);
void writefactor(value_t *cur);
void writeterm(node_t *cur);
void debug(node_t *cur);
void exeterm(node_t *cur);
void writestack(void);
void execute(node_t *cur);

/* eval.c */
void compile(node_t *cur);
char *lookup(void (*proc)(void));

/* memory.c */
node_t *mem_alloc(void);
void mem_free(void);

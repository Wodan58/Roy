/*
    module  : node.h
    version : 1.1
    date    : 08/30/16
*/
typedef struct node_t {
    union {
	int num;
	char *str;
	struct node_t *ptr;
	void (*fun)(void);
    };
    short type, index, uniq, mark;
    struct node_t *next;
} node_t;

extern int compiling, definition;

extern int symptr;
extern node_t symtab[];

extern int stkptr;
extern node_t stktab[];

int yylex(), yyparse(), yyerror(char *str);

void enterdef(char *str, node_t *next);
node_t *entersym(char *str);
node_t *newlist(node_t *ptr);
node_t *newnode(int type, int value);
node_t *concat(node_t *node, node_t *next);
node_t *copy(node_t *node);
node_t *reverse(node_t *cur);
void writeterm(node_t *cur);
void writefactor(node_t *cur);
void exeterm(node_t *cur);
void writestack();
void debug(node_t *cur);
void compile(node_t *cur);
node_t *alloc(node_t *node);
void table();
node_t *stk2lst();
void lst2stk(node_t *root);
void execute(node_t *cur);
node_t *mem_alloc();
void mem_free();

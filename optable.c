/*
    module  : optable.c
    version : 1.20
    date    : 06/21/22
*/
#include "joy.h"

/* clang-format off */
struct optable_t optable[] = {
        /* THESE MUST BE DEFINED IN THE ORDER OF THEIR VALUES */
{"__ILLEGAL",           do_id,  "N",    "->",
"internal error, cannot happen - supposedly.\n"},

{"__COPIED",            do_id,  "N",    "->",
"no message ever, used for gc.\n"},

{"__USR",               do_id,  "U",    "->",
"user node.\n"},

{"__ANON_FUNCT",        do_id,  "U",    "->",
"op for anonymous function call.\n"},

/* LITERALS */

{" truth value type",   do_id,  "A",    "->  B",
"The logical type, or the type of truth values.\nIt has just two literals: true and false.\n"},

{" character type",     do_id,  "A",    "->  C",
"The type of characters. Literals are written with a single quote.\nExamples:  'A  '7  ';  and so on. Unix style escapes are allowed.\n"},

{" integer type",       do_id,  "A",    "->  I",
"The type of negative, zero or positive integers.\nLiterals are written in decimal notation. Examples:  -123   0   42.\n"},

{" set type",           do_id,  "A",    "->  {...}",
"The type of sets of small non-negative integers.\nThe maximum is platform dependent, typically the range is 0..31.\nLiterals are written inside curly braces.\nExamples:  {}  {0}  {1 3 5}  {19 18 17}.\n"},

{" string type",        do_id,  "A",    "->  \"...\" ",
"The type of strings of characters. Literals are written inside double quotes.\nExamples: \"\"  \"A\"  \"hello world\" \"123\".\nUnix style escapes are accepted.\n"},

{" list type",          do_id,  "A",    "->  [...]",
"The type of lists of values of any type (including lists),\nor the type of quoted programs which may contain operators or combinators.\nLiterals of this type are written inside square brackets.\nExamples: []  [3 512 -7]  [john mary]  ['A 'C ['B]]  [dup *].\n"},

{" float type",         do_id,  "A",    "->  F",
"The type of floating-point numbers.\nLiterals of this type are written with embedded decimal points (like 1.2)\nand optional exponent specifiers (like 1.5E2).\n"},

{" file type",          do_id,  "A",    "->  FILE:",
"The type of references to open I/O streams,\ntypically but not necessarily files.\nThe only literals of this type are stdin, stdout, and stderr.\n"},

/* OPERANDS, OPERATORS, PREDICATES, COMBINATORS, AND MISCELLANEOUS */

#include "table.c"

{0, 0, "", "", ""}
};

char *opername(int o)
{
    if (o >= 0 && o < (int)(sizeof(optable) / sizeof(optable[0])))
        return optable[o].name;
    return 0;
}

void (*operproc(int o))(void)
{
    if (o >= 0 && o < (int)(sizeof(optable) / sizeof(optable[0])))
        return optable[o].proc;
    return 0;
}

char *opertype(int o)
{
    if (o >= 0 && o < (int)(sizeof(optable) / sizeof(optable[0])))
        return optable[o].arity;
    return 0;
}

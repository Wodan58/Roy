/*
    module  : runtime.h
    version : 1.1
    date    : 06/21/22
*/
#ifndef RUNTIME_H
#define RUNTIME_H

#include "joy.h"

#define STACK(n)        (stack_size() < (n))

/*
    First the list of defines that have something to do with compiling.
*/
#ifdef COMPILING
#define SYNCING         if (compiling) { fprintf(program, "stack_clear();"); }
#define COMPILE         if (compiling) { print(__func__); return; }
#define INSTANT(X)      if (compiling) { printstack(); X(prog); return; }
#else
#define SYNCING
#define COMPILE 
#define INSTANT(X)
#endif

/*
    The following list checks the types and is applicable to both COMPILING
    en RUNTIME. The error is not generated when compiling.
*/
#define ONEPARAM        if (STACK(1) || library) { \
                        execerror("one parameter", __func__); return; }
#define TWOPARAMS       if (STACK(2) || library) { \
                        execerror("two parameters", __func__); return; }
#define THREEPARAMS     if (STACK(3) || library) { \
                        execerror("three parameters", __func__); return; }
#define FOURPARAMS      if (STACK(4) || library) { \
                        execerror("four parameters", __func__); return; }
#define ONEQUOTE        if (!IS_LIST(stack[-1])) { \
                        execerror("quotation as top parameter", __func__); \
                        return; }
#define TWOQUOTES       ONEQUOTE; if (!IS_LIST(stack[-2])) { \
                        execerror("quotation as second parameter", __func__); \
                        return; }
#define THREEQUOTES     TWOQUOTES; if (!IS_LIST(stack[-3])) { \
                        execerror("quotation as third parameter", __func__); \
                        return; }
#define FOURQUOTES      THREEQUOTES; if (!IS_LIST(stack[-4])) { \
                        execerror("quotation as fourth parameter", __func__); \
                        return; }
#define SAME2TYPES      if (GET_TYPE_MASK(stack[-1]) != \
                        GET_TYPE_MASK(stack[-2])) { \
                        execerror("two parameters of the same type", __func__);\
                        return; }
#define STRING          if (!IS_USR_STRING(stack[-1])) { execerror("string", \
                        __func__); return; }
#define STRINGS2        if (!IS_USR_STRING(stack[-1]) || \
                        !IS_USR_STRING(stack[-2])) { execerror("two strings", \
                        __func__); return; }
#define INTEGER         if (!IS_INTEGER(stack[-1])) { execerror("integer", \
                        __func__); return; }
#define CHARACTER       if (!IS_CHAR(stack[-1])) { execerror("character", \
                        __func__); return; }
#define INTEGERS2       if (!IS_INTEGER(stack[-1]) || !IS_INTEGER(stack[-2])) \
                        { execerror("two integers", __func__); return; }
#define NUMERICTYPE     if (!IS_INTEGER(stack[-1]) && !IS_CHAR(stack[-1]) && \
                        !IS_BOOLEAN(stack[-1])) { execerror("numeric", \
                        __func__); return; }
#define NUMERIC         if (!IS_INTEGER(stack[-1]) && !IS_CHAR(stack[-1])) { \
                        execerror("numeric second parameter", __func__); \
                        return; }
#define NUMBER          if (!IS_NUMBER(stack[-1])) { \
                        execerror("float or integer", __func__); return; }
#define NUMBERS2        if (!IS_NUMBER(stack[-1]) || !IS_NUMBER(stack[-2])) { \
                        execerror("two floats or integers", __func__); return; }
#define FILE1           if (!IS_FILE(stack[-1]) || !GET_AS_FILE(stack[-1])) { \
                        execerror("file", __func__); return; }
#define FILE2           if (!IS_FILE(stack[-2]) || !GET_AS_FILE(stack[-2])) { \
                        execerror("file", __func__); return; }
#define CHECKZERO       if (!GET_AS_NUMBER(stack[-1])) { \
                        execerror("non-zero operand", __func__); return; }
#define LIST            if (!IS_LIST(stack[-1])) { execerror("list", __func__);\
                        return; }
#define USERDEF         if (get_type(stack[-1]) != INDEX_ && \
                        get_type(stack[-1]) != USR_) { \
                        execerror("user defined symbol", __func__); return; }
#define CHECKLIST(X)    if (!IS_LIST(X)) { execerror("internal list", \
                        __func__); return; }
#define CHECKSETMEMBER(X) \
        if ((!IS_INTEGER(X) && !IS_CHAR(X)) || GET_AS_INTEGER(X) < 0 || \
        GET_AS_INTEGER(X) >= SETSIZE_) { execerror("small numeric", __func__); \
        return; }
#define CHECKEMPTYSET(X) \
        if (!GET_AS_SET(X)) { execerror("non-empty set", __func__); return; }
#define CHECKEMPTYSTRING(X) \
        if (!*get_string(X)) { execerror("non-empty string", __func__); \
        return; }
#define CHECKEMPTYLIST(X) \
        if (!vec_size((Stack *)GET_AS_LIST(X))) { execerror("non-empty list", \
        __func__); return; }
#define CHECKSTACK      if (stack_empty()) { execerror("non-empty stack", \
                        __func__); return; }
#define CHECKFORMAT(SPEC) \
    if (!strchr("dioxX", SPEC)) \
    { execerror("one of: d i o x X", __func__); return; }
#define CHECKFORMATF(SPEC) \
    if (!strchr("eEfgG", SPEC)) \
    { execerror("one of: e E f g G", __func__); return; }
#define CHECKNUMERIC(NODE) \
    if (get_type(NODE) != INTEGER_) \
    { execerror("numeric list", __func__); return; }
#define CHECKNAME(STRING) \
    if (!STRING || *STRING) \
    { execerror("valid name", __func__); return; }
#define INDEXTOOLARGE   { execerror("smaller index", __func__); return; }
#define BADAGGREGATE    { execerror("aggregate parameter", __func__); return; }
#define BADDATA         { execerror("different type", __func__); return; }

#include "stack.c" /* allow inlining */
#endif

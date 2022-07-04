/*
    module  : nanbox2.h
    version : 1.1
    date    : 06/21/22
*/
#ifndef NANBOX2_H
#define NANBOX2_H

#include "nanbox1.h"

/*
    0000 - USR, STRING, LIST, BOOLEAN
    0001 - INDEX
    0002 - ANON_FUNCT
    0003 - FILE
    0004 - SET
    0005 - CHAR
    0006 - INTEGER
    0007 - FLOAT
         "
    FFFF - FLOAT
*/

/*
INDEX_ = 1
USR_ = 2        STRING_ = 8        STRING_ starts with "
ANON_FUNCT_ = 3
BOOLEAN_ = 4
CHAR_ = 5
INTEGER_ = 6
SET_ = 7
LIST_ = 9
FLOAT_ = 10
FILE_ = 11
*/

/*
    testers
*/
#define IS_USR_INDEX(v)         nanbox_is_index(v)
#define IS_USR_STRING(v)        nanbox_is_string(v)
#define IS_ANON_FUNCT(v)        nanbox_is_anon_funct(v)
#define IS_BOOLEAN(v)           nanbox_is_boolean(v)
#define IS_CHAR(v)              nanbox_is_char(v)
#define IS_INTEGER(v)           nanbox_is_int(v)
#define IS_SET(v)               nanbox_is_set(v)
#define IS_LIST(v)              nanbox_is_pointer(v)
#define IS_DOUBLE(v)            nanbox_is_double(v)
#define IS_FILE(v)              nanbox_is_file(v)
#define IS_NUMBER(v)            nanbox_is_number(v)

/*
    getters
*/
#define GET_AS_USR_INDEX(v)     nanbox_to_index(v)
#define GET_AS_USR_STRING(v)    nanbox_to_string(v)
#define GET_AS_ANON_FUNCT(v)    nanbox_to_anon_funct(v)
#define GET_AS_BOOLEAN(v)       nanbox_to_boolean(v)
#define GET_AS_CHAR(v)          nanbox_to_char(v)
#define GET_AS_INTEGER(v)       nanbox_to_int(v)
#define GET_AS_SET(v)           nanbox_to_set(v)
#define GET_AS_LIST(v)          nanbox_to_pointer(v)
#define GET_AS_DOUBLE(v)        nanbox_to_double(v)
#define GET_AS_FILE(v)          nanbox_to_file(v)
#define GET_AS_NUMBER(v)        nanbox_to_number(v)

/*
    setters
*/
#define MAKE_USR_INDEX(v)       nanbox_from_index(v)
#define MAKE_USR_STRING(v)      nanbox_from_string(v)
#define MAKE_ANON_FUNCT(v)      nanbox_from_anon_funct((NANBOX_POINTER_TYPE)(v))
#define MAKE_BOOLEAN(v)         nanbox_from_boolean(v)
#define MAKE_CHAR(v)            nanbox_from_char(v)
#define MAKE_INTEGER(v)         nanbox_from_int(v)
#define MAKE_SET(v)             nanbox_from_set(v)
#define MAKE_LIST(v)            nanbox_from_pointer(v)
#define MAKE_DOUBLE(v)          nanbox_from_double(v)
#define MAKE_FILE(v)            nanbox_from_file(v)

/*
    tag and payload - retrieving the payload in GET_AS_OBJECT bypasses all
                      checks. That should be ok if it is already known that
                      the payload has the correct type.
*/
#define GET_TYPE_MASK(v)        (v.as_int64 & NANBOX_HIGH16_TAG)
#define GET_AS_OBJECT(v)        (v.as_int64 & NANBOX_MASK_PAYLOAD)
#define IS_INITIAL(v)           (v.pointer == 0)
#define MK_INITIAL(v)           (v.pointer = 0)
#endif

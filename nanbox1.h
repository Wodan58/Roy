/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013 Viktor Söderqvist
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * nanbox.h
 * --------
 *
 * This file provides a way to store various types of data in a 64-bit
 * slot, including a type tag, using NaN-boxing.  NaN-boxing is a way to store
 * various information in unused NaN-space in the IEEE754 representation.  For
 * 64-bit platforms, unused bits in pointers are also used to encode various
 * information.  The representation in inspired by that used by Webkit's
 * JavaScriptCore.
 *
 * Datatypes that can be stored:
 *
 *   * int (int32_t)
 *   * double
 *   * pointer
 *   * boolean (true and false)
 *   * empty
 *
 * Any value with the top 13 bits set represents a quiet NaN.  The remaining
 * bits are called the 'payload'. NaNs produced by hardware and C-library
 * functions typically produce a payload of zero.  We assume that all quiet
 * NaNs with a non-zero payload can be used to encode whatever we want.
 */

#ifndef NANBOX_H
#define NANBOX_H

/*
 * Define this before including this file to get functions and type prefixed
 * with something other than "nanbox".
 */
#ifndef NANBOX_PREFIX
#define NANBOX_PREFIX nanbox
#endif

/* User-defined pointer type. Defaults to void*. Must be a pointer type. */
#ifndef NANBOX_POINTER_TYPE
#define NANBOX_POINTER_TYPE void*
#endif

/*
 * Macros to expand the prefix.
 */
#undef NANBOX_XXNAME
#define NANBOX_XXNAME(prefix, name) prefix ## name
#undef NANBOX_XNAME
#define NANBOX_XNAME(prefix, name) NANBOX_XXNAME(prefix, name)
#undef NANBOX_NAME
#define NANBOX_NAME(name) NANBOX_XNAME(NANBOX_PREFIX, name)

/*
 * In 64-bit mode, the pointer is unmasked.
 */
union NANBOX_NAME(_u)
{
    uint64_t as_int64;
    NANBOX_POINTER_TYPE pointer;
    double as_double;
};

#undef NANBOX_T
#define NANBOX_T NANBOX_NAME(_t)
typedef union NANBOX_NAME(_u) NANBOX_T;

/*
 * 64-bit platforms
 *
 * This range of NaN space is represented by 64-bit numbers beginning with
 * 13 bits of ones. That is, the first 16 bits are 0xFFF8 or higher.  In
 * practice, no higher value is used for NaNs.  We rely on the fact that no
 * valid double-precision numbers will be "higher" than this (compared as an
 * uint64).
 *
 * By adding 7 * 2^48 as a 64-bit integer addition, we shift the first 16 bits
 * in the doubles from the range 0000..FFF8 to the range 0007..FFFF.  Doubles
 * are decoded by reversing this operation, i.e. substracting the same number.
 *
 * The top 16-bits denote the type of the encoded nanbox_t:
 *
 *     Pointer {  0000:PPPP:PPPP:PPPP
 *             /  0001:xxxx:xxxx:xxxx
 *     Aux.   {           ...
 *             \  0005:xxxx:xxxx:xxxx
 *     Integer {  0006:0000:IIII:IIII
 *              / 0007:****:****:****
 *     Double  {          ...
 *              \ FFFF:****:****:****
 *
 * 32-bit signed integers are marked with the 16-bit tag 0x0006.
 *
 * The tags 0x0001..0x0005 can be used to store five additional types of
 * 48-bit auxiliary data, each storing up to 48 bits of payload.
 *
 * The tag 0x0000 denotes a pointer.
 */

#define NANBOX_VALUE_EMPTY      0x0llu
#define NANBOX_VALUE_STRING     0x1llu        // Strings have bit 0 set.

// Booleans have bit 1 set. True also has bit 0 set.
#define NANBOX_VALUE_FALSE      0x2llu
#define NANBOX_VALUE_TRUE       0x3llu

// This value is 7 * 2^48, used to encode doubles such that the encoded value
// will begin with a 16-bit pattern within the range 0x0007..0xFFFF.
#define NANBOX_DOUBLE_ENCODE_OFFSET     0x0007000000000000llu

// If the 16 first bits are 0x0005, this indicates a character and if they are
// 0x0006, this indicates an integer number.  Any larger value is a double, so
// we can use >= to check for either character, or integer, or double.
#define NANBOX_MIN_NUMBER       0x0006000000000000llu
#define NANBOX_HIGH16_TAG       0xffff000000000000llu

// The first 16 bits can be 0x0001 for INDEX, 0x0002 for ANON_FUNCT,
// 0x0003 for FILE, 0x0004 for CHAR, 0x0005 for SET.
#define NANBOX_POINTER          0x0000000000000000llu
#define NANBOX_INDEX            0x0001000000000000llu
#define NANBOX_ANON_FUNCT       0x0002000000000000llu
#define NANBOX_FILE             0x0003000000000000llu
#define NANBOX_SET              0x0004000000000000llu
#define NANBOX_CHAR             0x0005000000000000llu
#define NANBOX_INTEGER          0x0006000000000000llu

// NANBOX_MASK_POINTER defines the allowed non-zero bits in a pointer.
#define NANBOX_MASK_POINTER     0x0000fffffffffffcllu

// NANBOX_MASK_PAYLOAD extracts everything except the tag.
#define NANBOX_MASK_PAYLOAD     0x0000ffffffffffffllu

// NANBOX_MASK_STRING distinguishes strings from pointers and booleans.
#define NANBOX_MASK_STRING      0x0000000000000003llu

// NANBOX_MASK_BOOLEAN distinguishes booleans from pointers and strings.
#define NANBOX_MASK_BOOLEAN     0x0000000000000002llu

// NANBOX_MASK_SIGNBIT extracts the sign bit.
#define NANBOX_MASK_SIGNBIT     0x0000800000000000llu

// The 'empty' value is guaranteed to consist of a repeated single byte,
// so that it should be easy to memset an array of nanboxes to 'empty' using
// NANBOX_EMPTY_BYTE as the value for every byte.
#define NANBOX_EMPTY_BYTE       0x0

// Define bool nanbox_is_xxx(NANBOX_T val) and NANBOX_T nanbox_xxx(void)
// with empty substituted for xxx.
#define NANBOX_IMMEDIATE_VALUE_FUNCTIONS(NAME, VALUE)                          \
    static inline NANBOX_T NANBOX_NAME(_##NAME)(void) {                        \
        NANBOX_T val;                                                          \
        val.as_int64 = VALUE;                                                  \
        return val;                                                            \
    }                                                                          \
    static inline bool NANBOX_NAME(_is_##NAME)(NANBOX_T val) {                 \
        return val.as_int64 == VALUE;                                          \
    }
NANBOX_IMMEDIATE_VALUE_FUNCTIONS(empty, NANBOX_VALUE_EMPTY)
NANBOX_IMMEDIATE_VALUE_FUNCTIONS(false, NANBOX_VALUE_FALSE)
NANBOX_IMMEDIATE_VALUE_FUNCTIONS(true, NANBOX_VALUE_TRUE)

/*
 * Test whether the tag is INDEX.
 */
static inline bool NANBOX_NAME(_is_index)(NANBOX_T val) {
    return (val.as_int64 & NANBOX_HIGH16_TAG) == NANBOX_INDEX;
}

/*
 * Return the value without the tag.
 */
static inline uint64_t NANBOX_NAME(_to_index)(NANBOX_T val) {
    assert(NANBOX_NAME(_is_index)(val));
    return val.as_int64 & ~NANBOX_INDEX;
}

/*
 * Box the INDEX value with the tag.
 */
static inline NANBOX_T NANBOX_NAME(_from_index)(uint64_t set) {
    NANBOX_T val;
    val.as_int64 = (set & NANBOX_MASK_PAYLOAD) | NANBOX_INDEX;
    return val;
}

/*
 * Test whether the tag is ANON_FUNCT.
 */
static inline bool NANBOX_NAME(_is_anon_funct)(NANBOX_T val) {
    return (val.as_int64 & NANBOX_HIGH16_TAG) == NANBOX_ANON_FUNCT;
}

/*
 * Return the value without the tag.
 */
static inline void (*NANBOX_NAME(_to_anon_funct)(NANBOX_T val))() {
    assert(NANBOX_NAME(_is_anon_funct)(val));
    return (void (*)())(val.as_int64 & ~NANBOX_ANON_FUNCT);
}

/*
 * Box the ANON_FUNCT value with the tag.
 */
static inline NANBOX_T NANBOX_NAME(_from_anon_funct)(void (*proc)()) {
    NANBOX_T val;
    val.as_int64 = (uint64_t)proc | NANBOX_ANON_FUNCT;
    return val;
}

/*
 * Test whether the tag is BOOLEAN. It is, when bit 1 is set.
 */
static inline bool NANBOX_NAME(_is_boolean)(NANBOX_T val) {
    return !(val.as_int64 & NANBOX_HIGH16_TAG) &&
            (val.as_int64 & NANBOX_MASK_BOOLEAN) == NANBOX_MASK_BOOLEAN;
}

/*
 * Return the value without the tag: the value is bit 0, the tag is bit 1.
 */
static inline bool NANBOX_NAME(_to_boolean)(NANBOX_T val) {
    assert(NANBOX_NAME(_is_boolean)(val));
    return val.as_int64 & 1;
}

/*
 * Box the BOOLEAN value with the tag in bit 1.
 */
static inline NANBOX_T NANBOX_NAME(_from_boolean)(bool b) {
    NANBOX_T val;
    val.as_int64 = b ? NANBOX_VALUE_TRUE : NANBOX_VALUE_FALSE;
    return val;
}

/*
 * Test whether the tag is CHAR.
 */
static inline bool NANBOX_NAME(_is_char)(NANBOX_T val) {
    return (val.as_int64 & NANBOX_HIGH16_TAG) == NANBOX_CHAR;
}

/*
 * Return the value without the tag.
 */
static inline int64_t NANBOX_NAME(_to_char)(NANBOX_T val) {
    assert(NANBOX_NAME(_is_char)(val));
    return val.as_int64 & ~NANBOX_CHAR;
}

/*
 * Box the CHAR value with the tag.
 */
static inline NANBOX_T NANBOX_NAME(_from_char)(int64_t ch) {
    NANBOX_T val;
    val.as_int64 = (ch & NANBOX_MASK_PAYLOAD) | NANBOX_CHAR;
    return val;
}

/*
 * Test whether the tag is FILE.
 */
static inline bool NANBOX_NAME(_is_file)(NANBOX_T val) {
    return (val.as_int64 & NANBOX_HIGH16_TAG) == NANBOX_FILE;
}

/*
 * Return the value without the tag.
 */
static inline FILE *NANBOX_NAME(_to_file)(NANBOX_T val) {
    assert(NANBOX_NAME(_is_file)(val));
    return (FILE *)(val.as_int64 & ~NANBOX_FILE);
}

/*
 * Box the FILE value with the tag.
 */
static inline NANBOX_T NANBOX_NAME(_from_file)(FILE *fp) {
    NANBOX_T val;
    val.as_int64 = (uint64_t)fp | NANBOX_FILE;
    return val;
}

/*
 * Test whether the tag is SET.
 */
static inline bool NANBOX_NAME(_is_set)(NANBOX_T val) {
    return (val.as_int64 & NANBOX_HIGH16_TAG) == NANBOX_SET;
}

/*
 * Return the value without the tag.
 */
static inline uint64_t NANBOX_NAME(_to_set)(NANBOX_T val) {
    assert(NANBOX_NAME(_is_set)(val));
    return val.as_int64 & ~NANBOX_SET;
}

/*
 * Box the SET value with the tag.
 */
static inline NANBOX_T NANBOX_NAME(_from_set)(uint64_t set) {
    NANBOX_T val;
    val.as_int64 = (set & NANBOX_MASK_PAYLOAD) | NANBOX_SET;
    return val;
}

/* true if val is a double or an int */
static inline bool NANBOX_NAME(_is_number)(NANBOX_T val) {
    return val.as_int64 >= NANBOX_MIN_NUMBER;
}

static inline bool NANBOX_NAME(_is_int)(NANBOX_T val) {
    return (val.as_int64 & NANBOX_HIGH16_TAG) == NANBOX_MIN_NUMBER;
}

static inline NANBOX_T NANBOX_NAME(_from_int)(int64_t i) {
    NANBOX_T val;
    val.as_int64 = (i & NANBOX_MASK_PAYLOAD) | NANBOX_MIN_NUMBER;
    return val;
}

static inline int64_t NANBOX_NAME(_to_int)(NANBOX_T val) {
    uint64_t num;
    assert(NANBOX_NAME(_is_int)(val));
    num = val.as_int64 & NANBOX_MASK_PAYLOAD;
    if (num & NANBOX_MASK_SIGNBIT)
        num |= NANBOX_HIGH16_TAG;
    return (int64_t)num;
}

static inline bool NANBOX_NAME(_is_double)(NANBOX_T val) {
    return NANBOX_NAME(_is_number)(val) && !NANBOX_NAME(_is_int)(val);
}

static inline NANBOX_T NANBOX_NAME(_from_double)(double d) {
    NANBOX_T val;
    val.as_double = d;
    val.as_int64 += NANBOX_DOUBLE_ENCODE_OFFSET;
    assert(NANBOX_NAME(_is_double)(val));
    return val;
}

static inline double NANBOX_NAME(_to_double)(NANBOX_T val) {
    assert(NANBOX_NAME(_is_double)(val));
    val.as_int64 -= NANBOX_DOUBLE_ENCODE_OFFSET;
    return val.as_double;
}

static inline bool NANBOX_NAME(_is_pointer)(NANBOX_T val) {
    return !(val.as_int64 & ~NANBOX_MASK_POINTER) && val.as_int64;
}

static inline NANBOX_POINTER_TYPE NANBOX_NAME(_to_pointer)(NANBOX_T val) {
    assert(NANBOX_NAME(_is_pointer)(val));
    return val.pointer;
}

static inline NANBOX_T NANBOX_NAME(_from_pointer)(NANBOX_POINTER_TYPE pointer) {
    NANBOX_T val;
    val.pointer = pointer;
    assert(NANBOX_NAME(_is_pointer)(val));
    return val;
}

/*
 * A string is a pointer that has bit 0 set and bit 1 unset.
 */
static inline bool NANBOX_NAME(_is_string)(NANBOX_T val) {
    return !(val.as_int64 & NANBOX_HIGH16_TAG) &&
            (val.as_int64 & NANBOX_MASK_STRING) == NANBOX_VALUE_STRING;
}

/*
 * When returning the string, bit 0 is set to 0.
 */
static inline NANBOX_POINTER_TYPE NANBOX_NAME(_to_string)(NANBOX_T val) {
    assert(NANBOX_NAME(_is_string)(val));
    return (NANBOX_POINTER_TYPE)(val.as_int64 & ~NANBOX_VALUE_STRING);
}

/*
 * When storing a string in a nanbox, bit 0 must be set.
 */
static inline NANBOX_T NANBOX_NAME(_from_string)(NANBOX_POINTER_TYPE string) {
    NANBOX_T val;
    val.pointer = string;
    val.as_int64 |= NANBOX_VALUE_STRING;
    assert(NANBOX_NAME(_is_string)(val));
    return val;
}

/*
 * Representation-independent functions
 */
static inline double NANBOX_NAME(_to_number)(NANBOX_T val) {
    assert(NANBOX_NAME(_is_number)(val));
    return NANBOX_NAME(_is_int)(val) ? NANBOX_NAME(_to_int)(val)
                                     : NANBOX_NAME(_to_double)(val);
}
#endif /* NANBOX_H */

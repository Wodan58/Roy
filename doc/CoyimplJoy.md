 ![](Wynn.PNG)
==============

Introduction
============

Coy is a reimplementation of 42minjoy that itself is a conversion from the
original Pascal program. 42minjoy uses 30 builtins and the question is whether
this can be reduced a little by defining some builtins with the help of others.

Reduction
=========

Starting with the end result, only 10 builtins remain: `+`, `-`, `<`, `cons`,
`i`, `uncons`, `index`, `put`, `get`, `body`.

Subtraction, `-`, can be defined with `+`, but this can only result in positive
numbers:

    - == [[0] dip sub3 ;
    sub2 == [[1 +] dip] dup sub3 ;
    sub3 == [dup] dip dup [=] dip swap [[1 + sub2] [pop pop]] index i ;

This works by first installing an accumulator; sub2 increments that
accumulator; sub3 adds 1 to the smaller number and repeats itself until the
smaller number is equal to the larger number; the accumulator then contains the
difference. For negative numbers a negate operator would be needed and that
doesn't help to reduce the number of builtins.

`Cons`, `i`, `uncons`, and `index` all work on lists, whereas `<` is
polymorphic, except that it does not compare lists. It would be possible then
to merge `<` and `index` into one operator that performs `index` on lists and
`<` in all other cases.

`Put` is not really needed, because there is automatic output of the top of the
stack at the end of a program. And `get` is not really needed, because all input
to the program could be given in the program itself. It is only that I want the
tutorial to process exactly the same, whether it is processed with a reduced
instruction set, or whether it is processed with the full instruction set.

`Body` must be present to access the symbol table and could be used to implement
`index`, but only if the index variable is either `false` or `true`. The body of
`false` and `true` can then be used to build a program that indexes either the
first or the second entry of the indexed table. But as it is, `index` already
uses other values besides `true` in the tutorial and so another method is needed
to translate values other than `false` into `true`. This seems too much work for
too little reward. As it is, 10 builtins is small enough.

Further reduction
=================

Builtins `cons` and `uncons` are incorporated in the LET-expressions.
Builtins `<` and `index` have been merged into `<`.
Builtins `i` and `body` have been merged into `i`.
This merging was possible, because the unmerged variants use different data
types as input. This brings the number of builtins down to 6.

 ![](Wynn.PNG)
==============

Introduction
============

Coy is a reimplementation of 42minjoy that itself is a conversion from the
original Pascal program. It is extended with builtins from joy1.

Implementation
==============

The implementation uses vectors instead of linked lists for both the stack and
lists.

Builtins
--------

Two of the builtins from 42minjoy, `get` and `body`, are supposed to be
executed at compile time and are not part of the compiler output. `get` has
been added, `body` is available in compiled programs, but differs in meaning.

Compiler
--------

The decision of what to compile is left to each of the builtins. Generally, if
there are enough parameters on the stack of the correct type builtins will
execute at compile time; if not, the stack will be compiled as well as the
builtin. Some builtins, the ones that produce output, will always be compiled.
Noteworthy is also `unstack`, because it is interpreted as well as compiled. It
must be, because it changes to another stack and the runtime must know about
that.

Additions
---------

There will always be the need to add new builtins. It is sufficient to create
a C source file in the src-directory. The build system takes care of the rest.

Performance
===========

The aim is to have overall good performance. It is nice when the slow Fibonacci
function is executed almost as fast as when the algorithm was programmed
directly in C, but testing does not stop there. The other example programs must
also perform well. The way that memory is handled is the determining factor of
program speed; the amount of instructions needed is insignificant.

Comparison
----------

The fib.joy program is: `40 [small] [] [pred dup pred] [+] binrec.`
The lst.joy program is: `1 9000 from-to-list.` In the case of Coy and Moy some
changes have been made so as to allow the program to run faster: fib has the
condition set to `[dup small]` instead of `[small]`; lst.joy has been changed
in a similar fashion. The original Joy has `__settracegc` set to 0.

  ---------------------------------------------------
  | implementation | fib.joy | grmtst.joy | lst.joy |
  |----------------|---------|------------|---------|
  |           joy0 |      28 |        1.6 |    0.03 |
  |           Joy  |      61 |        6.1 |    0.03 |
  |           joy1 |      76 |        7.0 |    0.03 |
  |           Moy  |     140 |       16.0 |    0.08 |
  |           Coy  |      23 |        5.2 |    0.03 |
  ---------------------------------------------------

An explanation is needed. Why is Joy slower than the original version? This is
caused by the vector implementation of the heap and the non-recursive garbage
collector. The original uses a fixed array and a simpler collector.

Joy1 is slower than Joy, because it uses the BDW garbage collector. The many
small nodes that are needed for Joy are not a good fit for a garbage collector.

Moy is slowest, because it has a slow function call mechanism.

Coy is faster than the original in fib.joy, because it doesn't create garbage
in the first place and that is always faster. Coy is also faster when executing
grmtst.joy. Vectors can be more efficient than linked lists, because they
reduce the number of objects that the garbage collector needs to visit.

joy0 executes grmtst.joy a lot faster than other implementations. That makes
the garbage collectors in the other implementations look bad.

 ![](Wynn.PNG)
==============

Introduction
============

Roy started as a reimplementation of 42minjoy that itself is a conversion from
the original Pascal program. As soon as the tutorial from 42minjoy can be
processed correctly, other builtins are added from joy1, but not all of them.

Implementation
==============

This implementation, like Moy, uses vectors instead of linked lists for both the
stack and lists. It uses the normal C stack when doing recursion, unlike Moy.

Builtins
--------

Two of the builtins from 42minjoy, `get` and `body`, are supposed to be
executed at compile time and are not part of the compiler output; `get` reads
Joy source code and that is left out of compiled programs; `body` requires the
availability of a symbol table and that is usually left out from compiled
programs as it is here.

Compiler
--------

The compiler code is now moved to Moy, except that the final shape has not
yet been decided upon. The file `fib.c` is the output of the compiler in Moy.

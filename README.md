Coy
---

This is a reimplementation of [42minjoy](https://github.com/Wodan58/42minjoy).
This project depends on the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Installation
------------

The BDW garbage collector has to be present installed as well as CMake. Then run:

CMake -G "Unix Makefiles"

make

Additions
---------

In addition to normal interpreter mode, this program offers a -c option that
compiles to C11.

Two output files are created, demo1.txt and demo2.txt and they are similar.
The compiled program starts with an empty symbol table.

Adding a builtin, e.g. SELECT requires modification of the program in 5
separate locations.

Coy
---

Build|Linux|Windows|Coverage
---|---|---|---
status|[![Travis CI build status](https://travis-ci.org/Wodan58/Coy.svg?branch=master)](https://travis-ci.org/Wodan58/Coy)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Coy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Coy)|[![Coverage Status](https://coveralls.io/repos/github/Wodan58/Coy/badge.svg?branch=master)](https://coveralls.io/github/Wodan58/Coy?branch=master)

This is a reimplementation of [42minjoy](https://github.com/Wodan58/42minjoy).
This project depends on the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Installation
------------

The BDW garbage collector has to be installed as well as CMake. Then run:

CMake -G "Unix Makefiles" or CMake -G "NMake Makefiles"

make or nmake

Additions
---------

In addition to normal interpreter mode, this program offers a -c option that
compiles to C.

Two output files are created, demo1.txt and demo2.txt; the build process checks
that they are identical.

Adding a builtin, e.g. SELECT requires modification of the program in 3
separate locations: builtin.c, builtin.h, and node.c

Some builtins are not supported: nothing, sametype, and select.

After redoing dup, swap, and pop with LET expressions, only 10 builtins are
used in the tutorial.

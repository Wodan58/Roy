Coy
---

Build|Linux|Windows
---|---|---
status|[![Travis CI build status](https://travis-ci.org/Wodan58/Coy.svg?branch=master)](https://travis-ci.org/Wodan58/Coy)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Coy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Coy)

This is a reimplementation of [42minjoy](https://github.com/Wodan58/42minjoy).
This project depends on the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Installation
------------

The BDW garbage collector has to be installed as well as CMake. Then run:

CMake -G "Unix Makefiles"

make

Additions
---------

In addition to normal interpreter mode, this program offers a -c option that
compiles to C99.

Two output files are created, demo1.txt and demo2.txt and they are identical.

Adding a builtin, e.g. SELECT requires modification of the program in 5
separate locations.

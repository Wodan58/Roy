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

CMake -G "Unix Makefiles"

make

Additions
---------

In addition to normal interpreter mode, this program offers a -c option that
compiles to C99.

Two output files are created, demo1.txt and demo2.txt and they are identical.

Adding a builtin, e.g. SELECT requires modification of the program in 5
separate locations.

<img src="Coy.png" alt="picture" width="1000" />

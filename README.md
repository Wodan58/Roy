Coy
---

Build|Linux|Windows|Coverity|Coverage
---|---|---|---|---
status|[![Travis CI build status](https://travis-ci.org/Wodan58/Coy.svg?branch=master)](https://travis-ci.org/Wodan58/Coy)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Coy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Coy)|<a href="https://scan.coverity.com/projects/wodan58-coy"><img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/14634/badge.svg"/></a>|[![Coverage Status](https://coveralls.io/repos/github/Wodan58/Coy/badge.svg?branch=master)](https://coveralls.io/github/Wodan58/Coy?branch=master)

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

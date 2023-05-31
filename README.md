Coy
---

Build|Linux|Windows|Coverity
---|---|---|---
status|[![GitHub CI build status](https://github.com/Wodan58/Coy/actions/workflows/cmake.yml/badge.svg)](https://github.com/Wodan58/Coy/actions/workflows/cmake.yml)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Coy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Coy)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/14634.svg)](https://scan.coverity.com/projects/wodan58-coy)

This is a~n experimental, unsafe,~ vector only reimplementation of
[Moy](https://github.com/Wodan58/Moy). This project can use the
[BDW garbage collector](https://github.com/ivmai/bdwgc) for better performance.

Build instructions
------------------

    cmake .
    cmake --build .

Changes
-------

Some builtins have been added: `over` and `pick`. They are used in compiled
code, because compiled code does not save/restore the stack when executing a
condition.

Additions
---------

In addition to normal interpreter mode, this program offers two compile
options: -c and -l. Start the program with -h to see what they mean.

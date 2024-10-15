Roy
===

Build|Linux|Coverity
---|---|---
status|[![GitHub CI build status](https://github.com/Wodan58/Coy/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/Wodan58/Coy/actions/workflows/c-cpp.yml)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/14634.svg)](https://scan.coverity.com/projects/wodan58-coy)

This repository contains a recursion enabled runtime for files that have been
translated by [Moy](https://github.com/Wodan58/Moy) into C. This project also
depends on the [BDW garbage collector](https://github.com/ivmai/bdwgc).

Build instructions
------------------

    make

This builds the recursive Fibonacci program.

Changes
-------

Some builtins are not supported.

See also
--------

[Soy](https://github.com/Wodan58/Soy), simply compiled Moy.

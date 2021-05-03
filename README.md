Coy
---

Build|Linux|Windows|Coverity|Coverage|Codecov|Quality|Alerts
---|---|---|---|---|---|---|---
status|[![Travis CI build status](https://travis-ci.com/Wodan58/Coy.svg?branch=master)](https://travis-ci.com/Wodan58/Coy)|[![AppVeyor CI build status](https://ci.appveyor.com/api/projects/status/github/Wodan58/Coy?branch=master&svg=true)](https://ci.appveyor.com/project/Wodan58/Coy)|[![Coverity Scan Build Status](https://img.shields.io/coverity/scan/14634.svg)](https://scan.coverity.com/projects/wodan58-coy)|[![Coverage Status](https://coveralls.io/repos/github/Wodan58/Coy/badge.svg?branch=master)](https://coveralls.io/github/Wodan58/Coy?branch=master)|[![Codecov](https://codecov.io/gh/Wodan58/Coy/branch/master/graph/badge.svg)](https://codecov.io/gh/Wodan58/Coy)|[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/Wodan58/Coy.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Wodan58/Coy/context:cpp)|[![Alerts](https://img.shields.io/lgtm/alerts/g/Wodan58/Coy.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Wodan58/Coy/alerts)

This is an experimental, unsafe, vector only, reimplementation of
[Moy](https://github.com/Wodan58/Moy). This project depends on the
[BDW garbage collector](https://github.com/ivmai/bdwgc) and
[JAPI](https://github.com/maxstrauch/japi2-kernel).
JAPI is under the LGPL license, see LICENSE.txt

Installation
------------

The BDW garbage collector has to be installed as well as CMake. Then run:

    cmake .
    cmake --build .

And:

    java -jar JAPI.jar
    ./joy mandel.joy

This last test results in:

<img src="doc/mandel.jpg"/>

Mandelbrot in full Swing.

Additions
---------

In addition to normal interpreter mode, this program offers a -c option that
compiles to C.

Two output files are created, demo1.txt and demo2.txt; the build process checks
that they are identical.

Adding a builtin: it is sufficient to create a new file in de src-directory.
The build system makes sure that all dependent files are recreated.

Some builtins from Moy are not supported, because they require runtime type
information that is only partially supported in an unsafe manner.

The attempt to reduce the number of builtins is continued in
[HET](https://github.com/Wodan58/HET).
See [Underload](https://esolangs.org/wiki/Underload) for another
example.

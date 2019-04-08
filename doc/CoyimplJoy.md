 ![](Wynn.PNG)
==============

Introduction
============

Coy is a reimplementation of 42minjoy that itself is a conversion from the original
Pascal program. 42minjoy uses 30 builtins and the question is whether this can be reduced
a little by defining some builtins with the help of others.

Reduction
=========

10 builtins are sufficient: `dup`, `swap`, `pop` are stack operations;
`cons` and `uncons` are list operations;
`-` and `<` are integer operations;
`i` is needed to execute programs;
`get` and `put` provide I/O.
An integer constant `1` is needed, as well as a string constant, such as "i".

These 10 builtins can be encoded with the help of just two: `o` and `i`; proof of that
will be provided later on.

`<` and `index` have been merged: `<` on integers; `index` on lists.
`i` and `body` have been merged: `i` on lists; `body` on symbols.

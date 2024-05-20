# WeaveFont
A typographical Submodule for Weaver Game
Engine

This project is part of [Weaver Game
Engine](https://github.com/thiagoharry/weaver). It implements
WeaveFont, a language to desing and control typographical fonts strongly based on
[Knuth's METAFONT](https://en.wikipedia.org/wiki/Metafont).

Each WeaveFont source file can generate an infinity of
different typographical fonts, just changing some parameters. For
example, with a single source file, you could set the described font
size to 13pt, set 75% of bold, 10% of italics and toggle monospace
mode. The typographical font could also define other customized parameters,
like randomness or slanting, for example. Each WeaveFont source file
describes an entire typographical font family, with a set of parameters
that could be changed. And each one uses WeaveFont language, a complete interpreted
language to describe the font.

Despite similar syntax, WeaveFont has several differences to METAFONT. Some of them are:

* WeaveFont generates fonts on the fly, using hardware acceleration thanks to OpenGL.
* WeaveFont is not a macro language. Functionalities that on Knuth's METAFONT are
  created using macros, in WeaveFont are built in the language.
* Our variables have scope, not all of them are global. We also use more traditional
  rules in our lexer. For WeaveFont, `x1` and `x2` are two unrelated and valid variable names,
  for example. 
* We use floating-point math in the language, instead of the fixed-point math used by METAFONT.
  This makes our code faster, and usually more precise. However, this means that despite using
  the same algorithms to interpolate points in curves, our curves can have some differences
  to curves created by METAFONT (see [Issue 1](https://github.com/thiagoharry/weaver-interface-metafont/issues/1)).
* We do not support equations, just regular assignments. `a=b+c` is equal `a:=b+c`.
* All variables must be declared on WeaveFont, not just non-numerical ones.


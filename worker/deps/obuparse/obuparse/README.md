obuparse
========

A simple and portable single file AV1 OBU parser written in mostly C89 with a tiny bit of C99,
with a permissive license.

Why?
----

I got tired of rewriting ad-hoc OBU parsers for various tasks suchs as ISOBMFF muxing,
MSE codec string generation, level verification, etc. So I decided to write once,
as correctly as possible, and to use it everywhere in place of probably subtly-broken
ad-hoc parsers.

I could have ripped out an OBU parser from other projects, but they're all either
very intertwined with their respective encoder/decoder, written in very unportable
manners, or in non-FFI friendly languages. At the time of writing this, I am not
aware of any permissively licensed (or otherwise) OBU parsers that actually work
portably.

How?
----

Simply copy `obuparse.c` and `obuparser.h` into your project, or use this repository
as a git submodule.

By default, the parser uses a checked bitreader, but you can define `OBP_UNCHECKED_BITREADER`
to use the unchecked version if that really matters to you.

All API documentation lives in `obuparse.h`.

There is also a Makefile provided for building a simple shared library on Linux. It
should be straightforward to build for other OSes; all public symbols are namespaced
with `obp_`. All public enums and types are namespaced with `OBP`.

Features
--------

This section will expand as more of the library becomes complete, and it moves
out of being a work in progress.

* No allocations; only works on user-provided buffers and the stack.
* OBU header parsing.
* Sequence Header OBU parsing.
* Metadata OBU parsing.
* Tile List OBU parsing.
* Tile Group OBU parsing.
* Frame Header OBU parsing.
* Frame OBU parsing.

Tools
-----

The `tools` directory contains a simple tool to parse and serialize OBUs from
an IVF file into JSON, called `dumpobu`.

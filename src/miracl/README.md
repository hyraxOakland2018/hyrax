# miracl for Python

This directory includes a library for calling MIRACL from Python. Most notably, this
includes a couple implementations of fast multiexponentiation algorithms; see
`src/pymircffi/multiexp.c`.

To actually call this library from python, use the MiraclEC object defined in
the `src/fennel/pymircffi` module.

# libfennel - Hyrax reference implementation #

libfennel is the reference implementation of Hyrax, a zkSNARK that requires no trusted setup.

This implementation is written in Python and C/C++.

## Building and using ##

The code in this directory is pure Python, but to read PWS files and for elliptic curve operations
we use C/C++ extensions.  The source for these extensions live in ../miracl and ../libpws.

To make all of this easy, there's a makefile in this directory that you can use. For example,
`make -j4` will do more or less what you expect.

You will need to install a few libraries before you can build the C extensions, and you will need to
install Python's CFFI package. For more information on the libraries you'll need, see the README
files in ../libpws and ../miracl.

**Note**: you do *not* need to run `make install` in ../libpws or ../miracl.

## Running ##

If you want to run a PWS file, you should use `run_fennel.py` like so:

    ./run_fennel.py -p /path/to/PWS/file

Execute `./run_fennel.py` with no arguments to see all of the options. See `../pws/experiments/`
for some ideas of the invocations you should use.

## Tests ##

The `libfenneltests/` subdir has a pretty complete set of tests for libfennel. These tests do not
require building ../libpws, but they do require ../miracl.

You can run the tests like so:

    python libfenneltests/

## Elliptic curve modules ##

`pymircffi` implements the `MiraclEC` object. This object handles the Python-C interface via CFFI.
It is compatible with PyPy, too!

# License #

Copyright 2017, the Hyrax authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

#!/usr/bin/python
#
# (C) 2018 Hyrax Authors
#
# use CFFI to link from Python to pylaurent (test)

import os.path as OP

from cffi import FFI
ffi = FFI()
ffi.cdef("""
    const char *convert_matrix(char *in);
    const char *compute_laurent(char *t_yP, char *t_r, char *t_s);
    void clear_stringstream(void);
    void init(char *p);
""")
lib = ffi.dlopen(OP.join(OP.dirname(OP.realpath(__file__)), 'src', 'pylaurent.so'))

def init(prime):
    lib.init(str(prime))

def compute(Ypvec, rx, sx):
    tx = eval(ffi.string(lib.compute_laurent(str(Ypvec), str(rx), str(sx)))) # pylint: disable=eval-used
    lib.clear_stringstream()
    return tx

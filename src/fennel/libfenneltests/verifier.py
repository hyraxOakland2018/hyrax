#!/usr/bin/python
#
# (C) 2017 Hyrax Authors
#
# test layer prover

# hack: this test lives in a subdir
try:
    import sys
    import os.path
except:
    assert False
else:
    sys.path.insert(1, os.path.abspath(os.path.join(sys.path[0], os.pardir)))

import random

from libfennel.circuitverifier import CircuitVerifier
from libfennel.defs import Defs
from libfennel import randutil

def run_one_test(nInBits, nCopies, nLayers, qStat):
    nOutBits = nInBits

    in0vv = []
    in1vv = []
    typvv = []
    for _ in xrange(0, nLayers):
        (in0v, in1v, typv) = randutil.rand_ckt(nOutBits, nInBits)
        in0vv.append(in0v)
        in1vv.append(in1v)
        typvv.append(typv)

    ver = CircuitVerifier(nCopies, 2**nInBits, in0vv, in1vv, typvv)
    inputs = randutil.rand_inputs(nInBits, nCopies)
    ver.run(inputs)

    if not qStat:
        print "nInBits: %d, nCopies: %d, nLayers: %d" % (nInBits, nCopies, nLayers)
        for fArith in [ver.in_a, ver.out_a, ver.sc_a, ver.tV_a, ver.nlay_a]:
            if fArith is not None:
                print "    %s: %s" % (fArith.cat, str(fArith))

def run_tests(num_tests, qStat=True):
    for i in xrange(0, num_tests):
        Defs.track_fArith = i % 2 == 0
        run_one_test(random.randint(2, 4), 2**random.randint(3, 8), random.randint(2, 5), qStat)

        if qStat:
            sys.stdout.write('.')
            sys.stdout.flush()

    if qStat:
        print " (verifier test passed)"

if __name__ == "__main__":
    run_tests(16, False)

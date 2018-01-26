#!/usr/bin/python

import os
import sys

sys.path.insert(1, os.path.abspath(os.path.join(os.path.dirname(__file__), 'pypws')))
import pypws

from libfennel.defs import Defs

def main():
    if len(sys.argv) < 2:
        print "usage:", sys.argv[0], "<filename.pws>"
        sys.exit(1)
    elif not os.path.exists(sys.argv[1]):
        print "ERROR: cannot open", sys.argv[1]
        sys.exit(1)

    if len(sys.argv) > 2:
        pws_parsed = pypws.parse_pws_unopt(sys.argv[1], str(Defs.prime))
    else:
        pws_parsed = pypws.parse_pws(sys.argv[1], str(Defs.prime))

    print "# Info for", sys.argv[1]
    print "inputs:", len(pws_parsed[0])

    totals = {'MUL':0, 'ADD':0, 'SUB':0, 'MUX':0, 'OR':0, 'XOR':0, 'NOT':0, 'NAND':0, 'NOR':0, 'NXOR':0, 'NAAB': 0, 'PASS': 0}
    maxw = 0
    totw = 0
    for (num, lay) in enumerate(pws_parsed[1:]):
        oString = "layer %3d:" % (len(pws_parsed) - num - 2)
        counts = {'MUL':0, 'ADD':0, 'SUB':0, 'MUX':0, 'OR':0, 'XOR':0, 'NOT':0, 'NAND':0, 'NOR':0, 'NXOR':0, 'NAAB':0, 'PASS': 0}
        for (t, _, __, ___) in lay:
            counts[t] += 1
            totals[t] += 1

        for t in sorted(counts.keys()):
            oString += "\t" + t + ": %5d" % counts[t]

        oString += "\t" + "Total: %5d" % len(lay)
        print oString

        if len(lay) > maxw:
            maxw = len(lay)
        totw += len(lay)

    oString = "totals:    "
    for t in sorted(counts.keys()):
        oString += "\t" + t + ": %5d" % totals[t]

    oString += "\t" + "Total: %5d" % totw
    oString += "\t" + "Max: %5d" % maxw
    print oString

if __name__ == "__main__":
    main()

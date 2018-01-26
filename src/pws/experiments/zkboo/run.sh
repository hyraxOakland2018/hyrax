#!/bin/bash

mkdir -p log_zkboo

XDIR=../../../zkboo
PEXE=${XDIR}/p
VEXE=${XDIR}/v

make -C ${XDIR} clean
make -C ${XDIR}
if [[ ! -x ${PEXE} ]] || [[ ! -x ${VEXE} ]]; then
    echo "Could not build executables! Giving up."
    exit 1
fi

for i in $(seq 1 8); do
    echo "Merkle $i"
    NREPS=$(($((2*$((2**${i}))))-1))
    PREPS=$((2**$((9-${i}))))
    perf stat -d -r ${PREPS} ${PEXE} hyraxrules ${NREPS} &> log_zkboo/SHA256_${i}.out
    perf stat -d -r ${PREPS} ${VEXE} ${NREPS} &>> log_zkboo/SHA256_${i}.out
done

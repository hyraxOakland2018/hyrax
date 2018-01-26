#!/bin/bash
#
# (C) 2018 Hyrax Authors
#
# process output from running ZKBoo

FNAME=../SHA256/out/merkle_zkbpp.out
mkdir -p $(dirname "${FNAME}")

set -e
set -u

echo '$\log_2 M$, number of leaves in Merkle tree' > ${FNAME}
for i in {1..8}; do
    readarray -n 2 -t RESULT < <(grep task-clock log_zkboo/SHA256_${i}.out | awk '{print($1/1000);}')
    NREPS=$(($((2*$((2**${i}))))-1))
    SIZE=$((${NREPS}*16710))
    echo ${i} ${SIZE} ${RESULT[0]} ${RESULT[1]} 0
done >> ${FNAME}

#!/bin/bash
#
# (C) 2018 Hyrax Authors
#
# process outputs from Ligero runs

FNAME=../SHA256/out/merkle_ligero.out
FNAME2=../SHA256/out/merkle_ligeroun.out
mkdir -p $(dirname "${FNAME}")

set -e
set -u

# start the pipeline
exec 3< <(tail -n +3 ligero.csv | tr , ' ')

round () {
    echo $(($((${1}+12))/24));
};

echo '$\log_2 M$, number of leaves in Merkle tree' > ${FNAME}
echo '$\log_2 M$, number of leaves in Merkle tree' > ${FNAME2}
for i in {1..8}; do
    read -a RESULT <&3
    NINVOCS=$(($((2**$((${i}+1))))-1))
    if [[ ${NINVOCS} != ${RESULT[0]} ]]; then
        echo ERROR expected ${NINVOCS} invocations, got ${RESULT[0]}
        exit -1
    fi
    # fields 4 5 6 are amortized
    echo ${i} $(round ${RESULT[6]}) ${RESULT[4]} ${RESULT[5]} 0 >> ${FNAME}
    echo ${i} $(round ${RESULT[3]}) ${RESULT[1]} ${RESULT[2]} 0 >> ${FNAME2}
done 

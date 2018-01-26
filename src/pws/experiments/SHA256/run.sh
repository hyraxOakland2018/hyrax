#!/bin/bash

if [ ! -f "../../../miracl/lib/m191big_multi.ecs" ]; then
    echo "Looks like you haven't downloaded the m191 bigparams file; see ../../../miracl/lib/m191big_multi_url"
    exit 1
fi

case "$1" in
    hyrax)
        # need to run with 0, 2, 3
        if [[ -z $2 ]]; then
            echo "usage: ./run.sh hyrax k"
            echo " maybe try k=0, 2, or 3"
            exit -1
        fi
        RUN="pypy -OO ../../../fennel/run_fennel.py -z 3 -C m191big -n 0 -w $2 -R 306,7353"
        LOG=log_w$(tr -d '.' <<< $2)
        ;;
    hyraxun)
        RUN="pypy -OO ../../../fennel/run_fennel.py -z 1 -C m191 -n 0 -R 306,7353"
        LOG=log_unopt
        ;;
    bccgp)
        RUN="pypy -OO ../../../bccgp/run_bccgp.py -C m191 -n 0"
        LOG=log_bccgp
        ;;
    bullet)
        RUN="pypy -OO ../../../bccgp/run_bccgp.py -C m191big -n 0 -b"
        LOG=log_bullet
        ;;
    *)
        echo "ERROR arg 1 must be one of hyrax hyraxun bccgp bullet"
        exit 1
esac
mkdir -p ${LOG}

# merkle instances
for i in {1..8}; do
    echo "running Merkle $i"
    ${RUN} -p SHA256_64.pws -r SHA256_64_merkle_${i}_rdl.pws -c $((${i}+1)) -L ${LOG}/SHA256_64_merkle_${i}.log
done

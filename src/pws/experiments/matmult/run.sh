#/bin/bash

# max ncopies gives ~60M gates
# 256: 1
# 128: 4
# 64: 7
# 32: 10
# 16: 13

if [ ! -f "../../../miracl/lib/m191big_multi.ecs" ]; then
    echo "Looks like you haven't downloaded the m191 bigparams file; see ../../../miracl/lib/m191big_multi_url"
    exit 1
fi

case "$2" in
    hyrax)
        RUN="pypy -OO ../../../fennel/run_fennel.py -z 3 -C m191 -n 0"
        LOG=log
        ;;
    hyraxun)
        RUN="pypy -OO ../../../fennel/run_fennel.py -z 1 -C m191 -n 0"
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
        echo "ERROR arg 2 must be one of hyrax hyraxun bccgp bullet"
        exit 1
esac
mkdir -p ${LOG}


if [[ $1 = 16 ]]; then
    echo "16x16 matrices"
    for i in $(seq 1 15); do
        echo "log N="${i}
        ${RUN} -p matmult_16.pws -c $i -L ${LOG}/matmult_16x16_${i}.log
    done
fi

if [[ $1 = 32 ]]; then
    echo "32x32 matrices"
    for i in $(seq 1 12); do
        echo "log N="${i}
        ${RUN} -p matmult_32.pws -c $i -L ${LOG}/matmult_32x32_${i}.log
    done
fi

if [[ $1 = 64 ]]; then
    echo "64x64 matrices"
    for i in $(seq 1 9); do
        echo "log N="${i}
        ${RUN} -p matmult_64.pws -c $i -L ${LOG}/matmult_64x64_${i}.log
    done
fi

if [[ $1 = 128 ]]; then
    echo "128x128 matrices"
    for i in $(seq 1 6); do
        echo "log N="${i}
        ${RUN} -p matmult_128.pws -c $i -L ${LOG}/matmult_128x128_${i}.log
    done
fi

if [[ $1 = 256 ]]; then
    echo "256x256 matrices"
    for i in $(seq 1 1); do
        echo "log N="${i}
        ${RUN} -p matmult_256x256.pws -c $i -L ${LOG}/matmult_256x256_${i}.log
    done
fi

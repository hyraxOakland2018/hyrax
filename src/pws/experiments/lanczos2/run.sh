#!/bin/bash

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


if [[ $1 = 2 ]]; then
    # run tests for 2x downscaling
    echo "running 2x downscaling tests"
    for i in $(seq 4 2 18); do
        RDLFILE=lanczos2_2_*$((2**${i}))_rdl.pws
        LOGFILE=$(basename ${RDLFILE} _rdl.pws).log
        echo "** "${RDLFILE}
        ${RUN} -p lanczos2_2.pws -r ${RDLFILE} -c ${i} -L ${LOG}/${LOGFILE}
    done
fi

if [[ $1 = 4 ]]; then
    # run tests for 4x downscaling
    echo "running 4x downscaling tests"
    for i in $(seq 4 2 14); do
        RDLFILE=lanczos2_4_*$((2**${i}))_rdl.pws
        LOGFILE=$(basename ${RDLFILE} _rdl.pws).log
        echo "** "${RDLFILE}
        ${RUN} -p lanczos2_4.pws -r ${RDLFILE} -c ${i} -L ${LOG}/${LOGFILE}
    done
fi

if [[ $1 = 8 ]]; then
    # run tests for 8x downscaling
    echo "running 8x downscaling tests"
    for i in $(seq 4 2 14); do
        RDLFILE=lanczos2_8_*$((2**${i}))_rdl.pws
        LOGFILE=$(basename ${RDLFILE} _rdl.pws).log
        echo "** "${RDLFILE}
        ${RUN} -p lanczos2_8.pws -r ${RDLFILE} -c ${i} -L ${LOG}/${LOGFILE}
    done
fi

if [[ $1 = 16 ]]; then
    # run tests for 16x downscaling
    echo "running 16x downscaling tests"
    for i in $(seq 4 2 12); do
        RDLFILE=lanczos2_16_*$((2**${i}))_rdl.pws
        LOGFILE=$(basename ${RDLFILE} _rdl.pws).log
        echo "** "${RDLFILE}
        ${RUN} -p lanczos2_16.pws -r ${RDLFILE} -c ${i} -L ${LOG}/${LOGFILE}
    done
fi

#!/bin/sh

case "$1" in
    hyrax)
    hyraxun)
        EXTRA=""
        ;;
    bccgp)
    bullet)
        EXTRA="-C -R -P"
        ;;
    *)
        echo "must specify hyrax hyraxun bccgp bullet"
        exit 1
esac

( for i in $(seq 1 8); do echo $i; done ) | parallel ../../sha256gen.py ${EXTRA} -P -m

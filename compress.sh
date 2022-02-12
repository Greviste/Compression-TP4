#!/bin/bash

mkdir -p compressed
mkdir -p uncompressed
rm -r compressed/* uncompressed/*
for Q in {4..200..2}
do
    mkdir compressed/$Q
    mkdir uncompressed/$Q
    ./ondelette wifi.pgm compressed/$Q/wifi $Q
    for f in hf mfh mfv
    do
        ./rle compressed/$Q/wifi.$f.pgm compressed/$Q/wifi.$f.pgm.rle
        ./huffman c compressed/$Q/wifi.$f.pgm.rle compressed/$Q/wifi.$f.pgm.rle.huff
        rm compressed/$Q/wifi.$f.pgm compressed/$Q/wifi.$f.pgm.rle
        ./huffman d compressed/$Q/wifi.$f.pgm.rle.huff uncompressed/$Q/wifi.$f.pgm.rle
        ./unrle uncompressed/$Q/wifi.$f.pgm.rle uncompressed/$Q/wifi.$f.pgm
    done
    ./huffman c compressed/$Q/wifi.bf.pgm compressed/$Q/wifi.bf.pgm.huff
    rm compressed/$Q/wifi.bf.pgm
    ./huffman d compressed/$Q/wifi.bf.pgm.huff uncompressed/$Q/wifi.bf.pgm

    ./rebuild uncompressed/$Q/wifi uncompressed/back$Q.pgm $Q
done

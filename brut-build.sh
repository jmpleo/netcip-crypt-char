#!/bin/bash

for N in {2..4}; do
    for M in {2..4}; do
        for H in {4..40}; do
            ./build.sh $N $M $H
        done
    done
done

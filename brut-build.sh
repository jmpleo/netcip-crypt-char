#!/bin/bash

for N in {2..4}; do
    for M in {2..4}; do
        for H in {4..40}; do
          if  (( $H % $M == 0 && $M*$N != 4 )); then
            ./build.sh $N $M $H
          fi
        done
    done
done

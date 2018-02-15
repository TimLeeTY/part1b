#! /bin/bash

g++ -o bonker.out bonker.cc
./bonker.out > out.txt
gnuplot 'plotbonker2.gnu'
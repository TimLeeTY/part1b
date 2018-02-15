#! /bin/bash

g++ -o planet1.out planet1.cc
./planet1.out > out.txt
gnuplot 'plotmovie1.gnu'
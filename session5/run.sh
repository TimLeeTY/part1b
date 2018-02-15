#! /bin/bash

g++ -o planet.out planet.cc
./planet.out > out.txt
gnuplot 'plotmovie.gnu'
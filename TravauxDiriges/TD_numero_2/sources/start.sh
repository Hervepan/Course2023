#! /bin/bash

for i in $(seq 1 8)
do 
    printf "mandelbrot with $i process \n"
    mpiexec -n $i ./a.out
    echo -e "\n"
done    
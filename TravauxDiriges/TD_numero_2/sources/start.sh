#! /bin/bash

mpiCC matvec_$1.cpp -o matvec && mpiexec -n $2 ./matvec
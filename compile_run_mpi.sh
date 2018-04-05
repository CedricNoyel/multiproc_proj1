#!/bin/bash
mpicc -o hn matrix.c
mpirun -n 4 ./hn

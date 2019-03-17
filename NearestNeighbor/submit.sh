#!/bin/bash

#SBATCH -o testing%j.out
#SBATCH -e testing%j.err
#SBATCH -N 1
#SBATCH -p gpu_exp 
#SBATCH -J NN_GPU_Exercise
#SBATCH -t 04:00:00
#SBATCH --mail-type=ALL
#SBATCH --mail-user=mwilchek@gmu.edu

time ./nearest_neighbor
time ./nearest_neighbor
time ./nearest_neighbor
time ./nearest_neighbor
time ./nearest_neighbor


#!/bin/bash

#SBATCH -t 10
#SBATCH -o nik_output%j.out
#SBATCH -e nik_output%j.out
#SBATCH --mail-user=nikhita@gwu.edu
#SBATCH --mail-type=ALL
#SBATCH -p allgpu-noecc
#SBATCH -N 4

module load python/2.7.6
module load openmpi/1.8/gcc/4.9.2/cpu


run -n 48 python MPIMonteCarloPi_v2.py 10000000 

#!/bin/bash

#SBATCH -o testing%j.out
#SBATCH -e testing%j.err 
#SBATCH -N 10
#SBATCH -p short
#SBATCH -J MPI_Test
#SBATCH -t 00:30:00
#SBATCH --mail-type=ALL
#SBATCH --mail-user=maclach@gwu.edu

module load openmpi/current
module load python/2.7.11

time mpirun -n 160 python MPIMonteCarloPi_v2.py 10000000

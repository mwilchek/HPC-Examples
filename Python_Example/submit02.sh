#!/bin/bash


#SBATCH -o Python_test%j.out
#SBATCH -e Python_test%j.err

#SBATCH -t 10
#SBATCH -p c1exp
#SBATCH	 -N 1
#SBATCH  -n 20
 
srun sh wrapper.sh

#!/bin/bash


#SBATCH -o Python_test%j.out
#SBATCH -e Python_test%j.err

#SBATCH -t 10
#SBATCH -p c1exp
#SBATCH	 -N 1
#SBATCH  -n 20

cd /home/maclach/Codes/HPC_Examples/SLURM/SingleThreadSRun/Python_Example 
srun sh wrapper.sh

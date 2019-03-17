#!/bin/sh
# set output and error output filenames, %j will be replaced by Slurm with the jobid

#SBATCH -o testing%j.out
#SBATCH -e testing%j.err 
# single node in the "short" partition
#SBATCH -N 1
#SBATCH -n 3
#SBATCH -t 3
#SBATCH -p debug
# send email on job start/stop

#export OMP_NUM_THREADS=12
./hello

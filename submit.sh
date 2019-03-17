#!/bin/bash

#SBATCH -o testing%j.out
#SBATCH -e testing%j.err 
#SBATCH -N 1
#SBATCH -p short
#SBATCH -J glen_test
#SBATCH -t 00:30:00
#SBATCH --mail-type=ALL
#SBATCH --mail-user=<your_netid>@gwu.edu

module load matlab/r2017a

matlab -nojvm -nodesktop < test.m




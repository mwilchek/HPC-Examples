#!/bin/bash 

module load python/2.7.11
python python_example.py ${SLURM_JOBID} ${SLURM_PROCID} 1000

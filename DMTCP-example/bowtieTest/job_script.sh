#!/bin/sh
# ten mins timelimit:
#SBATCH -t 00:10:00
#SBATCH -p c1exp
#SBATCH -N 1
#SBATCH -o bowtie2%j.out
#SBATCH -e bowtie2%j.err
#SBATCH --mail-type=ALL
#SBATCH --mail-user=mwilchek@gwu.edu	
#SBATCH -D /lustre/groups/c1/DMTCP-example/bowtieTest

module load bowtie2

bowtie2 --local -x ../bowtie2/example/index/lambda_virus -U ../bowtie2/example/reads/longreads.fq -S eg3.sam -p 1 --quiet

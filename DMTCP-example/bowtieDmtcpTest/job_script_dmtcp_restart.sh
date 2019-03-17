#!/bin/sh
# ten mins timelimit:
#SBATCH -t 00:10:00
#SBATCH -p c1exp
#SBATCH -N 1
#SBATCH -o bowtie2%j.out
#SBATCH -e bowtie2%j.err
#SBATCH --mail-type=ALL
#SBATCH --mail-user=aklwong@gwu.edu
#SBATCH -D /lustre/groups/c1/DMTCP-example/bowtieDmtcpTest

module load bowtie2
module load dmtcp/current

# Start DMTCP
dmtcp_coordinator --daemon --port 0 --port-file /tmp/port
export DMTCP_COORD_HOST=`hostname`
export DMTCP_COORD_PORT=$(</tmp/port)

./dmtcp_restart_script.sh

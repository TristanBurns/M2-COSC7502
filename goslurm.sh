#!/bin/bash -l
#
#SBATCH --job-name=MPI_testing_TB
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=1G # memory (MB)
#SBATCH --time=0-00:05 # time (D-HH:MM)


export OMP_NUM_THREADS=${SLURM_CPUS_PER_TASK}
export MKL_NUM_THREADS=${SLURM_CPUS_PER_TASK}
echo 'running with OMP_NUM_THREADS =' $OMP_NUM_THREADS
echo 'running with MKL_NUM_THREADS =' $MKL_NUM_THREADS
echo "This is job '$SLURM_JOB_NAME' (id: $SLURM_JOB_ID) running on the following nodes:"
echo $SLURM_NODELIST
echo "running with OMP_NUM_THREADS= $OMP_NUM_THREADS "
echo "running with SLURM_TASKS_PER_NODE= $SLURM_TASKS_PER_NODE "

if [ ! -f GeneticAlgorithm ] ; then
   echo "unable to find GeneticAlgorithm (mpi version)"
   echo "you probably need to compile code"
   exit 2
fi

time mpiexec -n $1 ./GeneticAlgorithm >> outputfile_mpi.txt

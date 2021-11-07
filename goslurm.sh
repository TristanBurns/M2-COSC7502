#!/bin/bash -l
#
#SBATCH --job-name=Parallel_1_1024_42_8
#SBATCH --nodes=1
#SBATCH --ntasks=8
#SBATCH --ntasks-per-node=8
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=4G # memory (MB)
#SBATCH --time=0-00:01 # time (D-HH:MM)


export OMP_NUM_THREADS=${SLURM_CPUS_PER_TASK}
export MKL_NUM_THREADS=${SLURM_CPUS_PER_TASK}
echo 'running with OMP_NUM_THREADS =' $OMP_NUM_THREADS
echo 'running with MKL_NUM_THREADS =' $MKL_NUM_THREADS
echo "This is job '$SLURM_JOB_NAME' (id: $SLURM_JOB_ID) running on the following nodes:"
echo $SLURM_NODELIST
echo "running with OMP_NUM_THREADS= $OMP_NUM_THREADS "
echo "running with SLURM_TASKS_PER_NODE= $SLURM_TASKS_PER_NODE "

if [ ! -f ${SLURM_JOB_NAME} ] ; then
   echo "unable to find GeneticAlgorithm (mpi version)"
   echo "you probably need to compile code"
   exit 2
fi
export current_time=$(date "+%Hh%Mm%Ss")
echo ${SLURM_JOB_NAME}_$current_time.txt
time mpiexec -n ${1} ./${SLURM_JOB_NAME} >> ${SLURM_JOB_NAME}_$current_time.txt

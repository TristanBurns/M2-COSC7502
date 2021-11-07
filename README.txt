# COSC7052 Milestone 2
# Name: Tristan Burns
# Student Number: 42648493

----------------------
QUICKTEST INSTRUCTIONS
----------------------
1. Run: 
submitslurm.sh

This will compile and submit a job to slurm for 8 islands and a chromosome size of 1024. 
The results will be written to Parallel_1_1024_42_8_HhMmSs.txt

2. Modifications to the number of islands or problem size can be made inside submitslurm.sh, by editing parameters as required. 

----------------------
DETAILED INSTRUCTIONS
----------------------
1. Confirm user parameters (macros) in main.cpp file. The following parameters can be edited:

#define n 1024                   // Chromosome size (number of genes per individual).
#define m 128                    // Population size (number of individuals). ***MUST BE A POWER OF 2***
#define seed 42                  // Psuedorandom number generator seed (std:srand(seed)).
#define maxgenerations 1000000   // Maximum number of generations (while loop limit).
#define t 2                      // Tournament size (parents competing for selection).
#define verbose false            // Verbose output (cout) for verification.
#define printfitness true        // Best fitness per generation output (cout).
#define migration true           // Enables migration of (number of) migrants each generation in ring pattern between islands. 
#define migrants 1               // Number of individuals migrating each generation, **must be less than m/number of islands (MPI world_size)***. 

Warning: Setting verbose to true for large m or n (~>100) will result in very large output files and longer runtimes. 
Use verbose for small problem verification.

1. On getafix run the command:
module load gnu/7.2.0 gnutools mvapich2_eth

2. Compile the program using the makefile:
make 

3. Alternately you can compile using the command:
mpic++ -std=c++11 -w -g -O3 -funroll-loops -flto -fuse-linker-plugin functions.cpp main.cpp -o GeneticAlgorithm  

4. Run the program locally using the command:
mpiexec -n 8 ./GeneticAlgorithm

Where 8 is the number of islands, which can be varied. 2, 4, 8 and 16 islands have been tested on getafix.


5. Alternatively you can run the program on getafix using the command:
sbatch goslurm.sh 8

Where 8 is the number of islands, which can be varied. 2, 4, 8 and 16 islands have been tested on getafix.

Note: ensure the job-name in goslurm.sh is:
#SBATCH --job-name=GeneticAlgorithm

6. When run using goslurm.sh, GeneticAlgorithm will write outputs to GeneticAlgorith_HhMmSs.txt.



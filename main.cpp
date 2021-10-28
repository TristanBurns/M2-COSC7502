#include <mpi.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "functions.h" 

//######################################################################################
//####                                                                              ####
//####                               User Input (macros)                            ####
//####                                                                              ####
//######################################################################################

#define n 16                    // Chromosome size (number of genes per individual).
#define m 8                     // Population size (number of individuals).
#define seed 42                 // Psuedorandom number generator seed (std:srand(seed)).
#define maxgenerations 2000     // Maximum number of generations (while loop limit).
#define t 2                     // Tournament size (parents competing for selection).
#define verbose true            // Verbose output (cout) for verification.
#define printfitness false      // Best fitness per generation output (cout).

//######################################################################################
//####                                                                              ####
//####                         DO NOT MODIFY BELOW THIS LINE                        ####
//####                                                                              ####
//######################################################################################



using namespace std;
int main(int argc, char** argv)
{
   MPI_Init(&argc, &argv);

   int world_size;
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);

   int my_rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  
   printf("Initialising arrays on island %d out of %d\n", my_rank+1, world_size);
    // Initialise Arrays on each island
    int m_fraction = m/world_size;
    //  p[m/worldsize][n] - Array to store population with m individuals with chromosome size n.
    int *p = static_cast<int*>(malloc((m_fraction)*n*sizeof(int)));
    //  q[m][n] - Array to store m children with chromosome size n.                 
    int *q = static_cast<int*>(malloc((m_fraction)*n*sizeof(int)));
    //  best - Best (highest) fitness of current generation.
    int best;
    //  generation - While loop counter. Initialise first generation (generation 0).
    int generation = 0;
    //  fitness[maxgenerations] - Array to store best (highest) fitness per generation.
    int *fitness = static_cast<int*>(malloc((maxgenerations)*sizeof(int)));
    printf("Successfully created arrays on island %d out of %d\n", my_rank+1, world_size);
    
    // Deterministic and differe random seed for each island (rank).
    std::srand(seed+my_rank);
    // Initialise fraction of population on each island.
   RandomPopulationVerbose(p, n, m_fraction, my_rank);

   MPI_Finalize();
}
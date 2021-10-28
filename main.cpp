#include <mpi.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <algorithm>
#include "functions.h" 

//######################################################################################
//####                                                                              ####
//####                               User Input (macros)                            ####
//####                                                                              ####
//######################################################################################

#define n 1000                    // Chromosome size (number of genes per individual).
#define m 100                     // Population size (number of individuals).
#define seed 42                 // Psuedorandom number generator seed (std:srand(seed)).
#define maxgenerations 2000     // Maximum number of generations (while loop limit).
#define t 2                     // Tournament size (parents competing for selection).
#define verbose true            // Verbose output (cout) for verification.
#define printfitness false      // Best fitness per generation output (cout).
#define printrank 0            // Island (rank) to print out if verbose is true. 

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

  

    // Initialise Arrays on each island
    int m_fraction = m/world_size;
    //  p[m/worldsize][n] - Array to store population with m individuals with chromosome size n.
    int *p = static_cast<int*>(malloc((m_fraction)*n*sizeof(int)));
    //  q[m][n] - Array to store m children with chromosome size n.                 
    int *q = static_cast<int*>(malloc((m_fraction)*n*sizeof(int)));
    //  best - Best (highest) fitness of current generation.
    int best_island;
    int best_global;
    int best_rank=0;
    //  generation - While loop counter. Initialise first generation (generation 0).
    int generation = 0;
    //  fitness[maxgenerations] - Array to store best (highest) fitness per generation.
    int *fitness = static_cast<int*>(malloc((maxgenerations)*sizeof(int)));
   
   int *fitnesses = static_cast<int*>(malloc(world_size*sizeof(int)));
    
    // Deterministic and differe random seed for each island (rank).
    std::srand(seed+my_rank);
    // Initialise fraction of population on each island.

      
    if (verbose)
    {
      RandomPopulationVerbose(p, n, m_fraction, my_rank, printrank);
      best_island = MaxFitnessVerbose((int *)p, n, m_fraction, my_rank, printrank);
      best_global = best_island; // ***check logic if fails*** TBD
      
      while ((best_global != n) && (generation < maxgenerations))
      {
         fitness[generation] = best_island;
         if(my_rank==printrank)
         {
            std::cout << " ------------ Generation: " << generation << " Best Fitness: " << best_island << " --------------" << std::endl;
         }
         
         //CrossoverVerbose(t, (int *)p, (int *)q, n, m_fraction, my_rank, printrank);
         Crossover(t, (int *)p, (int *)q, n, m_fraction);
         //MutateVerbose((int *)q, n, m_fraction, my_rank, printrank);
         Mutate((int *)q, n, m_fraction);
         //NextGenerationVerbose((int *)p, (int *)q, n, m_fraction, my_rank, printrank);
         NextGeneration((int *)p, (int *)q, n, m_fraction);
         best_island = MaxFitness((int *)p, n, m_fraction);
        
         CompareRankFitnessVerbose(best_island, best_global, best_rank, fitnesses,  n,  my_rank,  printrank,  world_size);
         
         
         // if(my_rank==printrank)
         // {
         //    std::cout << "best_global outside" << best_global << std::endl;
         // }
         generation++;
      }
      fitness[generation] = best_island;
      if(my_rank==printrank)
      {
      //std::cout << " ------------ Generation: " << generation << " Best Fitness: " << fitness[generation] << " --------------" << std::endl;
      //std::cout << " ------------ Island: " << best_rank << " Best Global Fitness: " << best_global << " --------------" << std::endl;
      }


    }
    else
    {

    }


   MPI_Finalize();

}
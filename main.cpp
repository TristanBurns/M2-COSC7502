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

#define n 1024                  // Chromosome size (number of genes per individual).
#define m 128                    // Population size (number of individuals). **MUST BE A POWER OF 2**
#define seed 42                 // Psuedorandom number generator seed (std:srand(seed)).
#define maxgenerations 200000     // Maximum number of generations (while loop limit).
#define t 2                     // Tournament size (parents competing for selection).
#define verbose false            // Verbose output (cout) for verification.
#define printfitness true      // Best fitness per generation output (cout).
#define migration true        // Enables migration of (number of) migrants each generation in ring pattern between islands. 
#define migrants 1           // Number of individuals migrating each generation, must be less than m/number of islands. 


//######################################################################################
//####                                                                              ####
//####                         DO NOT MODIFY BELOW THIS LINE                        ####
//####                                                                              ####
//######################################################################################

#define migratetype 1           // 0 for ring migraion, 1 for random migration, default ring migration
#define printrank 0            // Island (rank) to print out if verbose is true.


using namespace std;
int main(int argc, char** argv)
{
   auto start = std::chrono::high_resolution_clock::now();

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
    int best_rank = 0;
    //  generation - While loop counter. Initialise first generation (generation 0).
    int generation = 0;
    //  fitness[maxgenerations] - Array to store best (highest) fitness per generation.
    int *fitness = static_cast<int*>(malloc((maxgenerations)*sizeof(int)));
    int *maxfitnesses = static_cast<int*>(malloc(world_size*sizeof(int)));
    int *rand_rank = static_cast<int*>(malloc(world_size*sizeof(int)));

    // Deterministic and different random seed for each island (rank).
    std::srand(seed+my_rank);
    // Initialise fraction of population on each island.
   if(my_rank==printrank)
   {
      std::cout << " INITIALISATION SUCCESSFUL --------------" << std::endl;
   }
         
   
    if (verbose)
    {
      RandomPopulation(p, n, m_fraction);
      best_island = MaxFitness((int *)p, n, m_fraction);
      best_global = best_island; // ***check logic if fails*** TBD
      
      while ((best_global != n) && (generation < maxgenerations))
      {
         fitness[generation] = best_island;
         if(my_rank==printrank)
         {
            std::cout << " ------------ Island: " << my_rank << " Generation: " << generation << " Best Fitness: " << best_island << " --------------" << std::endl;
         }
         
         //CrossoverVerbose(t, (int *)p, (int *)q, n, m_fraction, my_rank, printrank);
         Crossover(t, (int *)p, (int *)q, n, m_fraction);


         //MutateVerbose((int *)q, n, m_fraction, my_rank, printrank);
         Mutate((int *)q, n, m_fraction);


         //NextGenerationVerbose((int *)p, (int *)q, n, m_fraction, my_rank, printrank);
         NextGeneration((int *)p, (int *)q, n, m_fraction);
         if(migration)
         {
            Migrate((int *)p, n, m_fraction, migrants,  (int *)rand_rank, my_rank, printrank, world_size, migratetype);
         }
         

         best_island = MaxFitness((int *)p, n, m_fraction);


                
         CompareRankFitnessVerbose(best_island, best_global, best_rank, maxfitnesses,  n,  my_rank,  printrank,  world_size);
         
         generation++;
      }
      fitness[generation] = best_island;
      if(my_rank==printrank)
      {
         std::cout << " ------------ Generation: " << generation << " Best Fitness: " << fitness[generation] << " --------------" << std::endl;
      }
         
    }
    else
    {
      RandomPopulation(p, n, m_fraction);
      best_island = MaxFitness((int *)p, n, m_fraction);
      best_global = best_island; // ***check logic if fails*** TBD
      
      while ((best_global != n) && (generation < maxgenerations))
      {
         fitness[generation] = best_island;
         Crossover(t, (int *)p, (int *)q, n, m_fraction);
         Mutate((int *)q, n, m_fraction);
         NextGeneration((int *)p, (int *)q, n, m_fraction);
         if(migration)
         {
            Migrate((int *)p, n, m_fraction, migrants,  (int *)rand_rank, my_rank, printrank, world_size, migratetype);
         }
         best_island = MaxFitness((int *)p, n, m_fraction);
         CompareRankFitness(best_island, best_global, best_rank, maxfitnesses,  n,  world_size);
         generation++;
      }
      fitness[generation] = best_island;
    }
   
   PrintFitnesses(fitness, generation, my_rank, printrank, world_size);

   
   auto stop = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
   if (my_rank==printrank)
   {
      //TBD Time print function
      std::cout << "Runtime (microseconds): "<< duration << std::endl;
   }
   free(p);
   free(q);
   free(fitness);
   free(maxfitnesses);
   free(rand_rank);
   MPI_Finalize();
}
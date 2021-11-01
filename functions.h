#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void RandomPopulationVerbose(int *p, int n, int m, int my_rank, int print_rank);
void RandomPopulation(int *p, int n, int m);
int MaxFitnessVerbose(int *p, int n, int m, int my_rank, int print_rank);
int MaxFitness(int *p, int n, int m);
int IndividualFitness( int i, int *p, int n, int m);
int TournamentSelection(int tsize, int *p, int n, int m);
void CrossoverVerbose(int t, int *p, int *q, int n, int m, int my_rank, int print_rank);
void Crossover(int t, int *p, int *q, int n, int m);
void MutateVerbose(int *q, int n, int m, int my_rank, int print_rank);
void Mutate(int *q, int n, int m);
void NextGenerationVerbose(int *p, int *q, int n, int m, int my_rank, int print_rank);
void NextGeneration(int *p, int *q, int n, int m);
void PrintFitness(int fitness[], int generation);
void CompareRankFitnessVerbose(int best_island, int& best_global, int& best_rank, int* fitnesses,  int n, int my_rank, int print_rank, int world_size);
void CompareRankFitness(int best_island, int& best_global, int& best_rank, int* fitnesses,int n, int world_size);
void Migrate(int *p, int n, int m,int num_migrations, int my_rank, int world_size);

#endif

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

#endif

#include "functions.h"
#include <iostream>

// Macros for array pointer indexing.
#define p(I, J) *((p + (I)*n) + (J))
#define q(I, J) *((q + (I)*n) + (J))


void RandomPopulationVerbose(int *p, int n, int m, int my_rank)
/*
Fill static 2d int array at pointer *p with m indivduals with n
chromosmomes, gene values 0 or 1 (verbose cout).
*/
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            p(i, j) = ((int)std::rand() % 2);
            std::cout << p(i, j);
        }
        std::cout << " -> Individual " << i << " , Island "<< my_rank <<std::endl;
    }
    return;
}

void RandomPopulation(int *p, int n, int m)
/*
Fill static 2d int array at pointer *p with m indivduals with n
chromosmomes, gene values 0 or 1.
*/
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            p(i, j) = ((int)std::rand() % 2);
        }
    }
    return;
}

int MaxFitnessVerbose(int *p, int n, int m)
/*
Return integer of best (highest) fitness for the pointer *p with m indivduals with n
chromosmomes. Fitness is defined as the sum of the individuals chromosomes (verbose cout).
*/
{
    int best = 0;
    int besti = 0;
    int sum = 0;
    std::cout << "Running MaxFitness (Verbose)" << std::endl;
    for (int i = 0; i < m; i++)
    {
        sum = 0;
        for (int j = 0; j < n; j++)
        {
            std::cout << p(i, j);
            sum += p(i, j);
        }
        std::cout << " -> Individual " << i << ", Fitness: " << sum << std::endl;

        if (sum > best)
        {
            best = sum;
            besti = i;
        }
    }
    return best;
}

int MaxFitness(int *p, int n, int m)
/*
Return integer of best (highest) fitness for the pointer *p with m indivduals with n
chromosmomes. Fitness is defined as the sum of the individuals chromosomes.
*/
{
    int best = 0;
    int sum = 0;

    for (int i = 0; i < m; i++)
    {
        sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += p(i, j);
        }

        if (sum > best)
        {
            best = sum;
        }
    }
    return best;
}

int IndividualFitness(int i, int *p, int n, int m)
/*
Return integer fitness for the individual i in population array *p with m indivduals with n
chromosmomes. Fitness is defined as the sum of the individuals chromosomes.
*/
{
    int sum = 0;
    for (int j = 0; j < n; j++)
    {
        sum += p(i, j);
    }
    return sum;
}

int TournamentSelection(int tsize, int *p, int n, int m)
/*
Perform tsize torunament selection on population at array *p with m indivduals with n
chromosmomes. Randomly sample with replacement tsize individuals and return integer
index of individual with highest fitness sampled. 
*/
{
    int sumi;
    int sum;
    int besti;
    int best = 0;

    besti = (std::rand() % m);
    best = IndividualFitness(besti, p, n, m);

    for (int i = 0; i < tsize; i++)
    {
        sumi = (std::rand() % m);
        sum = IndividualFitness(sumi, p, n, m);
        if (sum > best)
        {
            besti = sumi;
            best = sum;
        }
    }
    return besti;
}

void CrossoverVerbose(int t, int *p, int *q, int n, int m)
/*
Perform single point crossover on parents from tournament selection of size t from population array *p.
Fill array *q with childeren from single point crossover (verbose cout).
*/
{
    int c = 0;
    int individual1;
    int individual2;
    std::cout << "Running Crossover (Verbose)" << std::endl;
    for (int i = 0; i < m; i += 2)
    {
        c = (std::rand() % n);
        individual1 = TournamentSelection(t, p, n, m);
        individual2 = TournamentSelection(t, p, n, m);
        for (int j = 0; j < c; j++)
        {
            q(i, j) = p(individual1, j);
            q(i + 1, j) = p(individual2, j);
        }

        for (int j = c; j < n; j++)
        {
            q(i, j) = p(individual2, j);
            q(i + 1, j) = p(individual1, j);
        }

        std::cout << "Crossover at chromosome " << c << ":" << std::endl;

        for (int j = 0; j < n; j++)
        {
            if (j == c)
            {
                std::cout << "|" << p(individual1, j);
            }
            else
            {
                std::cout << p(individual1, j);
            }
        }
        std::cout << " -> Parent 1 (Individual " << individual1 << ")";
        std::cout << std::endl;
        for (int j = 0; j < n; j++)
        {
            if (j == c)
            {
                std::cout << "|" << p(individual2, j);
            }
            else
            {
                std::cout << p(individual2, j);
            }
        }
        std::cout << " -> Parent 2 (Individual " << individual2 << ")";
        std::cout << std::endl;

        for (int j = 0; j < n; j++)
        {
            if (j == c)
            {
                std::cout << "|" << q(i, j);
            }
            else
            {
                std::cout << q(i, j);
            }
        }
        std::cout << " -> Child " << i ;
        std::cout << std::endl;

        for (int j = 0; j < n; j++)
        {
            if (j == c)
            {
                std::cout << "|" << q(+1, j);
            }
            else
            {
                std::cout << q(i + 1, j);
            }
        }
        std::cout << " -> Child " << i + 1 ;
        std::cout << std::endl;
    }
    return;
}

void Crossover(int t, int *p, int *q, int n, int m)
/*
Perform single point crossover on parents from tournament selection of size t from population array *p.
Fill array *q with childeren from single point crossover.
*/
{
    int c = 0;
    int individual1;
    int individual2;

    for (int i = 0; i < m; i += 2)
    {
        c = (std::rand() % n);
        individual1 = TournamentSelection(t, p, n, m);
        individual2 = TournamentSelection(t, p, n, m);
        for (int j = 0; j < c; j++)
        {
            q(i, j) = p(individual1, j);
            q(i + 1, j) = p(individual2, j);
        }

        for (int j = c; j < n; j++)
        {
            q(i, j) = p(individual2, j);
            q(i + 1, j) = p(individual1, j);
        }
    }

    return;
}

void MutateVerbose(int *q, int n, int m)
/*
Perform random bit flip mutation on individuals in array *q of m individuals
with chromosome length n.  Each chromosome has a probablility 1/n of having a 
bitflip mutation applied (verbose cout).
*/
{
    int c;
    int mu;
    bool mutated;

    std::cout << "Running Mutate (Verbose)" << std::endl;

    for (int i = 0; i < m; i++)
    {
        mutated = false;

        for (int j = 0; j < n; j++)
        {
            mu = (std::rand() % n);
            if (mu == 0)
            {
                (q(i, j)) = 1 - (q(i, j));
                mutated = true;
                c = j;
                std::cout << "*" << q(i, j) << "*";
            }
            else
            {
                std::cout << " " << q(i, j) << " ";
            }
        }

        if (mutated)
        {
            std::cout << "-> Child " << i << " Mutation at *_* " << std::endl;
        }

        else
        {
            std::cout << std::endl;
        }
    }
    return;
}

void Mutate(int *q, int n, int m)
/*
Perform random bit flip mutation on individuals in array *q of m individuals
with chromosome length n.  Each chromosome has a probablility 1/n of having a 
bitflip mutation applied (verbose cout).
*/
{
    int mu;

    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < n; j++)
        {
            mu = (std::rand() % n);
            if (mu == 0)
            {
                (q(i, j)) = 1 - (q(i, j));
            }
        }

    }
    return;
}



void NextGenerationVerbose(int *p, int *q, int n, int m)
/*
Assign children in array *q to population in array *p for next generation (verbose cout).
*/
{
    std::cout << "Assigning next generation (Verbose)" << std::endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << q(i, j);
            p(i, j) = q(i, j);
        }
        std::cout <<" -> Child " << i << " to Individual " << i << ", Fitness: " << IndividualFitness(i, p, n, m) << std::endl;
    }
}

void NextGeneration(int *p, int *q, int n, int m)
/*
Assign children in array *q to population in array *p for next generation.
*/
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            p(i, j) = q(i, j);
        }
    }
}

void PrintFitness(int fitness[], int generation)
/*
Print (cout) array comma separated values for generation and best (maximum) fitness.
*/
{
    std::cout << "Generation"
              << ","
              << "Best Fitness" << std::endl;
    for (int i = 0; i < (generation + 1); i++)
    {
        std::cout << i << "," << fitness[i] << std::endl;
    }
}
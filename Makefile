all:
	mpic++ -std=c++11 -w -g -O3 -funroll-loops -flto -fuse-linker-plugin functions.cpp main.cpp -o GeneticAlgorithm 


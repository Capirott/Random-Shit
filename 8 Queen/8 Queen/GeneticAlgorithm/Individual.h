#pragma once
#include <vector>

class Individual
{
private:
	int *chromosome;
	int size;
public:
	int fitness();
	void mutate(int rate);
	void setChromosome(int *, int size);
	int getChromosome(int);
	void printMatrix();
	bool is_A_Solution();
	int heuristic();  // Created for determinating the number of threatened queens
	Individual(Individual &);
	Individual();
	~Individual(); 
	Individual* operator+(Individual &);
	bool operator==(Individual &);
	bool operator<(Individual &);
};


#pragma once
#include "Population.h"
#include <vector>

class GeneticAlgorithm
{
	std::vector<Population *> population; 
	int nQueens;
	int pSize;
	int mProb;
public:
	GeneticAlgorithm(int *, int, int, int);
	Individual* solve(int &, int);
	~GeneticAlgorithm(void);
};


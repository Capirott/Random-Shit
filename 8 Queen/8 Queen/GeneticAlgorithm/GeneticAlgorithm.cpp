#include "GeneticAlgorithm.h"
#include "Population.h"
#include "Individual.h"
#include <iostream>
using namespace std;
GeneticAlgorithm::GeneticAlgorithm(int *chromosome, int nQueens, int pSize, int mProb)
{
	this->nQueens		= nQueens;
	this->pSize			= pSize;
	this->mProb			= mProb;
	
	Population *nPop	= new Population();
	
	Individual *god = new Individual;	
	god->setChromosome(chromosome, nQueens);
	nPop->addSubject(god);

	int *tmp = new int[nQueens];

	for (int j = 0; j < nQueens; ++j)
	{
		tmp[j] = j;
	}	
	Individual subject;
	subject.setChromosome(tmp, nQueens);

	Individual *child;
	for (int i = 1; i < pSize; ++i)
	{	// Generation of the first population subjects
		subject.mutate(100);
		while (!nPop->addSubject(child = *god + subject))
		{			
			delete child;
			subject.mutate(100);
		}
	}	

	population.push_back(nPop); // First generation added successfully	
}


GeneticAlgorithm::~GeneticAlgorithm(void)
{
}

Individual* GeneticAlgorithm::solve(int &n, int limit)
{

	for (n = 1; n < limit && !population.at(n - 1)->getBestSubject()->is_A_Solution(); ++n)
	{
		population.push_back(new Population);
		for (int i = 0; i < pSize; ++i)
		{
			Individual *child = population.at(n - 1)->crossOver();
			child->mutate(mProb);
			while (!population.at(n)->addSubject(child))
			{
				delete child;
				child = population.at(n - 1)->crossOver();
				child->mutate(mProb);
			}
		}
	}	
	return population.at(n - 1)->getBestSubject();
}
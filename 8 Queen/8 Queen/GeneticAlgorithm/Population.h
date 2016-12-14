#pragma once
#include <vector>

using std::vector;

class Individual;

class Population
{
	int pSize;
	int fSum;
private:
	vector<Individual *> subject;
public:
	Population();
	~Population(void);
	bool addSubject(Individual *);
	Individual* getBestSubject();
	Individual* crossOver();
	Individual* randomSelection();
	Individual* roulleteWheelSelection();
};


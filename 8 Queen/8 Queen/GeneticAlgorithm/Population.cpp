#include "Population.h"
#include "Individual.h"
#include <algorithm>

bool myfunc(Individual *a, Individual *b)
{
	return (*a < *b);
}

Population::Population()
{
	this->pSize = 0;
	this->fSum	= 0;
}


Population::~Population(void)
{
}


bool Population::addSubject(Individual *in)
{
	for (int i = 0; i < subject.size(); ++i)
	{
		if (*in == *subject.at(i))
			return false;
	}
	subject.push_back(in);
	std::sort(subject.begin(), subject.end(), myfunc);
	pSize++;
	fSum += in->fitness();
	return true;
}

Individual* Population::getBestSubject()
{
	return *(subject.end() - 1);
}

Individual* Population::randomSelection()
{
	
	return subject.at(rand() % pSize);
}


Individual* Population::roulleteWheelSelection()
{
	int k			= 0;
	int f			= 0;
	f = rand() % fSum;
	for (int i = 0; i < pSize; ++i)
	{
		k += subject.at(i)->fitness();
		if (f <= k)
			return subject.at(i);
	}
	return 0;
}

Individual* Population::crossOver()
{
	return *roulleteWheelSelection() + *roulleteWheelSelection();
}
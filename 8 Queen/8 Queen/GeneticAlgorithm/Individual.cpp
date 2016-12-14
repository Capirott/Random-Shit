#include "Individual.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>

using std::cout;
using std::swap;
using std::endl;
using std::left;
using std::setw;
using std::vector;
using std::abs;

Individual::Individual()
{
	chromosome = 0;
}

int Individual::fitness()
{
	int f = 0.5 * (size * size - size);
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (chromosome[i] == chromosome[j] || chromosome[i] - i == chromosome[j] - j || chromosome[i] + i == chromosome[j] + j)
			{
				f--;
			}
		}
	}
	return f;
}

int Individual::heuristic()
{
	return 0.5 * (size * size - size) - fitness();
}

void Individual::setChromosome(int *chromosome, int size)
{
	this->chromosome	= chromosome;
	this->size			= size;
}

void Individual::mutate(int rate)
{	// Exchange mutation
	int p = rand() % 101;
	if (p <= rate)
	{
		int i = rand() % size;
		int j = rand() % size;
		while (j == i)
			j = rand() % size;
		swap(chromosome[i], chromosome[j]);
	}	
}

int Individual::getChromosome(int i)
{
	return chromosome[i];
}
void Individual::printMatrix()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (chromosome[j] == i)
			{
				cout << left << setw(5) << 'Q';
			}
			else
			{
				swap(chromosome[j], i);
				cout << left << setw(5) << fitness();
				swap(chromosome[j], i);
			}
		}
		cout << endl << endl;
	}
	cout << endl << endl << endl;
}

Individual::~Individual()
{
	delete[] chromosome;
}

Individual* Individual::operator+(Individual &parent)
{
	Individual *child	= new Individual;
	int *tmp			= new int[size];
	int nSwap			= rand() % size / 2;

	for (int i = 0; i < size; ++i)
	{
		tmp[i] = chromosome[i];
	}

	for (int i = 0; i < nSwap; ++i)
	{
		int j = rand() % size;
		int	k;
		for (k = 0; k < size; ++k)
		{
			if (parent.chromosome[j] == chromosome[k])
				break;
		}
		swap(tmp[j], tmp[k]);
	}
	child->setChromosome(tmp, size);
	return child;
}

bool Individual::is_A_Solution()
{
	if ( 0.5 * (size * size - size)  == fitness() )
		return true;
	return false;
}

Individual::Individual(Individual &tmp)
{
	chromosome = new int[size];
	for (int i = 0; i < size; ++i)
	{
		chromosome[i] = tmp.chromosome[i];
	}
}

bool Individual::operator<(Individual &in)
{
	return (this->fitness() < in.fitness());
}


bool Individual::operator==(Individual &in)
{
	for (int i = 0; i < size; ++i)
	{
		if (chromosome[i] != in.chromosome[i])
			return false;
	}
	return true;
}
#include "HillClimbing.h"
#include <iostream>
#include <iomanip>

using std::swap;
using std::cout;
using std::endl;
using std::setw;
using std::left;


int HillClimbing::heuristic(int *queenPosition, int nQueen)
{
	int h = 0;
	for (int i = 0; i < nQueen - 1; ++i)
	{
		for (int j = i + 1; j < nQueen; ++j)
		{
			if (queenPosition[i] == queenPosition[j] || queenPosition[i] - i == queenPosition[j] - j || queenPosition[i] + i == queenPosition[j] + j)
			{
				h++;
			}
		}
	}
	return h;
}

int HillClimbing::getBestHeuristic(int *queenPosition, int nQueen, int &r, int &c)
{
	int hBest = (nQueen * nQueen - nQueen) * 0.5;
	for (int i = 0; i < nQueen; ++i)
	{
		for (int j = 0; j < nQueen; ++j)
		{
			if (queenPosition[j] != i)
			{
				swap(queenPosition[j], i);
				int h = heuristic(queenPosition, nQueen);
				if (h < hBest)
				{
					hBest = h;
					r = queenPosition[j];
					c = j;
				}
				else
				{					
					if (h == hBest)
					{ 
						if (rand() % 2)
						{	// used for picking another path
							r = queenPosition[j];
							c = j;
						}
					}
				}
				swap(queenPosition[j], i);
			}
		}
	}
	return hBest;
}

int HillClimbing::solve(int *queenPosition, int nQueen, int &n, int limit)
{
	int h, r, c;
	n = 0;
	do
	{
		h = getBestHeuristic(queenPosition, nQueen, r, c);
		swap(queenPosition[c], r);
	} while (h && ++n < limit);
	return h;
}

void HillClimbing::printMatrix(int *queenPosition, int nQueen)
{
	for (int i = 0; i < nQueen; ++i)
	{
		for (int j = 0; j < nQueen; ++j)
		{
			if (queenPosition[j] == i)
			{
				cout << left << setw(5) << 'Q';
			}
			else
			{
				swap(queenPosition[j], i);
				cout << left << setw(5) << heuristic(queenPosition, nQueen);
				swap(queenPosition[j], i);
			}
		}
		cout << endl << endl;
	}
	cout << endl << endl << endl;
}

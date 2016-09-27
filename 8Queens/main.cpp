#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

#define N 8

int heuristic(int queenPosition[N])
{
	int h = 0;	
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			if (queenPosition[i] == queenPosition[j] || queenPosition[i] - i == queenPosition[j] - j || queenPosition[i] + i == queenPosition[j] + j)
			{
				h++;
			}
		}
	}
	return h;
}

void printMatrix(int queenPosition[N])
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (queenPosition[j] == i)
			{
				cout << left << setw(5) << 'Q';
			}
			else
			{
				swap(queenPosition[j], i);
				cout << left << setw(5) << heuristic(queenPosition);
				swap(queenPosition[j], i);
			}
		}
		cout << endl << endl;
	}
	cout << endl << endl << endl;
}

int getBestHeuristic(int queenPosition[N], int &r, int &c)
{
	int hBest = N * 1000;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{				
			if (queenPosition[j] != i) 
			{
				swap(queenPosition[j], i);
				int h = heuristic(queenPosition);
				if (h < hBest)
				{
					hBest = h;
					r = queenPosition[j];
					c = j;
				}
				swap(queenPosition[j], i);
			}
		}
	}


	return hBest;
}

int main()
{
	int queenPosition[N]	= {4, 5, 6, 3, 4, 5 , 6, 5};
	int h, x = 0, r, c;
		srand(time(NULL));
	for (int i = 0; i < N; ++i)
	{	
		queenPosition[i] = rand() % N;
	}
	do 
	{
		cout << "Actual heuristic: " << (h = heuristic(queenPosition)) << endl;
		cout << "Best heuristic: " << (h = getBestHeuristic(queenPosition, r, c));
		cout << "(" << r << ", " << c << ")" << endl;
		printMatrix(queenPosition);
		swap(queenPosition[c], r);
	} while (h && x++ < 10);
	cout << "Last Result: \n";
	cout << "Best heuristic found: " << (h = heuristic(queenPosition)) << endl;
	printMatrix(queenPosition);
	getchar();
	return 0;
}

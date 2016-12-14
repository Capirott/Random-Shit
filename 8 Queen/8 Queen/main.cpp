#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GeneticAlgorithm\GeneticAlgorithm.h"
#include "GeneticAlgorithm\Individual.h"
#include "HillClimbing\HillClimbing.h"

using namespace std;

#define NUMBER_OF_QUEENS		numberOfQueens[l]
#define POPULATION_SIZE			numberOfQueens[l]
#define MUTATION_PROBABILITY	20
#define NUMBER_OF_ITERATIONS    200
#define NUMBER_OF_SOLUTIONS		100

int main(void)
{
	int numberOfQueens[] = { 5, 10, 15, 20, 30, 50};
	for (int l = 0; l < 6; ++l)
	{
		int tGa = 0;
		int nGa = 0;
		int tHl = 0;
		int nHl = 0;
		int h = 0;
		srand(time(0));
		for (int i = 0; i < NUMBER_OF_SOLUTIONS; ++i)
		{
			int *queenPosition = new int [NUMBER_OF_QUEENS];
			for (int i = 0; i < NUMBER_OF_QUEENS; ++i)
			{
				queenPosition[i] = i;
			}
			int nSwap = rand() % NUMBER_OF_QUEENS / 2;
			for (int i = 0; i < nSwap; ++i)
			{
				swap(queenPosition[rand() % NUMBER_OF_QUEENS], queenPosition[rand() % NUMBER_OF_QUEENS]);
			}
			int n;
			GeneticAlgorithm ga(queenPosition, NUMBER_OF_QUEENS, POPULATION_SIZE, MUTATION_PROBABILITY);
			Individual *solution = ga.solve(n, NUMBER_OF_ITERATIONS);
			h = solution->heuristic();
			//cout << "Genetic Algorithm:\n";
			//cout << "Number of threatened queens: " << h << endl;
			//cout << "Iterarions: " << n << endl << endl;
			tGa += h;
			nGa += n;
			tHl += h = HillClimbing::solve(queenPosition, NUMBER_OF_QUEENS, n, NUMBER_OF_ITERATIONS);
			nHl += n;
			//cout << "Hill Climbing Algorithm:\n";
			//cout << "Number of threatened queens: " << h << endl;
			//cout << "Iterarions: " << n << endl << endl;
		}
		cout << "Number of queens: " << NUMBER_OF_QUEENS << endl;
		cout << "Genetic Algorithm:\nIterations Average: " << nGa / NUMBER_OF_SOLUTIONS << "\nNumber of threatned queens average: " << tGa / NUMBER_OF_SOLUTIONS << endl << endl;
		//cout << "Hill Climbing:\nIterations Average: " << nHl / NUMBER_OF_SOLUTIONS << "\nNumber of threatned queens average: " << tHl / NUMBER_OF_SOLUTIONS << endl << endl << endl;
	}
	getchar();
	return 0;
}
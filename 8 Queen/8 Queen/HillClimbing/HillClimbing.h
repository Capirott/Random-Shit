#pragma once
class HillClimbing
{
public:
	static int heuristic(int *, int);
	static int getBestHeuristic(int*, int, int&, int&);
	static int solve(int *, int, int &, int);
	static void printMatrix(int *, int);
};


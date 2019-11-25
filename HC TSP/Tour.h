#pragma once

#include <vector>
#include "Graph.h"
#include <iostream>

using namespace std;

bool canGo(int m[10][10], int x, int y)
{
	if (m[x][y] != -2) return true;
	else return false;
}

bool isValidTour(int m[10][10], vector<unsigned> tour)
{
	for (unsigned i = 0; i < tour.size() - 1; i++)
		if (!canGo(m, tour[i], tour[i + 1])) return false;
	return true;
}

bool createValidTour(vector<unsigned>& tour, Graph *g)
{
	for (unsigned i = 1; i < tour.size() - 1; i++)
	{
		for (unsigned j = i + 1; j < tour.size() - 1; j++)
		{
			unsigned aux = tour[i];
			tour[i] = tour[j];
			tour[j] = aux;
			if (isValidTour(g->gDist, tour)) return true;
		}
	}
	return false;
}

int custo(vector<unsigned> tour, Graph* g)
{
	int cost = 0;
	if (isValidTour(g->gDist, tour))
	{
		for (unsigned i = 0; i < tour.size() - 1; i++)
			cost += g->gDist[tour[i]][tour[i + 1]];
		return cost;
	}
	else return INT_MAX;
}

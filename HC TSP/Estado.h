#pragma once

#include <vector>
#include "Graph.h"
#include "Tour.h"

using namespace std;

class Estado
{
public:

	vector <unsigned> tour;
	int cost;

	Estado(vector<unsigned> touri, Graph *g)
	{
		this->tour = touri;
		this->cost = custo(tour, g);
	}

	void toString()
	{
		cout << "Custo: " << this->cost << endl << "Tour sequence: ";
		for (int i = 0; i < this->tour.size(); i++)
			cout << this->tour[i] << " ";
		cout << endl;
	}

	

};
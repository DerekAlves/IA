#include <vector>
#include <algorithm>
#include <time.h>
#include "Graph.h"
#include "Estado.h"
#include "Tour.h"

using namespace std;

bool operator<(Estado a, Estado b)
{
	return a.cost < b.cost;
}

void hc(vector<unsigned> init, Graph *g, Estado& best, unsigned depth)
{
	vector<unsigned> aux(11);
	if (depth < 3)
	{
		for(int i = 1; i < 10; i++)
			for (int j = 1; j < 10; j++)
			{
				if (i != j)
				{
					for (unsigned k = 0; k < init.size(); k++)
						aux[k] = init[k];

					swap(aux[i], aux[j]);
					Estado next = Estado(aux, g);
					
					if (isValidTour(g->gDist, next.tour))
						best = min(next, best);
					hc(aux, g, best, depth + 1);
				}
			}
	}

	return;
}

void restart(int cities[10], Estado &melhor, Graph *g, int interaction)
{

	vector<unsigned> initialTour;

	initialTour.push_back(cities[0]);
	for (int i = 1; i < 10; i++)
		initialTour.push_back(cities[i]);// creating valid tour 
	initialTour.push_back(cities[0]);


	Estado atual = Estado(initialTour, g);
	hc(initialTour, g, atual, 0);
	if (isValidTour(g->gDist, atual.tour))
	{
		melhor = min(atual, melhor);
	}

	cout << "Melhor ate o reinicio: " << interaction << endl;
	melhor.toString();
	cout << "----------------------------------------------------------\n";
}



int main()
{
	cout << "Rodando Hill-Climbing 20 vezes com reinicio aleatorio! Aguarde..." << endl;
	srand(time(NULL));
	int options[10] = { 0 };
	int cities[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int index;

	vector<unsigned> initialTour;

	initialTour.push_back(cities[0]);
	for (int i = 1; i < 10; i++)
		initialTour.push_back(cities[i]);// creating valid tour 
	initialTour.push_back(cities[0]);

	Graph* g = new Graph();

	Estado melhor = Estado(initialTour, g);


	for (int j = 20; j ; j--)
	{
		for (int i = 0; i < 10; i++)
		{
			index = rand() % 10;
			while (options[index] != 0)
				index = rand() % 10;
			options[index] = 1;
			cities[i] = index;
		}
		memset(options, 0, sizeof(options));

		restart(cities, melhor, g, (20 - j) + 1);

	}
	cout << "Melhor solucao: ";
	melhor.toString();
	cout << endl;
	return 0;
}

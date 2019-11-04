// IA - Missionários e canibais.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <vector>
#include <queue>
#include "Estado.h"

using namespace std;

void printSolution(Estado* solucao)//Recursivamente, printa a solução começando pela raiz, (3,3) | (0,0)
{
	if (solucao == NULL) return;
	else
	{
		printSolution((solucao->pai));
		solucao->toString();
	}
}

int main()
{
	cout << "Bem vindo a um solucionador para o problema dos missionarios e canibais utilizando bfs!\n" << "#############################################################\n";
	Estado *raiz = new Estado();
	Estado *atual = NULL;
	Estado *filho;

	queue<Estado*> fronteira;
	vector<Estado*> estados;
	fronteira.push(raiz);

	int c[5] = { 2, 1, 1, 0, 0 };
	int m[5] = { 0, 0, 1, 1, 2 };

	bool foundSolution = false;
	bool empty = false;

	cout << "Iniciando BFS, aguarde...\n" << "#############################################################\n";

	while (!foundSolution && !empty)
	{
		if (!fronteira.empty())
		{
			atual = fronteira.front();
			fronteira.pop();
			if ( atual -> isValidSolution() && atual -> isNotRepeated(estados))
			{
				estados.push_back(atual);
				if (!atual -> isSolution())
				{
					for (unsigned i = 0; i < 5; i++)
					{
						filho = new Estado(m[i], c[i], atual);
						if (filho->isValidSolution() && filho -> isNotRepeated(estados))
						{
							fronteira.push(filho);
							atual->filhos.push_back(filho);
						}
					}

				}
				else
				{
					cout << "Solucao encontrada!\n";
					atual -> toString();
					foundSolution = atual -> isSolution();
				}
			}
		}
		else
		{
			cout << "Fronteira vazia!\nSolucao nao encontrada!\n";
			empty = true;
		}
	}

	if (foundSolution)
	{
		cout << "Apresentando solucao! --------------------------------------------------------\n";
		printSolution(atual);
	}
	
	return 0;
}
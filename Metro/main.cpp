#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include "Estado.h"
#include "Instancia.h"

using namespace std;

float h(float g[14][14], unsigned s, unsigned e)
{
	return g[s][e];
}


bool verifyLine(vector<unsigned> linha, unsigned s, unsigned e)
{
	unsigned found = 0;
	for (unsigned i = 0; i < linha.size(); i++)
	{
		if (linha[i] == s) found++;
		if (linha[i] == e) found++;
		if (found == 2) return true;
	}
	return false;

}

bool sameLine(vector<unsigned> linha[4], unsigned line, unsigned d)
{
	for (unsigned i = 0; i < linha[line].size(); i++)
	{
		if (linha[line][i] == d) return true;
	}
		
	return false;
}


unsigned findLine(vector<unsigned> linha[4], unsigned s, unsigned e)
{
	unsigned i;
	for (i = 0; i < 4; i++)
		if (verifyLine(linha[i], s, e)) return i + 1;
	return 0;
}
void printSolution(Estado* solucao)//Recursivamente, printa a solução começando pela raiz.
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
	cout << "Iniciando A* para o problema do metro de Paris!" << endl;
	Instancia instance = Instancia();
	unsigned s, e, line;
	
	cout << "Digite um numero de 1 a 14 representando a estacao de partida: ";
	cin >> s;
	cout << "Digite um numero de 1 a 4 representando a linha de partida: ";
	cin >> line;
	cout << "Digite um numero de 1 a 14 representando a estacao de destino: ";
	cin >> e;
	cout << endl;

	Estado* raiz = new Estado(s, line, 0);
	Estado* atual = NULL;
	Estado* next;
	bool foundSolution = false;

	priority_queue <Estado*, vector<Estado*>, greater<Estado*>> fronteira;
	fronteira.push(raiz);

	while (!foundSolution && !fronteira.empty())
	{
		atual = fronteira.top();
		fronteira.pop();

		if (!atual->isSolution(e))
		{
			for (unsigned i = 0; i < 14; i++)
			{
				if (instance.g[atual->estacao-1][i] != 0)
				{
					if (sameLine(instance.linha, atual->linha-1, i+1))
						next = new Estado(atual, h(instance.gTime, atual->estacao -1, i), i+1, atual->linha, h(instance.gTime, i, e-1));
					else
					{
						line = findLine(instance.linha, atual->estacao, i+1);
						next = new Estado(atual, h(instance.gTime, atual->estacao - 1, i) + 4, i + 1, line, h(instance.gTime, i, e-1));
					}
					fronteira.push(next);
					atual->filhos.push_back(next);
				}
			}
		}
		else { cout << "SOLUCAO ENCONTRADA!###########################\n"; foundSolution = true; }
	}
	
	printSolution(atual);

	return 0;
}
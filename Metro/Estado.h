#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Estado
{
public:

	Estado* pai;
	vector <Estado*> filhos;
	float custo;
	unsigned profundidade;
	unsigned estacao;
	unsigned linha;
	float heuristica;
	
	bool operator<(Estado* b)
	{
		return (this->custo + this->heuristica) < (b->custo + b->heuristica);
	}

	Estado(unsigned estacao, unsigned linha, float h)// construtor
	{
		this->pai = NULL;
		this->custo = 0;
		this->profundidade = 0;
		this->estacao = estacao;
		this->linha = linha;
		this->heuristica = h;
	}

	Estado(Estado* pai, float custo, unsigned estacao, unsigned linha, float h)// construtor
	{
		this->pai = pai;
		this->custo = pai->custo + custo;
		this->profundidade = pai->profundidade + 1;
		this->estacao = estacao;
		this->linha = linha;
		this->heuristica = h;
	}

	/*~Estado();*/

	void toString()
	{
		cout << "Estacao: " << this->estacao << "\nLinha: " << this->linha << "\nCusto: " << this->custo << " minutos\nProfundidade: " << this->profundidade << "\nHeuristica: " << this->heuristica << " minutos\n____________________________________________________________________________________\n";
	}

	bool isSolution(unsigned e)
	{
		if (this->estacao == e) return true;
		else return false;
	}
};
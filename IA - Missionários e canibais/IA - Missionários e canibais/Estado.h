#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Estado
{
public:

	Estado* pai;
	vector <Estado*> filhos;
	pair<int, int> margemE, margemD; // first -> missionários, second -> canibais

	bool atMargemE;

	Estado()
	{
		this->pai = NULL;
		this->margemE.first = this->margemE.second = 3;
		this->margemD.first = this->margemD.second = 0;
		this->atMargemE = true;
	}

	Estado(int m, int c, Estado* pai)
	{
		this->atMargemE = !(pai->atMargemE);
		this->pai = pai;
		this->margemE.first = pai->margemE.first;
		this->margemE.second = pai->margemE.second;
		this->margemD.first = pai->margemD.first;
		this->margemD.second = pai->margemD.second;

		if (pai->atMargemE)
		{
			this->margemE.first -= m;
			this->margemE.second -= c;
			this->margemD.first += m;
			this->margemD.second += c;
		}
		else 
		{
			this->margemE.first += m;
			this->margemE.second += c;
			this->margemD.first -= m;
			this->margemD.second -= c;
		}
	}

	/*~Estado();*/

	void toString()
	{
		printf("MargemE(%d, %d) | MargemD(%d, %d) | Lado: %d\n", this->margemE.first, this->margemE.second, this->margemD.first, this->margemD.second, this->atMargemE);
	}

	bool isSolution()
	{
		return (this->margemE.first == 0 && this->margemE.second == 0 && this->margemD.first == 3 && this->margemD.second == 3);
	}

	bool isValidSolution()
	{

		if (this->margemE.first		< 0 ||
			this->margemE.first		> 3 ||
			this->margemE.second	< 0 ||
			this->margemE.second	> 3 ||
			this->margemD.first		< 0 ||
			this->margemD.first		> 3 ||
			this->margemD.second	< 0 ||
			this->margemD.second	> 3) return false;

		if ((this->margemE.first > 0 && this->margemD.first > 0)	&&
			((this->margemE.second > this->margemE.first)			||
			(this->margemD.second > this->margemD.first))) return false;
		else return true;
	}

	bool isNotRepeated(vector<Estado*> estados) // trata estados repetidos
	{
		for (unsigned i = 0; i < estados.size(); i++)
			if (this->margemE == estados[i]->margemE && this->margemD == estados[i]->margemD && this->atMargemE == estados[i]->atMargemE) return false;

		return true;
	}
};
#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Instancia
{
public:

	unsigned estacoes = 14;
	float gTime[14][14] = { 0 };
	unsigned g[14][14] =  {	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					/*2*/	{1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
					/*3*/	{0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
					/*4*/	{0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
					/*5*/	{0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
					/*6*/	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					/*7*/	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					/*8*/	{0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0},
					/*9*/	{0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
					/*10*/	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					/*11*/	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
					/*12*/	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
					/*13*/	{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					/*14*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}	};
	
	vector <unsigned> linha[4];

	Instancia()
	{
		unsigned gk[14][14] = {	{	NULL, 11,   20,   27,   40,   43,   39,   28,   18,   10,   18,   30,   30,   32	},
						/*2*/	{	11,	  NULL, 9,    16,   29,   32,   28,   19,   11,   4,    17,   23,   21,   24	},
						/*3*/	{	20,	  9,    NULL,  7,   20,   22,   19,   15,   10,   11,   21,   21,   13,   18	},
						/*4*/	{	27,   16,   7,    NULL, 13,   16,   12,   13,   13,   18,   26,   21,   11,   17	},
						/*5*/	{	40,	  29,   20,   13,   NULL, 3,    2,    21,   25,   31,   38,   27,   16,   20	},
						/*6*/	{	43,   32,   22,   16,   3,    NULL, 4,    23,   28,   33,   41,   30,   17,   20	},
						/*7*/	{	39,	  28,   19,   12,   2,    4,    NULL, 22,   25,   29,   38,   28,   13,   17	},
						/*8*/	{	28,   19,   15,   13,   21,   23,   22,   NULL, 9,    22,   18,   7,    25,   30	},
						/*9*/	{	18,   11,   10,   13,   25,   28,   25,   9,    NULL, 13,   12,   12,   23,   28	},
						/*10*/	{	10,   4,    11,   18,   31,   33,   29,   22,   13,   NULL, 20,   27,   20,   23	},
						/*11*/	{	18,   17,   21,   26,   38,   41,   38,   18,   12,   20,   NULL, 15,   35,   39	},
						/*12*/	{	30,   23,   21,   21,   27,   30,   28,   7,    12,   27,   15,   NULL, 31,   37	},
						/*13*/	{	30,   21,   13,   11,   16,   17,   13,   25,   23,   20,   35,   31,   NULL, 5		},
						/*14*/	{	32,	  24,   18,   17,   20,   20,   17,   30,   28,   23,   39,   37,   5,    NULL	}	};

		unsigned l1[6] = { 1, 2, 3, 4, 5, 6 };
		unsigned l2[6] = { 7, 5, 8, 9, 2, 10 };
		unsigned l3[6] = { 11, 9, 3, 13 };
		unsigned l4[6] = { 12, 8, 4, 13, 14 };

		for (unsigned i = 0; i < 14; i++)
			for (unsigned j = 0; j < 14; j++)
			{
				if (gk[i][j] != NULL)
					this->gTime[i][j] = (float)(gk[i][j] * 60) / (float)30;
				else this -> gTime[i][j] = 0;
			}
				
			
		for (unsigned i = 0; i < 6; i++)
			this->linha[0].push_back(l1[i]);
		for (unsigned i = 0; i < 6; i++)
			this->linha[1].push_back(l2[i]);
		for (unsigned i = 0; i < 4; i++)
			this->linha[2].push_back(l3[i]);
		for (unsigned i = 0; i < 5; i++)
			this->linha[3].push_back(l4[i]);
	}

	void printInstance()
	{
		for (unsigned i = 0; i < estacoes; i++)
		{
			printf("| ");
			for (unsigned j = 0; j < estacoes; j++)
				printf("%5.2lf ", this->gTime[i][j]);
			printf("|\n");
		}


		printf("Linha 1 ----------\n");
		for (unsigned i = 0; i < this->linha[0].size(); i++)
			printf("%u ", this->linha[0][i]);
		printf("\nLinha 2 ----------\n");
		for (unsigned i = 0; i < this->linha[1].size(); i++)
			printf("%u ", this->linha[1][i]); 
		printf("\nLinha 3 ----------\n");
		for (unsigned i = 0; i < this->linha[2].size(); i++)
			printf("%u ", this->linha[2][i]);
		printf("\nLinha 4 ----------\n");
		for (unsigned i = 0; i < this->linha[3].size(); i++)
			printf("%u ", this->linha[3][i]);
		printf("\n");
	}
};
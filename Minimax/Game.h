#pragma once

#include <iostream>
#include <algorithm>
#include "Estado.h"

const char PLAYER = 'O';
const char AI = 'X';

using namespace std;

class Game
{
public:
	char map[3][3] = { 0 };

	Game()
	{
		for (unsigned i = 0; i < 3; i++)
			for (unsigned j = 0; j < 3; j++)
				map[i][j] = ' ';
	}

	bool makePlay(char p, unsigned posX, unsigned posY)
	{
		if (isEmpty(posX, posY)) { map[posX][posY] = p; return true; }
		else return false; 
	}

	bool isEmpty(unsigned posX, unsigned posY) { return map[posX][posY] == ' '; }

	void gameToString()
	{
		cout << " ";
		for (unsigned i = 0; i < 3; i++)
			cout << "  " << i;
		cout << endl;
		for (unsigned i = 0; i < 3; i++)
		{
			cout << i <<" | ";
			for (unsigned j = 0; j < 3; j++)
				cout << map[i][j] << " ";
			cout << "|\n";
		}
	}

	bool checkIfWin(char p)// checa se o jogador de char p ganhou
	{
		//linhas
		for (unsigned i = 0; i < 3; i++)
			if (map[i][0] == p && map[i][1] == p && map[i][2] == p)
				return true;
		
		//colunas
		for (unsigned i = 0; i < 3; i++)
			if (map[0][i] == p && map[1][i] == p && map[2][i] == p)
				return true;

		//diagonais
		if (map[0][0] == p && map[1][1] == p && map[2][2] == p)
			return true;
		else if (map[0][2] == p && map[1][1] == p && map[2][0] == p)
			return true;
		
		return false;
	}

	bool gameIsOver()
	{
		if (gameScore() == 10 || gameScore() == -10) return true;
		else if (!isMovesLeft()) return true;
		else return false;
	}

	bool isMovesLeft()
	{
		for (unsigned i = 0; i < 3; i++)
			for (unsigned j = 0; j < 3; j++)
				if (map[i][j] == ' ') return true;
		return false;
	}

	int gameScore()
	{
		if (checkIfWin(PLAYER)) return 10;//ia ganha
		else if (checkIfWin(AI)) return -10;//jogador ganha
		else return 0; // jogo não terminou
	}

	Estado miniMax(char mapMM[3][3])
	{
		int bestScore = INT_MAX;
		Estado bestState;

		for(unsigned i = 0; i < 3; i++)
			for(unsigned j = 0; j < 3; j++)
				if (mapMM[i][j] == ' ')
				{
					mapMM[i][j] = AI;
					int tempScore = maxV(mapMM);
					if (tempScore <= bestScore)// min, mas preciso criar o estado para retorno :(.
					{ bestScore = tempScore; bestState = Estado(i, j); }
					mapMM[i][j] = ' ';
				}
		return bestState;
	}

	int maxV(char mapMM[3][3])
	{
		if (gameIsOver()) return gameScore();
		Estado bestState;

		int bestScore = INT_MIN;

		for(unsigned i = 0 ; i < 3; i++)
			for (unsigned j = 0; j < 3; j++)
			{
				if (mapMM[i][j] == ' ')
				{
					mapMM[i][j] = PLAYER;
					int tempScore = minV(mapMM);
					bestScore = max(tempScore, bestScore);// recebe o maior valor entre temp e best.
					mapMM[i][j] = ' ';
				}
			}
		
		return bestScore;
	}

	int minV(char mapMM[3][3])
	{
		if (gameIsOver()) return gameScore();
		Estado bestState;
		
		int bestScore = INT_MAX;

		for (unsigned i = 0; i < 3; i++)
			for (unsigned j = 0; j < 3; j++)
			{
				if (mapMM[i][j] == ' ')
				{
					mapMM[i][j] = AI;
					int tempScore = maxV(mapMM);
					bestScore = min(tempScore, bestScore);// recebe o menor valor entre temp e best.
					mapMM[i][j] = ' ';
				}
			}
		
		return bestScore;
	}
	void play()
	{
		unsigned posX, posY;
		for (int turn = 0; !checkIfWin(PLAYER) && !checkIfWin(AI) && !gameIsOver(); )
		{
			cout << "Estado atual do jogo:\n";
			gameToString();
			cout << "______________________________________________________________________\n";
			if (turn % 2 == 0)
			{
				cout << "Seu turno, digite dois numeros separados por espaco no intervalo [0,2]\nrepresentando a coordenada de sua jogada.\n";
				cin >> posX >> posY;
				while ( (posX > 2 || posY > 2) || !makePlay(PLAYER, posX, posY) ) { cout << "Coordenadas Invalidas ou posicao ja esta ocupada, digite novamente!\n"; cin >> posX >> posY; }
				if (checkIfWin(PLAYER)) cout << "Você venceu!\n"; // nao deve acontecer!
				turn++;
			}
			else
			{
				cout << "Turno da AI! Aguarde sua jogada...\n";
				Estado AIp = miniMax(map);
				makePlay(AI, AIp.posX, AIp.posY);
				if (checkIfWin(AI)) cout << "AI ganhou!\n"; // deve acontecer!
				turn++;
			}
		}
		if (!checkIfWin(PLAYER) && !checkIfWin(AI))
		{
			cout << "EMPATE________________________________________________________________\n";
			gameToString();
			cout << "______________________________________________________________________\n";
		}
		else
		{
			cout << "Estado final do jogo:\n";
			cout << "______________________________________________________________________\n";
			gameToString();
			cout << "______________________________________________________________________\n";
		}
	}
};
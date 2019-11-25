#include "Game.h"
#include <iostream>


int main()
{
	cout << "Iniciando Tic Tac Toe, Jogador vs AI! (Minimax)\n";
	Game* game = new Game();
	game->play();

	return 0;
}

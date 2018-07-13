#include "Ghost.h"
#include "Game.h"
#include <time.h>

Ghost::Ghost(Game* game, Texture* texture, int spriteCol):
	GameCharacter(game, texture, spriteCol)
{
	srand(time(NULL));
}

Ghost::~Ghost()
{
}

void Ghost::update()
{
	/*
	while (!_game->nextCell(col, row, dir))
	{
		dir = static_cast<Direction>(rand() % 4);
	}
	*/
	move();
}

void Ghost::reset()
{
	/*IA-> debe volver a la casilla de inicio*/
	//x = iniX;
	//y = iniY;
	//col = iniCol;
	//row = iniRow;
	//dir = iniDir;
}

#include "Pacman.h"
#include "Game.h"
#include "GameCharacter.h"

Pacman::Pacman(Game* game, Texture* texture, int spriteCol):
	GameCharacter(game, texture, spriteCol), nextDir(NONE)
{
}

Pacman::~Pacman()
{
}

void Pacman::update()
{	
	//Movimiento
	if (nextDir != NONE && game->nextCell(col, row, nextDir))//Si hay una dirección en memoria y la la nueva posición es viable
	{
		direction = nextDir;
		nextDir = NONE;
		move();
	}
	else if (game->nextCell(col, row, direction))//Si no se tiene que cambiar de dirección y se puede mover en la dirección actual se hace
		move();
	
}

void Pacman::reset()
{
	col = iniCol;
	row = iniRow;
	direction = Direction::RIGHT;
}

bool Pacman::kill()
{
	std::cout << "PACMAN HIT! ";
	lifes--;
	std::cout << "Lifes: " << lifes<<std::endl;
	if (lifes <= 0)
		return true;
	else 
	{
		std::string msg = "Lifes left: " + std::to_string(lifes);
		SDL_ShowSimpleMessageBox(2, "Try again", msg.c_str(), game->getWindow());
		reset();
	}
	return false;
}

void Pacman::setDirection(Direction newDirection)
{
	nextDir = newDirection;
}

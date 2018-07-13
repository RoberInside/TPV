#include "GameCharacter.h"
#include "Game.h"
#include "Texture.h"
#include <fstream>

GameCharacter::GameCharacter(Game* game, Texture* texture, int renderCol) :
	GameObject(game), texture(texture), row(0), iniRow(0), col(0), iniCol(0), direction(Direction::NONE), frameConter(0),
	w(game->getTileWidth()), h(game->getTileHeight()), colFrame(renderCol)
{
}
GameCharacter::~GameCharacter()
{
}

void GameCharacter::render()
{
	frameConter = ((frameConter + 1) % 2);
	int auxCol = colFrame + frameConter;
	texture->renderFrame(game->getRenderer(), { col*w, row*h, w, h }, (int)direction, auxCol);
}

void GameCharacter::loadFromFile(std::ifstream& f)
{
	int d;
	f >> col >> row >> iniCol >> iniRow >> d;
	direction = (Direction)d;
}

void GameCharacter::saveToFile(std::ofstream& f)
{
	int d = direction;
	f << col <<" "<< row << " " << iniCol << " " << iniRow << " " << d<< std::endl;
}

void GameCharacter::move()
{
	switch(direction)
	{
	case UP:
		row--;
		break;
	case DOWN:
		row++;
		break;
	case RIGHT:
		col++;
		break;
	case LEFT:
		col--;
		break;
	case NONE:
		break;
	default:
		break;
	}
}

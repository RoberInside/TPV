#include "GameCharacter.h"
#include "Game.h"
#include "Texture.h"

GameCharacter::GameCharacter(Game* game, Texture* texture, int x, int y, int row, int col, Direction direction, int renderCol) :
	GameObject(game), texture(texture), x(x), iniX(x), y(y), iniY(y), row(row), iniRow(row), col(col), iniCol(col), direction(direction), frameConter(0),
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
	texture->renderFrame(game->getRenderer(), { x, y, w, h }, (int)direction, auxCol);
}

void GameCharacter::loadFromFile(const char * data)
{
}

void GameCharacter::saveToFile(const char * data)
{
}

void GameCharacter::move()
{
	switch(direction)
	{
	case UP:
		y -= h;
		row--;
		break;
	case DOWN:
		y += h;
		row++;
		break;
	case RIGHT:
		x += w;
		col++;
		break;
	case LEFT:
		x -= w;
		col--;
		break;
	case NONE:
		break;
	default:
		break;
	}
}

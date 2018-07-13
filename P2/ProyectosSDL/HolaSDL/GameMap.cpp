#include "GameMap.h"
#include "Game.h"
#include "GameObject.h"


GameMap::GameMap(Game * game):
	GameObject(game), food(0)
{
	wallTexture = game->loadMapResources(Wall);
	foodTexture = game->loadMapResources(Food);
	vitaminTexture = game->loadMapResources(Vitamin);
}

GameMap::~GameMap()
{
	if (map) {
		for (int i = 0; i < rows; i++)
			delete[] map[i];
		delete[] map;
	}
}

MapCell GameMap::getCell(int row, int col)
{
	if (row < 0)		return map[rows - 1][col];
	if (row >= rows)	return map[0][col];
	if (col < 0)		return map[row][cols - 1];
	if (col >= cols)	return map[row][0];
	/*else*/			return map[row][col];
}

void GameMap::setCell(MapCell type, int row, int col)
{
	map[row][col] = type;
}

void GameMap::render()
{
	SDL_Rect r{ 0,0, game->getTileWidth(), game->getTileHeight()};
	SDL_Renderer* tmp = game->getRenderer();
	for (size_t i = 0; i < cols; i++)
	{
		for (size_t j = 0; j < rows; j++)
		{
			r.x = i * game->getTileWidth();
			r.y = j * game->getTileWidth();
			switch (map[j][i])
			{
			case Wall:
				wallTexture->render(tmp, r);
				break;
			case Food:
				foodTexture->render(tmp, r);
				break;
			case Vitamin:
				vitaminTexture->render(tmp, r);
				break;
			default:
				break;
			}
		}
	}
}

void GameMap::update()
{
	//No estoy muy seguro de qué tiene que hacer esto pero bueno
}

bool GameMap::loadFromFile(std::ifstream & f)
{
	f >> rows >> cols;
	initBoard();
	char buffer;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
		{
			f >> buffer;
			map[i][j] = (MapCell)buffer;
			if (buffer == Food) food++;
		}
	}
	return true;
}

bool GameMap::saveToFile(std::ofstream & f)
{
	f << rows <<" "<< cols<<std::endl;
	char buffer;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols-1; j++) {
			f << map[i][j] << " ";
		}
		f << map[i][cols - 1] << std::endl;
	}
	return true;
}

void GameMap::printCell(int row, int col)
{
	const char* type ="";

	if (row < 0) row = rows - 1;
	if (row >= rows) row = 0;
	if (col < 0) col = cols - 1;
	if (col >= cols) col = 0;

	switch (map[row][col])
	{
	case Empty:
		type = "Empty";
		break;
	case Wall:
		type = "Wall";
		break;
	case Food:
		type = "Food";
		break;
	case Vitamin:
		type = "Vitamin";
		break;
	default:
		break;
	}
	std::cout << "Cell " << row<<", " << col<<" is the type: "<< type<<"\n";
}

void GameMap::initBoard()
{
	map = new MapCell*[rows];
	for (int i = 0; i < rows; i++)
		map[i] = new MapCell[cols];
}

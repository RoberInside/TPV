#include "GameMap.h"
#include "Game.h"


GameMap::GameMap(Game * game, int rows, int cols):
	rows(rows), cols(cols), game(game), food(0)
{
	map = new MapCell*[rows];
	for (int i = 0; i < rows; i++)
		map[i] = new MapCell[cols];

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

void GameMap::render(SDL_Renderer * renderer)
{
	SDL_Rect r{ 0,0, game->tileWidth, game->tileHeight };
	for (size_t i = 0; i < cols; i++)
	{
		for (size_t j = 0; j < rows; j++)
		{
			r.x = i * game->tileWidth;
			r.y = j * game->tileHeight;
			switch (map[j][i])
			{
			case Wall:
				wallTexture->render(renderer, r);
				break;
			case Food:
				foodTexture->render(renderer, r);
				break;
			case Vitamin:
				vitaminTexture->render(renderer, r);
				break;
			default:
				break;
			}
		}
	}
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

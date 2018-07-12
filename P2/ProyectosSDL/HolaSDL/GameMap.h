#pragma once
#include "Texture.h"
#include <fstream>

enum MapCell {Empty, Wall, Food, Vitamin};

class GameMap
{
	friend class Game;
public:
	GameMap(Game* game, int rows, int cols);
	~GameMap();

	MapCell getCell(int row, int col);
	void setCell(MapCell type, int row, int col);
	void render(SDL_Renderer* renderer);
	int getRows() { return rows; };
	int getCols() { return cols; };

	void printCell(int row, int col);

private:
	Game* game;

	Texture* foodTexture;
	Texture* wallTexture;
	Texture* vitaminTexture;

	MapCell** map;
	int food;
	int rows;
	int cols;
};


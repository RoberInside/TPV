#pragma once
#include "Texture.h"
#include "GameObject.h"
#include <fstream>

enum MapCell {Empty, Wall, Food, Vitamin};

class GameMap:
	public GameObject
{
	friend class Game;
public:
	GameMap(Game* game);
	~GameMap();

	MapCell getCell(int row, int col);
	void setCell(MapCell type, int row, int col);
	void render();
	void update();
	int getRows() { return rows; };
	int getCols() { return cols; };

	bool loadFromFile(std::ifstream& f);
	bool saveToFile(std::ofstream& f);


	void printCell(int row, int col);

private:

	void initBoard();

	Game* game;

	Texture* foodTexture;
	Texture* wallTexture;
	Texture* vitaminTexture;

	MapCell** map;
	int food;
	int rows;
	int cols;
};


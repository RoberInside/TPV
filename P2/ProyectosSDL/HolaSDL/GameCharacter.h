#pragma once
#include "GameObject.h"
//#include "Texture.h"
enum Direction {RIGHT, DOWN, LEFT, UP, NONE};
class Texture;
class GameCharacter :
	public GameObject
{
	GameCharacter(Game* game, Texture* texture, int x, int y, int row, int col, Direction direction, int frameCol);
	virtual ~GameCharacter();

	void render();
	void loadFromFile(const char* data);
	void saveToFile(const char* data);

protected:

	void move();

	int x, y, iniX, iniY;
	int row, col, iniRow, iniCol;
	Direction direction;
	Texture* texture;

private:
	char frameConter;
	char colFrame;
	int w, h;
};

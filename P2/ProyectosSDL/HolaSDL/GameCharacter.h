#pragma once

#include <fstream>

#include "GameObject.h"

enum Direction {RIGHT, DOWN, LEFT, UP, NONE};

class Texture;
class GameCharacter :
	public GameObject
{
public:
	GameCharacter(Game* game, Texture* texture, int spriteCol);
	virtual ~GameCharacter();

	void render();
	void loadFromFile(std::ifstream& f);
	void saveToFile(std::ofstream& f);

	//Getters and setters
	int getW() { return w; };
	void setW(int w_) { w = w_; };

	int getH() { return h; };
	void setH(int h_) { h = h_; };

	Direction getDirection() { return direction; };
	virtual void setDirection(Direction newDirection) { direction = newDirection; };

	int getRow() { return row; };
	void setRow(int row_) { row = row_; };

	int getCol() { return col; };
	void setCol(int col_) { col = col_; };

protected:

	void move();

	int row, col, iniRow, iniCol;
	Direction direction;
	Texture* texture;

private:
	int w, h;
	char frameConter;
	char colFrame;
};

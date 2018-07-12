#pragma once

#include "Texture.h"

class Game;
enum Direction;

class Ghost
{
public:
	Ghost(Texture * texture, Game * game, int px, int py, Direction dir, int row, int col);
	~Ghost();

	void render(SDL_Renderer* renderer, int row, int col);
	void update();
	void reset();
	int getX() { return x; }
	int getY(){return y;}
	void setX(int x_) { x = x_; };
	void setY(int y_) { y = y_; };
	int getRow(){return row; }
	int getCol() {return col;};
	void setRow(int row_) { row = row_; };
	void setCol(int col_) { col = col_; };
private:
	void move(Direction dir);

	Texture* _texture;
	int x, y;
	int iniX, iniY;
	Direction dir;
	Direction iniDir;
	Game* _game;
	int h, w; 
	int row, col;
	int iniRow, iniCol;
};


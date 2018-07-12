#pragma once
#include "Texture.h"

class Game;
enum Direction { UP, DOWN, RIGHT, LEFT, NONE };

class Pacman
{
public:
	Pacman(Texture* texture, Game* game, int px, int py, int row, int col);
	~Pacman();

	void render(SDL_Renderer* renderer);
	void update();
	void reset();
	bool kill();

	//Getters and setters
	int getW() { return w; };
	void setW(int w_) { w = w_; };

	int getH() { return h; };
	void setH(int h_) { h = h_; };
	
	int getX() { return x; };
	void setX(int x_) { x = x_; };
	
	int getY() { return y; };
	void setY(int y_) { y = y_; };

	Direction getDirection() { return dir; };
	void setDirection(Direction newDirection);

	int getRow() { return row; };
	void setRow(int row_) { row = row_; };

	int getCol() { return col; };
	void setCol(int col_) { col = col_; };

	int getLifes() { return lifes; }


private:

	void move(Direction newDir);

	Texture * texture;
	Game* game;
	int iniX, iniY;
	int x, y;
	int row, col;
	Direction dir;
	Direction nextDir;
	int w, h;
	int iniRow, iniCol;
	
	Uint32 timeSuperWasActivated;

	int lifes;
};


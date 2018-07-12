#include "Ghost.h"
#include "Game.h"
#include <time.h>

Ghost::Ghost(Texture * texture, Game * game, int px, int py, Direction dir, int row, int col):
	_texture(texture), _game(game), 
	x(px), y(py), dir(dir), 
	row(row), col(col), h(game->tileHeight), w(game->tileWidth)
{
	srand(time(NULL));
}

Ghost::~Ghost()
{
}

void Ghost::render(SDL_Renderer * renderer, int row, int col)
{
	SDL_Rect r{ x, y, w, h };
	_texture->renderFrame(renderer, r, row, col);
}

void Ghost::update()
{
	while (!_game->nextCell(col, row, dir))
	{
		dir = static_cast<Direction>(rand() % 4);
	}
	move(dir);
}

void Ghost::reset()
{
	x = iniX;
	y = iniY;
	col = iniCol;
	row = iniRow;
	dir = iniDir;
}

void Ghost::move(Direction dir)
{
	switch (dir)
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
	default:
		break;
	}
}
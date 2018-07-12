#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Texture * texture, Game * game, int px, int py, int row, int col):
	texture(texture), game(game), lifes(3),
	x(px), y(py), iniX(px), iniY(py),
	row(row), col(col), iniCol(col), iniRow(row), 
	w(game->tileWidth), h(game->tileHeight), dir(Direction::NONE), nextDir(NONE)
{
}

Pacman::~Pacman()
{
}

void Pacman::render(SDL_Renderer * renderer)
{
	texture->render(renderer, { x, y, w, h });
	//texture->renderFrame(renderer, { x, y, w, h }, 0, 0);
}

void Pacman::update()
{	
	//Movimiento
	if (nextDir != NONE && game->nextCell(col, row, nextDir))//Si hay una dirección en memoria y la la nueva posición es viable
	{
		dir = nextDir;
		nextDir = NONE;
		move(dir);
	}
	else if (game->nextCell(col, row, dir))//Si no se tiene que cambiar de dirección y se puede mover en la dirección actual se hace
		move(dir);
	
}

void Pacman::reset()
{
	x = iniX;
	y = iniY;
	col = iniCol;
	row = iniRow;
	dir = Direction::RIGHT;
}

bool Pacman::kill()
{
	std::cout << "PACMAN HIT! ";
	lifes--;
	std::cout << "Lifes: " << lifes<<std::endl;
	if (lifes <= 0)
		return true;
	else 
	{
		std::string msg = "Lifes left: " + std::to_string(lifes);
		SDL_ShowSimpleMessageBox(2, "Try again", msg.c_str(), game->getWindow());
		reset();
	}
	return false;
}

void Pacman::setDirection(Direction newDirection)
{
	nextDir = newDirection;
}

void Pacman::move(Direction newDir)
{
	const char* dirString = "";//DEBUG
	switch (newDir)
	{
	case UP:
		y -= h;
		row--;
		dirString = "UP";
		break;
	case DOWN:
		y += h;
		row++;
		dirString = "DOWN";
		break;
	case RIGHT:
		x += w;
		col++;
		dirString = "RIGHT";
		break;
	case LEFT:
		x -= w;
		col--;
		dirString = "LEFT";
		break;
	case NONE:
		break;
	default:
		break;
	}
	//Debug!
	std::cout << "\n**************************************************************************************\n";
	std::cout << "Pacman Direction:\n    "<<dirString<<"\nPacman position:\n    col: " << col << " row:" << row << "\n";
	game->getGameMap()->printCell(row, col);
}

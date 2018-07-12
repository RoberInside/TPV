#pragma once
//Sytem Libraries
#include <iostream>
#include <string>
#include <vector>
//User Libraries
#include <SDL.h>
#include "Ghost.h"
#include "Pacman.h"
#include "GameMap.h"

const int NGHOSTS = 4;
const int TIME_SUPER = 5000;//ms

class Game
{
public:
	Game();
	~Game();
	void run();
	bool nextCell(int col, int row, Direction dir);
	GameMap* getGameMap() { return map; };//Provisional
	SDL_Window* getWindow() { return window; };
	SDL_Renderer* getRenderer() { return renderer; };
	Texture* loadMapResources(MapCell cellType);
	int tileWidth;
	int tileHeight;
private:

	bool initSDL();
	void closeSDL();

	void update();
	void render();
	void handleEvents();

	bool initPacman(int x, int y);

	bool initGhost(int i, int x, int y);
	void initMap(std::string levelPath);
	bool collision(Ghost* ghost);
	void rollBorders();

	void setSuperPacman();

	SDL_Window * window;
	SDL_Renderer* renderer;

	bool error, exit, gameover, win, pause;

	Ghost* ghosts[NGHOSTS];
	Pacman* pacman;
	Texture* textures[5];
	GameMap* map;
	const int WIDTH = 800;
	const int HEIGHT = 600;
	int xWin, yWin;


	int score;
	Uint32 superPacmanTimer;
	bool superPacman;
};


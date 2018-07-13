#pragma once
//Sytem Libraries
#include <iostream>
#include <string>
#include <vector>
#include <list>
//User Libraries
#include <SDL.h>
#include "GameObject.h"
#include "Ghost.h"
#include "Pacman.h"
#include "GameMap.h"

const int TIME_SUPER = 5000;//ms

enum TextureEnum{Characters, Wall, Food, Vitamin};
const char* texturePaths[] = { "..\\images\\characters.png", "..\\images\\wall.png", "..\\images\\food.png", "..\\images\\vitamin.png" };

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
	int getTileWidth() { return tileWidth; };
	int getTileHeight() { return tileHeight; };
private:

	bool initSDL();
	void closeSDL();

	void update();
	void render();
	void handleEvents();

	bool initPacman(int x, int y);

	bool initGhost(int i, int x, int y);
	void initTextures();
	bool collision(Ghost* ghost);
	void rollBorders();

	void setSuperPacman();

	bool save(const std::string& path);
	bool load(const std::string& path);

	SDL_Window * window;
	SDL_Renderer* renderer;

	bool error, exit, gameover, win, pause;

	std::list<GameObject*> objects;
	Pacman*pacman;

	Texture* textures[4];

	int tileWidth;
	int tileHeight;
	const int WIDTH = 800;
	const int HEIGHT = 600;

	int level;
	int score;
	Uint32 superPacmanTimer;
	bool superPacman;
};


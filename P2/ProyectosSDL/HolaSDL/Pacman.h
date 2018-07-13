#pragma once
#include "Texture.h"
#include "GameCharacter.h"
class Game;

class Pacman:
	public GameCharacter
{
public:
	Pacman(Game* game, Texture* texture, int spriteCol);
	~Pacman();

	void update();
	void reset();
	bool kill();
	void setDirection(Direction newDirection);
	int getLifes() { return lifes; }


private:
	Direction nextDir;

	Uint32 timeSuperWasActivated;

	int lifes;
};


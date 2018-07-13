#pragma once
#include "Texture.h"
#include "GameCharacter.h"

class Game;
enum Direction;

class Ghost:
	public GameCharacter
{
public:
	Ghost(Game* game, Texture* texture, int spriteCol);
	~Ghost();

	void update();
	void reset();

private:

	Texture* _texture;

};


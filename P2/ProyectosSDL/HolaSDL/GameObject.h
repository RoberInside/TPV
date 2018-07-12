#pragma once

class Game;
class GameObject
{
public:
	GameObject(Game* game): game(game) {};
	virtual ~GameObject() {};
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void loadFromFile(const char* file) = 0;
	virtual void saveToFile  (const char* file) = 0;
protected:
	Game * game;
};

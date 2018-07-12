#pragma once

class Game;
class GameObject
{
public:
	GameObject(Game* game): game(game) {};
	virtual ~GameObject() {};
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void loadFromFile(std::ifstream& f) = 0;
	virtual void saveToFile  (std::ofstream& f) = 0;
protected:
	Game * game;
};

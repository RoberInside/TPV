#pragma once
#include <string>

class Game;
class DataManager
{
public:
	DataManager& get()
	{
		static DataManager instance;
		return instance;

	}
	~DataManager();
	void init(Game* game) { this->game = game; };
	void save(const std::string& path);
	void load(const std::string& path);
private:
	DataManager();
	Game* game = nullptr;
};


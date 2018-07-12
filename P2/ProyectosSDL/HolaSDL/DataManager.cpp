#include "DataManager.h"
#include <fstream>


DataManager::~DataManager()
{
}

void DataManager::save(const std::string& path)
{
	std::ofstream o;
	o.open(path);
	if (o.fail()) {/*Rutina de fallo*/}
	else
	{
		o << game->getLevel() << " " << game->getScore() << std::endl;
		//Esto está bien pero necesitamos asegura que el orden de los objetos es siempre el mismo
		//Podemos hacer comprobaciones, pero es más costoso en tiempo de ejecución
		auto& objects = game->getGameObjects();
		for (auto o : objects)
			o->saveToFile(o);
	}
}

void DataManager::load(const std::string& path)
{
	
}
std::string getExtension(const std::string& s)
{
	std::string result = "";
	for (int i = s.size() - 1; s[i] != '.' && i >= 0; i--)
		result.push_back(s[i]);
	return result;
}
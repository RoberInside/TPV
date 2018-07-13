#include "Game.h"
#include <fstream>


Game::Game() :
	window(nullptr), renderer(nullptr),
	exit(false), gameover(false),pause(false), win(false), score(0)
{
	textures[0] = textures[1] = nullptr;
	initSDL();
	initMap("..\\images\\level02.dat");
}


Game::~Game()
{
}

bool Game::initSDL()
{
	bool flag = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "¡SDL no se ha podido iniciar! \nSDL_Error: " << SDL_GetError() << '\n';
		flag = false;
	}
	else {
		xWin = yWin = SDL_WINDOWPOS_CENTERED;
		window = SDL_CreateWindow("SDL PACMAN", xWin, yWin, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			std::cout << "¡La ventana no se ha podido crear! \nSDL_Error: " << SDL_GetError() << '\n';
			flag = false;
		}
		else {
			//Toma la superficie de la ventana:
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == nullptr) {
				std::cout << "¡No se ha podido crear el renderer! \nSDL_Error: " << SDL_GetError() << '\n';
				flag = false;
			}
		}
	}
	return flag;
}

void Game::closeSDL()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

void Game::run() 
{
	if (!error)
	{
		Uint32 MSxUpdate = 1000;
		std::cout << "Play\n";
		Uint32 lastUpdate = SDL_GetTicks();

		handleEvents();
		while (!exit && !gameover)
		{
			if(SDL_GetTicks() - lastUpdate >= MSxUpdate && !pause)
			{
				update();
				render();
				lastUpdate = SDL_GetTicks();
			}
			if (map->food <= 0) {
				std::string msg = "Score: " + std::to_string(score) + "\n Lifes left: " + std::to_string(pacman->getLifes());
				SDL_ShowSimpleMessageBox(2, "VICTORY", msg.c_str(), window);
				exit = true;
			}
			handleEvents();
		}
		if (gameover)
		{
			std::string msg = "Score: " + std::to_string(score);
			SDL_ShowSimpleMessageBox(2, "YOU LOSE", msg.c_str(), window);
		}
		render();
		if (exit) std::cout << "EXIT\n";
		SDL_Delay(1000);
	}
}

bool Game::nextCell(int col, int row, Direction dir)
{
	switch (dir)
	{
	case UP:
		row--;
		break;
	case DOWN:
		row++;
		break;
	case RIGHT:
		col++;
		break;
	case LEFT:
		col--;
		break;
	case NONE:
		break;
	default:
		break;
	}
	return map->getCell(row, col) != Wall;
}
const char* ghostColor[] = { "Red", "PINK", "Green", "Yellow" };
void Game::update()
{
	if (SDL_GetTicks() >= superPacmanTimer + TIME_SUPER) superPacman = false;

	pacman->update();
	rollBorders();

	if (map->getCell(pacman->getRow(), pacman->getCol()) == Vitamin) {
		score += 200;
		map->setCell(Empty, pacman->getRow(), pacman->getCol());
		setSuperPacman();
	}
	if (map->getCell(pacman->getRow(), pacman->getCol()) == Food) {
		score += 100;
		map->setCell(Empty, pacman->getRow(), pacman->getCol());
	}
	std::cout << "------------------------------------------------------\n";
	for (int i = 0; i < NGHOSTS; i++) { 
			ghosts[i]->update();
			std::cout << "Ghost " << ghostColor[i] << " position:\n    row: " << ghosts[i]->getRow() << " col: " << ghosts[i]->getCol()<<"\n";
			if (collision(ghosts[i])) std::cout<<"+++++++++++++++++++++++++++++++++++ Collision with Ghost "<< ghostColor[i] <<"+++++++++++++++++++++++++++++++++++\n";
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto o : objects)
		o->render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) && !exit) {
		switch (e.type)
		{
		case SDL_QUIT:
			exit = true;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				std::cout << "EXIT\n";
				exit = true;
				break;
			case SDLK_SPACE:
				std::cout << "PAUSE\n";
				pause = !pause;
			case SDLK_UP: case SDLK_w:
				pacman->setDirection(UP);
				std::cout << "Pressed: UP\n";
				break;
			case SDLK_DOWN: case SDLK_s:
				pacman->setDirection(DOWN);
				std::cout << "Pressed: DOWN\n";
				break;
			case SDLK_RIGHT: case SDLK_d:
				pacman->setDirection(RIGHT);
				std::cout << "Pressed: RIGHT\n";
				break;
			case SDLK_LEFT: case SDLK_a:
				pacman->setDirection(LEFT);
				std::cout << "Pressed: LEFT\n";
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

Texture* Game::loadMapResources(MapCell celltype)
{
	switch (celltype)
	{
	case Wall:
		textures[2] = new Texture();
		textures[2]->loadTexture(renderer, "..\\images\\wall.png", 1, 1);
		return textures[2];
	case Food:
		textures[3] = new Texture();
		textures[3]->loadTexture(renderer, "..\\images\\food.png", 1, 1);
		return textures[3];
	case Vitamin:
		textures[4] = new Texture();
		textures[4]->loadTexture(renderer, "..\\images\\burguer.png", 1, 1);
		return textures[4];
	default:
		return nullptr;
	}
}

bool Game::initPacman(int x, int y)
{
	textures[0] = new Texture(); 
	textures[0]->loadTexture(renderer, "..\\images\\pacman.png", 1, 1);
	pacman = new Pacman(textures[0], this, x * tileWidth, y*tileHeight, y, x);
	return (bool)textures[0];
}

bool Game::initGhost(int i, int x, int y)
{
	textures[1] = new Texture();
	textures[1]->loadTexture(renderer, "..\\images\\ghostSheet.png", 1, 5);
	ghosts[i] = new Ghost(textures[1], this, x*tileWidth, y*tileHeight, (Direction)0, y, x);
	return (bool)textures[1];
}

void Game::initTextures()
{
}



bool Game::collision(Ghost* ghost)
{
	bool collision = false;
	if(pacman->getRow() == ghost->getRow() && pacman->getCol() && ghost->getRow())
	{
		if (superPacman)
		{
			score += 500;
			ghost->reset();
		}
		else {
			gameover = pacman->kill();
		}

		collision = true;
	}

	return collision;
}

void Game::rollBorders()
{
	if (pacman->getX() <= 0) {
		pacman->setCol(map->getCols() - 1);
		pacman->setX((map->getCols() - 1) * tileWidth);
	}
	else if (pacman->getX() >= ((map->getCols()) * tileWidth)) {
		pacman->setX(0);
		pacman->setCol(0);
	}


	if (pacman->getY() <= 0) {
		pacman->setRow(map->getRows() - 1);
		pacman->setY((map->getRows() - 1) * tileHeight);
	}
	else if (pacman->getY() >= ((map->getRows()) * tileHeight)) {
		pacman->setRow(0);
		pacman->setY(0);
	}
	for (int i = 0; i < NGHOSTS; i++)
	{
		if (ghosts[i]->getX() <= 0) {
			ghosts[i]->setCol(map->getCols() - 1);
			ghosts[i]->setX((map->getCols() - 1) * tileWidth);
		}
		else if (ghosts[i]->getX() >= ((map->getCols()) * tileWidth)) {
			ghosts[i]->setX(0);
			ghosts[i]->setCol(0);
		}


		if (ghosts[i]->getY() <= 0) {
			ghosts[i]->setRow(map->getRows() - 1);
			ghosts[i]->setY((map->getRows() - 1) * tileHeight);
		}
		else if (ghosts[i]->getY() >= ((map->getRows()) * tileHeight)) {
			ghosts[i]->setRow(0);
			ghosts[i]->setY(0);
		}
	}
}

void Game::setSuperPacman()
{
	std::cout << "SUPER!!!!!!!\n";
	superPacmanTimer = SDL_GetTicks();
	superPacman = true;
}

bool Game::save(const std::string & path)
{
	std::ofstream o(path);
	if (o.fail()) return false;
	//Save game state
	o << level << " " << score<<std::endl;
	//Save map
	for (auto i = objects.begin(); i != objects.end(); i++)
		(*i)->saveToFile(o);
	return true;
}

bool Game::load(const std::string & path)
{
	std::ifstream f(path);
	if (f.fail) return false;
	if (strcmp(path.c_str() + (path.size() - 3), "sav"))
		f >> level >> score;
	objects.push_back(new GameMap(this));
	objects.push_back(new Pacman(this));
	int nghost = 0;
	bool intelligent = false;
	f >> nghost;
	auto it = objects.begin();
	it++; it++;
	for (size_t i = 0; i < nghost; i++, it++)
	{
		f >> intelligent;
		objects.push_back((intelligent) ? new IntelligentGhost(this) : new Ghost(this));
		(*it)->loadFromFile(f);
	}

	return true;
}


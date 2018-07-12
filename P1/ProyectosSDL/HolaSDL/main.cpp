#include "Game.h"
#include "checkML.h"

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game = Game();
	game.run();
	return 0;
}
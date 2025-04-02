#include "lsGame.h"

int main()
{
	lsConfiguration::initialize();

	lsGame game;
	game.run();
	return 0;
}

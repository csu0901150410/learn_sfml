#include "lsGame.h"

int main()
{
    lsPlayer::set_default_inputs();

	lsGame game;
    game.run(60);
    return 0;
}

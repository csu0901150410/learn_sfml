#include "lsGame.h"

#include "lsConfiguration.h"

int main()
{
    // ��ʼ��������Դ
    lsConfiguration::initialize();

	lsGame game;
    game.run(60);
    return 0;
}

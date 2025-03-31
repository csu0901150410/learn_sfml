#include "lsGame.h"

#include "lsConfiguration.h"

int main()
{
    // 初始化加载资源
    lsConfiguration::initialize();

	lsGame game;
    game.run(60);
    return 0;
}

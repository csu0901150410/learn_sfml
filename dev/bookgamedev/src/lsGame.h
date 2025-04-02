#pragma once

#include <SFML/Graphics.hpp>

#include "lsConfiguration.h"

class lsGame
{
public:
	lsGame();
	void run();

private:
	void process_events();
	void update();
	void render();

private:
	sf::RenderWindow m_window;
	sf::Sprite m_player;
	sf::Text m_text;
};

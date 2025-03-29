#pragma once

#include <SFML//Graphics.hpp>

#include "lsPlayer.h"

class lsGame
{
public:
	// 禁止拷贝构造
	lsGame(const lsGame&) = delete;
	// 禁止赋值运算符
	lsGame& operator=(const lsGame&) = delete;
	lsGame();

public:
	static std::string get_resources_path();

public:
	void run(int frame_per_seconds);

private:
	void process_events();
	void update(sf::Time deltaTime);
    void render();

private:
	sf::RenderWindow m_window;
	//sf::CircleShape m_player;
	lsPlayer m_player;

	sf::Font m_font;
	sf::Text m_text;
	float m_fps;
};

#pragma once

#include <SFML//Graphics.hpp>

class lsGame
{
public:
	// ½ûÖ¹¿½±´¹¹Ôì
	lsGame(const lsGame&) = delete;
	// ½ûÖ¹¸³ÖµÔËËã·û
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
	sf::CircleShape m_player;

	sf::Font m_font;
	sf::Text m_text;
	float m_fps;
};

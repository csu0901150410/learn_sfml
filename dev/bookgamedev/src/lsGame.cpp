#include "lsGame.h"

lsGame::lsGame()
	: m_window(sf::VideoMode(640, 480), "demo")
	, m_player()
	, m_text()
{
	m_player.setTexture(lsConfiguration::m_textures.get(lsConfiguration::kPlayer));
	m_player.setPosition(100, 100);

	m_text.setFont(lsConfiguration::m_fonts.get(lsConfiguration::kFiraCodeRegular));
	m_text.setString("FiraCode Font");
	m_text.setPosition(10, 10);
}

void lsGame::run()
{
	while (m_window.isOpen())
	{
		process_events();
		update();
		render();
	}
}

void lsGame::process_events()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::EventType::Closed == event.type)
			m_window.close();
	}
}

void lsGame::update()
{

}

void lsGame::render()
{
	m_window.clear();
	m_window.draw(m_player);
	m_window.draw(m_text);
	m_window.display();
}

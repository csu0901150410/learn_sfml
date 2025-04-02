#include "lsGame.h"

lsGame::lsGame()
	: m_window(sf::VideoMode(640, 480), "demo")
	, m_player()
	, m_text()
	, m_renderer(m_window)
{
	m_player.setTexture(lsConfiguration::m_textures.get(lsConfiguration::kPlayer));
	m_player.setPosition(100, 100);

	m_text.setFont(lsConfiguration::m_fonts.get(lsConfiguration::kFiraCodeRegular));
	m_text.setString("FiraCode Font");
	m_text.setPosition(10, 10);

	m_document.add_shape(std::make_unique<lsLine>(lsVector2f(50.f, 50.f), lsVector2f(100.f, 100.f), COLOR_RED));
	m_document.add_shape(std::make_unique<lsLine>(lsVector2f(50.f, 50.f), lsVector2f(100.f, 200.f), COLOR_BLUE));// 这颜色转的有点问题
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
	/*m_window.clear();
	m_window.draw(m_player);
	m_window.draw(m_text);
	m_window.display();*/

	lsRenderContext ctx;
	ctx.window_ptr = &m_window;
	m_document.render(m_renderer, ctx);
}

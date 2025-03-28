#include "lsGame.h"

#include <iostream>

lsGame::lsGame()
	: m_window(sf::VideoMode(800, 600), "sfml demo")
	, m_player(150)
	, m_font()
	, m_text()
	, m_fps(0)
{
	m_player.setFillColor(sf::Color::Red);
	m_player.setPosition(10, 20);

	if (!m_font.loadFromFile(get_resources_path() + "font/FiraCode-Regular.ttf"))
	{
		std::cout << "load font failed" << std::endl;
	}

	m_text.setFont(m_font);
    m_text.setCharacterSize(24);
	m_text.setPosition(10, 10);
}

// 可以在项目属性/调试/工作目录中设置根目录
std::string lsGame::get_resources_path()
{
	std::string path = "resources/";
	return path;
}

// 固定时间步长
void lsGame::run(int frame_per_seconds)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// 每帧的时间间隔，假设60帧/秒，每帧的时间间隔 = 1/60s
    sf::Time timePerFrame = sf::seconds(1.f / frame_per_seconds);

	int frameCount = 0;
	sf::Time fpsTimeout = sf::Time::Zero;

	while (m_window.isOpen())
	{
		process_events();
		bool repaint = false;

		// 叠加上一次循环的耗时，看看在此间隔内需要更新多少帧
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;
		fpsTimeout += deltaTime;
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			repaint = true;
			update(timePerFrame);

			// 计算fps
			frameCount++;
			m_fps = frameCount / fpsTimeout.asSeconds();
		}
		
		// 清一下，不然溢出了
		if (fpsTimeout > sf::seconds(1))
        {
			fpsTimeout -= sf::seconds(1);
            frameCount = 0;
        }

		// 更新了才需要重绘，限制重绘的频率
		if (repaint)
			render();
	}
}

void lsGame::process_events()
{
	sf::Event event;
    while (m_window.pollEvent(event))
    {
		switch (event.type)
		{
		case sf::Event::Closed:
		{
            m_window.close();
		}
		break;
		}
    }
}

void lsGame::update(sf::Time deltaTime)
{

}

void lsGame::render()
{
	sf::String strfpc = "FPS : " + std::to_string(static_cast<int>(m_fps));
	m_text.setString(strfpc);

	m_window.clear();
    m_window.draw(m_player);
	m_window.draw(m_text);
    m_window.display();
}

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

// ��������Ŀ����/����/����Ŀ¼�����ø�Ŀ¼
std::string lsGame::get_resources_path()
{
	std::string path = "resources/";
	return path;
}

// �̶�ʱ�䲽��
void lsGame::run(int frame_per_seconds)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// ÿ֡��ʱ����������60֡/�룬ÿ֡��ʱ���� = 1/60s
    sf::Time timePerFrame = sf::seconds(1.f / frame_per_seconds);

	int frameCount = 0;
	sf::Time fpsTimeout = sf::Time::Zero;

	while (m_window.isOpen())
	{
		process_events();
		bool repaint = false;

		// ������һ��ѭ���ĺ�ʱ�������ڴ˼������Ҫ���¶���֡
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;
		fpsTimeout += deltaTime;
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			repaint = true;
			update(timePerFrame);

			// ����fps
			frameCount++;
			m_fps = frameCount / fpsTimeout.asSeconds();
		}
		
		// ��һ�£���Ȼ�����
		if (fpsTimeout > sf::seconds(1))
        {
			fpsTimeout -= sf::seconds(1);
            frameCount = 0;
        }

		// �����˲���Ҫ�ػ棬�����ػ��Ƶ��
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

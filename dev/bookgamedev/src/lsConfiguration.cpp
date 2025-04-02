#include "lsConfiguration.h"

lsResourceManager<sf::Texture, int> lsConfiguration::m_textures;
lsResourceManager<sf::Font, int> lsConfiguration::m_fonts;

void lsConfiguration::initialize()
{
	init_textures();
	init_fonts();
}

void lsConfiguration::init_textures()
{
	m_textures.load(Textures::kPlayer, "resources/image/supermarie.png");
}

void lsConfiguration::init_fonts()
{
	m_fonts.load(Fonts::kFiraCodeRegular, "resources/font/FiraCode-Regular.ttf");
}

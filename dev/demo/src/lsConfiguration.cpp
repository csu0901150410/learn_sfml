#include "lsConfiguration.h"

lsResourceManager<sf::Texture, int> lsConfiguration::m_textures;
lsActionMap<int> lsConfiguration::m_playerInputs;

void lsConfiguration::initialize()
{
	init_textures();
	init_player_inputs();
}

void lsConfiguration::init_textures()
{
	m_textures.load(Textures::kPlayer, "resources/image/supermarie.png");
}

void lsConfiguration::init_player_inputs()
{
	// 用id标记动作，后续使用可以直接通过id去绑定动作和回调
	m_playerInputs.map(PlayerInputs::kUp, lsAction(sf::Keyboard::Up));
	m_playerInputs.map(PlayerInputs::kLeft, lsAction(sf::Keyboard::Left));
	m_playerInputs.map(PlayerInputs::kRight, lsAction(sf::Keyboard::Right));
}


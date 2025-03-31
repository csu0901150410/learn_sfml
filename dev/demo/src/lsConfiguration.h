#pragma once

#include <SFML/Graphics.hpp>

#include "lsResourceManager.hpp"
#include "lsActionMap.hpp"

class lsConfiguration
{
public:
	lsConfiguration() = delete;
	lsConfiguration(const lsConfiguration&) = delete;
	lsConfiguration& operator=(const lsConfiguration&) = delete;

	enum Textures : int
	{
		kPlayer,
	};
	// ȫ�ֵ���Դ
	static lsResourceManager<sf::Texture, int> m_textures;

	enum PlayerInputs : int
	{
		kUp,
		kLeft,
		kRight,
	};
	// ȫ�ֵĶ���
	static lsActionMap<int> m_playerInputs;

	static void initialize();

private:
	static void init_textures();
	static void init_player_inputs();
};

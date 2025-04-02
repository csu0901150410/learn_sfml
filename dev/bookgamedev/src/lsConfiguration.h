#pragma once

#include <SFML/Graphics.hpp>

#include "lsResourceManager.hpp"

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
	// 全局的资源
	static lsResourceManager<sf::Texture, int> m_textures;

	enum Fonts : int
	{
		kFiraCodeRegular,
	};
	static lsResourceManager<sf::Font, int> m_fonts;

	static void initialize();

private:
	static void init_textures();
	static void init_fonts();
};

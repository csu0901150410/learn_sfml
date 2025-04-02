#pragma once

#include <unordered_map>
#include <memory>

#include <SFML/Audio.hpp>

// sfml����/�������Դ�Ĺ���ģ����
template <typename RESOURCE, typename IDENTIFIER = int>
class lsResourceManager
{
public:
	lsResourceManager(const lsResourceManager&) = delete;
	lsResourceManager& operator=(const lsResourceManager&) = delete;
	lsResourceManager() = default;

	template <typename ... Args>
	void load(const IDENTIFIER& id, Args&& ... args);

	RESOURCE& get(const IDENTIFIER& id) const;

private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> m_map;
};

// ƫ�ػ�ģ�壬����sf::Music
template <typename IDENTIFIER>
class lsResourceManager<sf::Music, IDENTIFIER>
{
public:
	lsResourceManager(const lsResourceManager&) = delete;
	lsResourceManager& operator=(const lsResourceManager&) = delete;
	lsResourceManager() = default;

	template <typename ... Args>
	void load(const IDENTIFIER& id, Args&& ... args);

	sf::Music& get(const IDENTIFIER& id) const;

private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Music>> m_map;
};

#include "lsResourceManager.inl"

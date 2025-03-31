#pragma once

#include <stdexcept>
#include <utility>

template <typename RESOURCE, typename IDENTIFIER>
template <typename ... Args>
void lsResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	std::unique_ptr<RESOURCE> ptr(new RESOURCE);
	if (!ptr->loadFromFile(std::forward<Args>(args)...))
	{
		throw std::runtime_error("Impossible to load file");
	}
	m_map.emplace(id, std::move(ptr));
}

template <typename RESOURCE, typename IDENTIFIER>
RESOURCE& lsResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id) const
{
	return *(m_map.at(id));
}

template <typename IDENTIFIER>
template <typename ... Args>
void lsResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	std::unique_ptr<sf::Music> ptr(new sf::Music);
	if (!ptr->openFromFile(std::forward<Args>(args)...))
	{
		throw std::runtime_error("Impossible to load file");
	}
	m_map.emplace(id, std::move(ptr));
}

template <typename IDENTIFIER>
sf::Music& lsResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
{
	return *(m_map.at(id));
}

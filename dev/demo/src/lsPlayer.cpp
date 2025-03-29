#include "lsPlayer.h"

#define M_PI 3.1415926535897932384626433832795f

lsPlayer::lsPlayer()
	: m_shape(sf::Vector2f(32, 32))
	, m_isMoving(false)
	, m_rotation(0)
{
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setOrigin(sf::Vector2f(16, 16));
}

void lsPlayer::update(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();
	if (0 != m_rotation)
	{
		float angle = (m_rotation > 0 ? 1 : -1) * 180 * seconds;
		m_shape.rotate(angle);
	}

	if (m_isMoving)
	{
		float angle = m_shape.getRotation() / 180 * M_PI - M_PI / 2;
		m_velocity += sf::Vector2f(cos(angle), sin(angle)) * 60.0f * seconds;
	}
	else
	{
		m_velocity = sf::Vector2f(0, 0);
	}

	m_shape.move(seconds * m_velocity);
}

void lsPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape, states);
}


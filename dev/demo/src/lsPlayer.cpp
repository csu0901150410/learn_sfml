#include "lsPlayer.h"

#include "lsAction.h"
#include "lsConfiguration.h"

#define M_PI 3.1415926535897932384626433832795f

lsPlayer::lsPlayer()
	: lsActionTarget(lsConfiguration::m_playerInputs)
	, m_isMoving(false)
	, m_rotation(0)
{
	// 从配置类冲获取资源
	m_sprite.setTexture(lsConfiguration::m_textures.get(lsConfiguration::Textures::kPlayer));
	m_sprite.setOrigin(10, 10);

	// 绑定动作，原本是左键-->旋转，现在是左键-->事件动作-->旋转
	// 这样控制事件动作的挂载/卸载，就能控制是否响应按键了
	bind(lsConfiguration::PlayerInputs::kUp, [this](const sf::Event&)
		{
			m_isMoving = true;
		});

	bind(lsConfiguration::PlayerInputs::kLeft, [this](const sf::Event&)
		{
			m_rotation -= 1;
		});

	bind(lsConfiguration::PlayerInputs::kRight, [this](const sf::Event&)
		{
			m_rotation += 1;
		});
}

void lsPlayer::process_events()
{
	m_isMoving = false;
	m_rotation = 0;
	// 调用父类的方法
	lsActionTarget::process_events();
}

void lsPlayer::update(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();
	if (0 != m_rotation)
	{
		float angle = (m_rotation > 0 ? 1 : -1) * 180 * seconds;
		m_sprite.rotate(angle);
	}

	if (m_isMoving)
	{
		float angle = m_sprite.getRotation() / 180 * M_PI - M_PI / 2;
		m_velocity += sf::Vector2f(cos(angle), sin(angle)) * 60.0f * seconds;
	}
	else
	{
		m_velocity = sf::Vector2f(0, 0);
	}

	m_sprite.move(seconds * m_velocity);
}

void lsPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}


#include "lsPlayer.h"

#include "lsAction.h"

#define M_PI 3.1415926535897932384626433832795f

// 类静态成员定义
lsActionMap<int> lsPlayer::m_playerInputs;

lsPlayer::lsPlayer()
	: lsActionTarget(m_playerInputs)
	, m_shape(sf::Vector2f(32, 32))
	, m_isMoving(false)
	, m_rotation(0)
{
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setOrigin(sf::Vector2f(16, 16));

	// 绑定动作，原本是左键-->旋转，现在是左键-->事件动作-->旋转
	// 这样控制事件动作的挂载/卸载，就能控制是否响应按键了
	bind(PlayerInputs::kUp, [this](const sf::Event&)
		{
			m_isMoving = true;
		});

	bind(PlayerInputs::kLeft, [this](const sf::Event&)
		{
			m_rotation -= 1;
		});

	bind(PlayerInputs::kRight, [this](const sf::Event&)
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

void lsPlayer::set_default_inputs()
{
	// 实际上就是将lsAction对象存储到一个map对象中，用的时候不再通过lsAction对象索引，
	// 而是通过key去索引lsAction
	m_playerInputs.map(PlayerInputs::kUp, lsAction(sf::Keyboard::Up));
	m_playerInputs.map(PlayerInputs::kLeft, lsAction(sf::Keyboard::Left));
	m_playerInputs.map(PlayerInputs::kRight, lsAction(sf::Keyboard::Right));
}

void lsPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape, states);
}


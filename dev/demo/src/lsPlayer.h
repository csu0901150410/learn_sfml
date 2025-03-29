#pragma once

#include <SFML/Graphics.hpp>

#include <utility>

class lsPlayer : public sf::Drawable
{
public:
	lsPlayer(const lsPlayer&) = delete;
	lsPlayer& operator=(const lsPlayer&) = delete;
	lsPlayer();

	// 实现放在头文件，编译时只引用到头文件，模板实例化时就需要访问到定义了
	// 可变数量参数模板/万能引用
	template <typename ... Args>
	inline void set_position(Args&& ... args)
	{
		m_shape.setPosition(std::forward<Args>(args)...);
	}

	void update(sf::Time deltaTime);

private:
	virtual void draw(sf::RenderTarget& target, 
		sf::RenderStates states) const override;

public:
	bool m_isMoving;
	int m_rotation;

private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_velocity;
};

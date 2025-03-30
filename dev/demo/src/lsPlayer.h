#pragma once

#include <SFML/Graphics.hpp>

#include <utility>

#include "lsActionTarget.hpp"

class lsPlayer : public sf::Drawable, public lsActionTarget<int>
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

	void process_events();
	void update(sf::Time deltaTime);

	enum PlayerInputs
	{
		kUp,
		kLeft,
		kRight,
	};
	static void set_default_inputs();

private:
	virtual void draw(sf::RenderTarget& target, 
		sf::RenderStates states) const override;

private:
	bool m_isMoving;
	int m_rotation;

	sf::RectangleShape m_shape;
	sf::Vector2f m_velocity;

	// 当前lsPlayer类应用的一套事件-动作映射，可以换成另一套，即另一个lsActionMap对象
	static lsActionMap<int> m_playerInputs;
};


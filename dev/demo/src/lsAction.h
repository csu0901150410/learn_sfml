#pragma once

#include <SFML/Graphics.hpp>

// 封装事件成为动作
class lsAction
{
public:
	enum Type
	{
		kRealTime = 1,
		kPressed = 1 << 1,
		kReleased = 1 << 2,
	};

	// 拷贝构造函数
	lsAction(const lsAction& other);
	// 拷贝赋值运算符
	lsAction& operator=(const lsAction& other);

	lsAction(const sf::Keyboard::Key& key, int type = Type::kRealTime | Type::kPressed);
	lsAction(const sf::Mouse::Button& button, int type = Type::kRealTime | Type::kPressed);

	bool test() const;

	bool operator==(const sf::Event& event) const;
	bool operator==(const lsAction& other) const;

private:
	// 声明友元，以便友元可访问私有成员
	friend class lsActionTarget;
	sf::Event m_event;
	int m_type;
};

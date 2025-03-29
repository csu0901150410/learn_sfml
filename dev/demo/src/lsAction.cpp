#include "lsAction.h"

lsAction::lsAction(const lsAction& other)
	: m_type(other.m_type)
{
	std::memcpy(&m_event, &other.m_event, sizeof(sf::Event));
}

lsAction::lsAction(const sf::Keyboard::Key& key, int type /*= Type::kRealTime | Type::kPressed*/)
	: m_type(type)
{
	m_event.type = sf::Event::EventType::KeyPressed;
    m_event.key.code = key;
}

lsAction::lsAction(const sf::Mouse::Button& button, int type /*= Type::kRealTime | Type::kPressed*/)
	: m_type(type)
{
	m_event.type = sf::Event::EventType::MouseButtonPressed;
	m_event.mouseButton.button = button;
}

// 检测实时事件
bool lsAction::test() const
{
	bool result = false;
	if (sf::Event::EventType::KeyPressed == m_event.type)
	{
		// m_event.type是KeyPressed时，有可能m_type只有Type::kReleased
		if (m_type & Type::kPressed)
		{
			result = sf::Keyboard::isKeyPressed(m_event.key.code);
		}
	}
	else if (sf::Event::EventType::MouseButtonPressed == m_event.type)
	{
		if (m_type & Type::kPressed)
		{
			result = sf::Mouse::isButtonPressed(m_event.mouseButton.button);
		}
	}

	return result;
}

bool lsAction::operator==(const lsAction& other) const
{
	// 后一个条件调用了事件和动作的匹配
	return (other.m_type == m_type) && (other == m_event);
}

// 匹配事件和动作，事件类型和键值要匹配
bool lsAction::operator==(const sf::Event& event) const
{
	bool result = false;
	switch (event.type)
	{
	case sf::Event::EventType::KeyPressed:
	{
		if (m_type & Type::kPressed && sf::Event::EventType::KeyPressed == m_event.type)
		{
			result = (event.key.code == m_event.key.code);
		}
	}
	break;

	case sf::Event::EventType::KeyReleased:
	{
		// 构造的时候，强制m_event.type是KeyPressed
		if (m_type & Type::kReleased && sf::Event::EventType::KeyPressed == m_event.type)
		{
			result = (event.key.code == m_event.key.code);
		}
	}
	break;

	case sf::Event::EventType::MouseButtonPressed:
	{
		if (m_type & Type::kPressed
			&& sf::Event::EventType::MouseButtonPressed == m_event.type)
		{
			result = (event.mouseButton.button == m_event.mouseButton.button);
		}
	}
	break;

	case sf::Event::EventType::MouseButtonReleased:
	{
		if (m_type & Type::kReleased
			&& sf::Event::EventType::MouseButtonReleased == m_event.type)
		{
			result = (event.mouseButton.button == m_event.mouseButton.button);
		}
	}
	break;
	}

	return result;
}

lsAction& lsAction::operator=(const lsAction& other)
{
	std::memcpy(&m_event, &other.m_event, sizeof(sf::Event));
	m_type = other.m_type;
    return *this;
}


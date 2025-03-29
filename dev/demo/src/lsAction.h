#pragma once

#include <SFML/Graphics.hpp>

// ��װ�¼���Ϊ����
class lsAction
{
public:
	enum Type
	{
		kRealTime = 1,
		kPressed = 1 << 1,
		kReleased = 1 << 2,
	};

	// �������캯��
	lsAction(const lsAction& other);
	// ������ֵ�����
	lsAction& operator=(const lsAction& other);

	lsAction(const sf::Keyboard::Key& key, int type = Type::kRealTime | Type::kPressed);
	lsAction(const sf::Mouse::Button& button, int type = Type::kRealTime | Type::kPressed);

	bool test() const;

	bool operator==(const sf::Event& event) const;
	bool operator==(const lsAction& other) const;

private:
	// ������Ԫ���Ա���Ԫ�ɷ���˽�г�Ա
	friend class lsActionTarget;
	sf::Event m_event;
	int m_type;
};

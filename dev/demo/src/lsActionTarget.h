#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <list>
#include <utility>

#include "lsAction.h"

class lsActionTarget
{
public:
	// �ص���������ָ��
	using action_callback = std::function<void(const sf::Event&)>;

	lsActionTarget();

	// ��ʵʱ�¼�������Ҫ�����ⲿpollEventsʱ���ã�ִֻ��ƥ���¼��ĵ����ص�
	bool process_event(const sf::Event& event) const;

	// ʵʱ�¼�����ִ�е�ǰ�����¼����������лص�
	void process_events() const;

	void bind(const lsAction& action, const action_callback& callback);
	void unbind(const lsAction& action);

private:
	// ��list������vector��ԭ����list���Ը�Ч�����ɾ��
	std::list<std::pair<lsAction, action_callback>> m_eventsRealTime;
	std::list<std::pair<lsAction, action_callback>> m_eventsPoll;
};

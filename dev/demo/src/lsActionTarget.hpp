#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <list>
#include <utility>

#include "lsAction.h"
#include "lsActionMap.hpp"

// �󶨶����ͻص�
template <typename T = int>
class lsActionTarget
{
public:
	lsActionTarget(const lsActionTarget<T>&) = delete;
	lsActionTarget<T>& operator=(const lsActionTarget<T>&) = delete;

	// �ص���������ָ��
	using action_callback = std::function<void(const sf::Event&)>;

	lsActionTarget(const lsActionMap<T>& map);

	// ��ʵʱ�¼�������Ҫ�����ⲿpollEventsʱ���ã�ִֻ��ƥ���¼��ĵ����ص�
	bool process_event(const sf::Event& event) const;

	// ʵʱ�¼�����ִ�е�ǰ�����¼����������лص�
	void process_events() const;

	// ��keyȥ��������
	void bind(const T& key, const action_callback& callback);
	void unbind(const T& key);

private:
	// ��list������vector��ԭ����list���Ը�Ч�����ɾ��
	std::list<std::pair<T, action_callback>> m_eventsRealTime;
	std::list<std::pair<T, action_callback>> m_eventsPoll;

	const lsActionMap<T>& m_actionMap;
};

#include "lsActionTarget.inl"

#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <list>
#include <utility>

#include "lsAction.h"

class lsActionTarget
{
public:
	// 回调函数函数指针
	using action_callback = std::function<void(const sf::Event&)>;

	lsActionTarget();

	// 非实时事件处理，主要用在外部pollEvents时调用，只执行匹配事件的单个回调
	bool process_event(const sf::Event& event) const;

	// 实时事件处理，执行当前满足事件条件的所有回调
	void process_events() const;

	void bind(const lsAction& action, const action_callback& callback);
	void unbind(const lsAction& action);

private:
	// 用list而不是vector的原因是list可以高效插入和删除
	std::list<std::pair<lsAction, action_callback>> m_eventsRealTime;
	std::list<std::pair<lsAction, action_callback>> m_eventsPoll;
};

#include "lsActionTarget.h"

lsActionTarget::lsActionTarget()
{

}

bool lsActionTarget::process_event(const sf::Event& event) const
{
	bool result = false;
	for (auto& action : m_eventsPoll)
	{
		// 反过来不行，这个运算符要在类外以非成员函数形式重载
		// if (event == action.first)
		if (action.first == event)
		{
			action.second(event);
			result = true;
			break;
		}
	}
	return result;
}

void lsActionTarget::process_events() const
{
	for (auto& action : m_eventsRealTime)
	{
		if (action.first.test())
			action.second(action.first.m_event);
	}
}

void lsActionTarget::bind(const lsAction& action, const action_callback& callback)
{
	bool rt = (action.m_type & lsAction::Type::kRealTime);
	(rt ? m_eventsRealTime : m_eventsPoll).emplace_back(action, callback);
}

void lsActionTarget::unbind(const lsAction& action)
{
	auto remove_func = [&action](const std::pair<lsAction, action_callback>& pair) {
		return (pair.first == action);
	};

	bool rt = (action.m_type & lsAction::Type::kRealTime);
	(rt ? m_eventsRealTime : m_eventsPoll).remove_if(remove_func);
}


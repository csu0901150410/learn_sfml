#pragma once

template <typename T>
lsActionTarget<T>::lsActionTarget(const lsActionMap<T>& map)
	: m_actionMap(map)
{

}

template <typename T>
bool lsActionTarget<T>::process_event(const sf::Event& event) const
{
	bool result = false;
	for (auto& pair : m_eventsPoll)
	{
		// 反过来不行，这个运算符要在类外以非成员函数形式重载
		// if (event == action)
		if (m_actionMap.get(pair.first) == event)
		{
			pair.second(event);
			result = true;
			break;
		}
	}
	return result;
}

template <typename T>
void lsActionTarget<T>::process_events() const
{
	for (auto& pair : m_eventsRealTime)
	{
		const lsAction& action = m_actionMap.get(pair.first);
		if (action.test())
			pair.second(action.m_event);
	}
}

template <typename T>
void lsActionTarget<T>::bind(const T& key, const action_callback& callback)
{
	const lsAction& action = m_actionMap.get(key);
	bool rt = (action.m_type & lsAction::Type::kRealTime);
	(rt ? m_eventsRealTime : m_eventsPoll).emplace_back(key, callback);
}

template <typename T>
void lsActionTarget<T>::unbind(const T& key)
{
	auto remove_func = [&key](const std::pair<lsAction, action_callback>& pair)
		{
			return (pair.first == key);
		};

	const lsAction& action = m_actionMap.get(key);
	bool rt = (action.m_type & lsAction::Type::kRealTime);
	(rt ? m_eventsRealTime : m_eventsPoll).remove_if(remove_func);
}

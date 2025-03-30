#pragma once

template <typename T>
inline void lsActionMap<T>::map(const T& key, const lsAction& action)
{
	m_map.emplace(key, action);
}

template <typename T>
inline const lsAction& lsActionMap<T>::get(const T& key) const
{
	return m_map.at(key);
}

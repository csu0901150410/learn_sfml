#pragma once

#include <unordered_map>

#include "lsAction.h"

template <typename T = int>
class lsActionMap
{
public:
	lsActionMap(const lsActionMap<T>&) = delete;
	lsActionMap<T>& operator=(const lsActionMap<T>&) = delete;
	lsActionMap() = default;

	void map(const T& key, const lsAction& action);
	const lsAction& get(const T& key) const;

private:
	std::unordered_map<T, lsAction> m_map;
};

#include "lsActionMap.inl"

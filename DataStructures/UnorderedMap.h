#pragma once

#include <iostream>
#include <vector>
#include "Pair.h"

namespace agl {

	template<typename keyType, typename valueType>
	class UnorderedMap
	{
	public:
		UnorderedMap() { }

		UnorderedMap(std::initializer_list<std::pair<keyType, valueType>> map)
		{
			for (std::pair<keyType, valueType> pair : map)
				m_Map.emplace_back(pair.first, pair.second);
		}

		void insert(Pair<keyType, valueType> Pair)
		{
			m_Map.push_back(Pair);
		}

		void erase(keyType key)
		{
			std::vector<Pair<keyType, valueType>> temp;
			for (int i = 0; i < m_Map.size(); i++)
				if (m_Map[i].key != key)
					temp.push_back(m_Map[i]);

			m_Map = temp;
		}

		const bool empty() const
		{
			return m_Map.empty();
		}

		const int size() const
		{
			return m_Map.size();
		}

		void clear()
		{
			m_Map.clear();
		}

		valueType& operator[](keyType key)
		{
			for (int i = 0; i < m_Map.size(); i++)
				if (m_Map[i].key == key)
					return m_Map[i].value;

			valueType temp{};
			return temp;
		}

		const valueType& operator[](keyType key) const
		{
			for (int i = 0; i < m_Map.size(); i++)
				if (m_Map[i].key == key)
					return m_Map[i].value;

			valueType temp{};
			return temp;
		}

		template<typename _itemType, typename _valueType>
		friend std::ostream& operator<<(std::ostream& stream, UnorderedMap<_itemType, _valueType> UnorderedMap);
	private:
		std::vector<Pair<keyType, valueType>> m_Map;
	};

	template<typename _itemType, typename _valueType>
	std::ostream& operator<<(std::ostream& stream, UnorderedMap<_itemType, _valueType> UnorderedMap)
	{
		stream << "[ ";
		for (int i = 0; i < UnorderedMap.m_Map.size(); i++)
			if (i < UnorderedMap.m_Map.size() - 1)
				stream << UnorderedMap.m_Map[i].key << ", ";
			else
				stream << UnorderedMap.m_Map[i];

		stream << " ]";

		return stream;
	}
}
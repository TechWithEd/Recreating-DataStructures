#pragma once

#include <iostream>
#include <algorithm>
#include "Pair.h"

namespace agl {
	template<typename keyType, typename valueType>
	class Map
	{
	private:
		std::vector<Pair<keyType, valueType>> m_Map;
	public:
		Map() { }

		Map(std::initializer_list<std::pair<keyType, valueType>> map)
		{
			for (std::pair<keyType, valueType> pair : map)
				m_Map.emplace_back(pair.first, pair.second);
		}

		void insert(Pair<keyType, valueType> pair)
		{
			m_Map.push_back(pair);
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
			sort();
			for (int i = 0; i < m_Map.size(); i++)
				if (m_Map[i].key == key)
				{
					return m_Map[i].value;
				}

			valueType temp{};
			return temp;
		}

		const valueType& operator[](keyType key) const
		{
			sort();
			for (int i = 0; i < m_Map.size(); i++)
				if (m_Map[i].key == key)
					return m_Map[i].value;

			valueType temp{};
			return temp;
		}

		template<typename keyType, typename valueType>
		friend std::ostream& operator<<(std::ostream&, Map<keyType, valueType>);
	private:
		void swap(int index1, int index2)
		{
			Pair<keyType, valueType> temp = m_Map[index1];
			m_Map[index1] = m_Map[index2];
			m_Map[index2] = temp;
		}

		void sort()
		{
			std::sort(m_Map.begin(), m_Map.end(), [](Pair<keyType, valueType> a, Pair<keyType, valueType> b)
				{
					return a.value < b.value;
				});
		}
	};

	template<typename keyType, typename valueType>
	std::ostream& operator<<(std::ostream& stream, Map<keyType, valueType> map)
	{
		map.sort();
		stream << '[';
		for (int i = 0; i < map.size(); i++)
			if (i < map.size() - 1)
				stream << map.m_Map[i] << ", ";
			else
				stream << map.m_Map[i];
		std::cout << ']';

		return stream;
	}
}
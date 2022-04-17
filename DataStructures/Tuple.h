#pragma once

#include <iostream>
#include <vector>
#include <variant>

namespace agl {
	template<typename ...types>
	class Tuple
	{
	private:
		std::vector<std::variant<types...>> m_Array;
	public:
		Tuple() { }

		Tuple(const std::vector<std::variant<types...>>& tuple)
		{
			for (int i = 0; i < tuple.size(); i++)
				m_Array.push_back(tuple[i]);
		}

		template<typename T>
		T& get(int index)
		{
			return std::get<T>(m_Array[index]);
		}

		void swap(int first, int last)
		{
			auto temp = m_Array[first];
			m_Array[first] = m_Array[last];
			m_Array[last] = temp;
		}
	};
}
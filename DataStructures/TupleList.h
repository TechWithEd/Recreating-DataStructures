#pragma once

#include <any>
#include <vector>
#include <iostream>

namespace agl {
	class TupleList
	{
	public:
		TupleList()
		{
			
		}

		TupleList(const std::vector<std::any>& other)
			: m_Array(other) { }

		void insert(const std::any& item)
		{
			m_Array.push_back(item);
		}

		void removeLast()
		{
			m_Array.pop_back();
		}

		void clear()
		{
			m_Array.clear();
		}

		size_t size()
		{
			return m_Array.size();
		}

		size_t capacity()
		{
			return m_Array.capacity();
		}

		template<typename T>
		T& get(int index)
		{
			return std::any_cast<T>(m_Array[index]);
		}

		void swap(int first, int last)
		{
			std::any temp = m_Array[first];
			m_Array[first] = m_Array[last];
			m_Array[last] = temp;
		}
	private:
		std::vector<std::any> m_Array;
	};
}
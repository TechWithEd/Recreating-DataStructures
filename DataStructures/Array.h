#pragma once

#include <iostream>

namespace agl {
	template<typename Array>
	class ArrayIterator
	{
	public:
		using ValueType = typename Array::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
	public:
		ArrayIterator(PointerType ptr)
			: m_Ptr(ptr) { }
 
		ArrayIterator& operator++()
		{
			m_Ptr++;
			return *this;
		}

		ArrayIterator operator++(int)
		{
			ArrayIterator iterator = *this;
			++(*this);
			return iterator;
		}

		ArrayIterator& operator--()
		{
			m_Ptr--;
			return *this;
		}

		ArrayIterator operator--(int)
		{
			ArrayIterator iterator = *this;
			--(*this);
			return iterator;
		}

		ReferenceType operator[](int index)
		{
			return *(m_Ptr + index);
		}

		PointerType operator->()
		{
			return m_Ptr;
		}

		ReferenceType operator*()
		{
			return *m_Ptr;
		}

		bool operator==(const ArrayIterator& other) const
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!=(const ArrayIterator& other) const
		{
			return !(*this == other);
		}
	private:
		PointerType m_Ptr;
	};

    template<typename T, const size_t length>
    class Array
    {
    private:
        T m_Array[length];
    public:
		using ValueType = T;
		using Iterator = ArrayIterator<Array<T, length>>;

        Array()
		{

		}

		Array(std::initializer_list<T> il)
		{
			Iterator pointer = begin();
			for (int i = il.size(); i < length; i++)
				m_Array[i] = NULL;

			for (const T& i : il)
				*pointer++ = i;
		}

        T IndexOf(T item)
        {
            for (int i = 0; i < length; i++)
                if (m_Array[i] == item)
                    return i;

            return -1;
        }

        T& operator[](int index)
		{
			return m_Array[index];
		}

        bool operator==(Array other)
		{
			return !(other.m_Array == m_Array);
		}

		bool operator!=(Array other)
		{
			return !(other.m_Array != m_Array);
		}

        const size_t Size() const
		{
			return length;
		}

		T* data()
		{
			return m_Array;
		}

		Iterator begin()
		{
			return Iterator(m_Array);
		}

		Iterator end()
		{
			return Iterator(m_Array + length);
		}
    };
}
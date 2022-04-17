#pragma once

namespace agl {
	template<typename Vector>
	class VectorIterator
	{
	public:
		using ValueType = typename Vector::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
	public:
		VectorIterator(const PointerType& ptr)
			: m_Ptr(std::move(ptr)) { }

		VectorIterator& operator++()
		{
			m_Ptr++;
			return *this;
		}

		VectorIterator operator++(int)
		{
			VectorIterator iterator = *this;
			++(*this);
			return iterator;
		}

		VectorIterator& operator--()
		{
			m_Ptr--;
			return *this;
		}

		VectorIterator operator--(int)
		{
			VectorIterator iterator = *this;
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

		bool operator==(const VectorIterator& other) const
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!=(const VectorIterator& other) const
		{
			return !(*this == other);
		}
	private:
		PointerType m_Ptr;
	};

	template<typename T>
	class Vector
	{
	public:
		using ValueType = T;
		using Iterator = VectorIterator<Vector<T>>;
	public:
		Vector()
		{
			ReAlloc(2);
		}

		Vector(std::initializer_list<T> values)
		{
			ReAlloc(2);
			for (const T& value : values)
			{
				if (m_Size >= m_Capacity)
					ReAlloc(m_Capacity + m_Capacity / 2);

				m_Array[m_Size] = std::move(value);
				m_Size++;
			}
		}

		~Vector()
		{
			Clear();
			delete[] m_Array;
		}

		void PushBack(T&& value)
		{
			if (m_Size >= m_Capacity)
				ReAlloc(m_Capacity + m_Capacity / 2);
			
			m_Array[m_Size] = std::move(value);
			m_Size++;
		}

		template<typename... Args>
		T& EmplaceBack(Args&&... args)
		{
			if (m_Size >= m_Capacity)
				ReAlloc(m_Capacity + m_Capacity / 2);

			new(&m_Array[m_Size]) T(std::forward<Args>(args)...);
			return m_Array[m_Size++];
		}

		void PopBack()
		{
			if (m_Size > 0)
			{
				m_Array[m_Size].~T();
				m_Size--;
			}
		}

		void Clear()
		{
			const size_t size = m_Size;
			for (int i = 0; i < size; i++)
				m_Array[i].~T();

			m_Size = 0;
		}

		void Erase(int index)
		{
			if (index < 0 || index >= m_Size)
				throw std::invalid_argument("...");

			const int size = m_Size;
			m_Array[index].~T();

			for (int i = index; i < size; i++)
				m_Array[i] = m_Array[i + 1];

			m_Size--;
		}
		
		size_t Size()
		{
			return m_Size;
		}

		size_t Capacity()
		{
			return m_Capacity;
		}

		T& operator[](int index)
		{
			if (index < 0 || index >= m_Size)
				throw std::invalid_argument("...");

			return m_Array[index];
		}

		const T& operator[](int index) const
		{
			if (index < 0 || index >= m_Size)
				throw std::invalid_argument("...");

			return m_Array[index];
		}

		Iterator begin()
		{
			return Iterator(m_Array);
		}

		Iterator end()
		{
			return Iterator(m_Array + m_Size);
		}

		void Sort(int startingIndex, int endingIndex, bool(*func)(T, T))
		{
			for (int i = startingIndex; i < endingIndex + 1; i++)
				for (int j = startingIndex + 1; j < endingIndex + 1; j++)
					if (func(m_Array[j], m_Array[j - 1]))
						Swap(j, j - 1);
		}

		void Swap(int index1, int index2)
		{
			const T temp = m_Array[index1];
			m_Array[index1] = m_Array[index2];
			m_Array[index2] = temp;
		}

		void Reverse()
		{
			Vector<T> reversedVector;

			for (int i = m_Size - 1; i > -1; i--)
				reversedVector.EmplaceBack(m_Array[i]);

			Clear();

			for (int i = 0; i < reversedVector.Size(); i++)
				EmplaceBack(reversedVector[i]);
		}
	private:
		void ReAlloc(size_t newCapacity)
		{
			T* temp = new T[newCapacity];
			if (newCapacity < m_Size)
				m_Size = newCapacity;
			for (int i = 0; i < m_Size; i++)
				temp[i] = std::move(m_Array[i]);
		
			delete[] m_Array;
			m_Array = temp;
			m_Capacity = newCapacity;
		}
	private:
		size_t m_Size;
		size_t m_Capacity;
		T* m_Array;
	};
}
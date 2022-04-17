#pragma once

#include <iostream>

namespace agl {
	template<typename _Type>
	class UniquePtr
	{
	private:
		_Type* m_Object;

	public:
		UniquePtr(_Type* Object)
		{
			m_Object = Object;
		}

		UniquePtr(const UniquePtr<_Type>& other) = delete;

		~UniquePtr()
		{
			delete m_Object;
		}

		_Type& operator*()
		{
			return *m_Object;
		}

		_Type* operator->()
		{
			return m_Object;
		}

		_Type* get()
		{
			return m_Object;
		}

		void reset(_Type* object)
		{
			delete m_Object;
			m_Object = object;
		}

		UniquePtr operator=(_Type* other) = delete;
	};
}
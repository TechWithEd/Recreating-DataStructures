#pragma once

#include <iostream>
#include <string>

namespace agl {
	class String
	{
	private:
		char* m_String = (char*)"";
		size_t m_Size = 0;
	public:
		String() = default;

		String(const char* string)
		{
			m_Size = strlen(string);
			m_String = new char[m_Size + 1];
			memcpy(m_String, string, m_Size);
			m_String[m_Size] = 0;
		}

		String(String& other)
		{
			m_Size = strlen(other.m_String);
			m_String = new char[other.m_Size + 1];
			memcpy(m_String, other.m_String, m_Size);
			m_String[m_Size] = 0;
		}

		~String()
		{
			m_String = new char[0];
			delete[] m_String;
		}

		const char* toLowerCase()
		{
			for (size_t i = 0; i < m_Size; i++)
				m_String[i] = tolower(m_String[i]);

			return m_String;
		}

		const char* toUpperCase()
		{
			for (size_t i = 0; i < m_Size; i++)
				m_String[i] = toupper(m_String[i]);

			return m_String;
		}

		size_t length()
		{
			return m_Size;
		}

		friend std::ostream& operator<<(std::ostream& stream, String& string);

		bool operator==(String other)
		{
			return other.m_String == m_String;
		}

		bool operator!=(String other)
		{
			return !(other.m_String == m_String);
		}

		bool operator==(const char* other)
		{
			return other == m_String;
		}

		bool operator!=(const char* other)
		{
			return other != m_String;
		}

		char& operator[](int index)
		{
			return m_String[index];
		}

		friend std::istream& operator>>(std::istream& stream, String& string);
	};

	std::ostream& operator<<(std::ostream& stream, String& string)
	{
		return stream << string.m_String;
	}

	std::istream& operator>>(std::istream& stream, String& string)
	{
		return stream >> string.m_String;
	}
}
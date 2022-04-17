#pragma once

#include <iostream>
#include <tuple>

namespace agl {
	template<typename first, typename second>
	class Variant
	{
	private:
		first firstVar;
		second secondVar;
	public:
		Variant() { }

		Variant(first firstVar, second secondVar)
		{
			this->firstVar = firstVar;
			this->secondVar = secondVar;
		}

		first& getFirst()
		{
			return firstVar;
		}

		second& getSecond()
		{
			return secondVar;
		}
	};
}
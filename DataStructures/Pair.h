#pragma once

namespace agl {
	template<typename keyType, typename valueType>
	struct Pair
	{
		keyType key;
		valueType value;

		Pair(keyType key, valueType value)
			: key(key), value(value) { }

		Pair() { };
	};

	template<typename keyType, typename valueType>
	std::ostream& operator<<(std::ostream& stream, Pair<keyType, valueType> pair)
	{
		return stream << pair.key << '=' << pair.value;
	}
}
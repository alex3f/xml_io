#pragma once
#include "interfaces/XmlDocNode.h"

namespace io
{
	template<typename T, typename = void>
	struct trait_functions;

	template<typename T, std::enable_if_t<std::is_arithmetic<T>::value, int> = 0>
	struct arithmetic_trait_functions
	{
		static auto constexpr name() { return typeid(T).name(); }
		static void serialize(T value, XmlDocNodePtr const &node) { node->set_value(std::to_string(value)); }
	};

	template<typename T>
	struct trait_functions<T, typename std::enable_if_t<std::is_integral<T>::value>> : arithmetic_trait_functions<T>
	{
		static void unserialize(T &value, XmlDocNodePtr const &node) { value = std::stoi(node->get_value()); }
	};

	template<typename T>
	struct trait_functions<T, typename std::enable_if_t<std::is_floating_point<T>::value>> : arithmetic_trait_functions<T>
	{
		static void unserialize(T &value, XmlDocNodePtr const &node) { value = std::stod(node->get_value()); }
	};

} // namespace io

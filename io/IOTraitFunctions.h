#pragma once
#include "interfaces/XmlDocNode.h"

namespace io
{
	template<typename T, typename = void>
	struct trait_functions;

	template<typename T, std::enable_if_t<std::is_arithmetic<T>::value, int> = 0>
	struct arithmetic_trait_functions
	{
		static auto const name() 
		{ 
			std::string name(typeid(T).name());

			// NOTE: поскольку имя используетмся для именования узла xml, оно не должно содержать пробелов. 
			std::replace(name.begin(), name.end(), ' ', '_');

			return name; 
		}
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
		static void unserialize(T &value, XmlDocNodePtr const &node) { value = std::stof(node->get_value()); }
	};

} // namespace io

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

	template<>
	struct trait_functions<std::string>
	{
		static auto constexpr name() { return "std::string"; }
		static void serialize(std::string const &str, XmlDocNodePtr const &node) { node->set_value(str); }
		static void unserialize(std::string &str, XmlDocNodePtr const &node) { str = std::move(node->get_value()); }
	};

	template<typename T>
	extern std::string get_class_name();

	template<typename T>
	struct trait_functions<T, std::enable_if_t<std::is_class<T>::value>>
	{
		static auto constexpr name() { return get_class_name<T>(); }
		static void serialize(T const &value, XmlDocNodePtr const &node) { value.serialize(node); }
		static void unserialize(T &value, XmlDocNodePtr const &node) { value.unserialize(node); }
	};

} // namespace io

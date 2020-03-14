#pragma once
#include "interfaces/XmlDocNode.h"

namespace
{
	template<typename T>
	void serialize_fundamental(T const &value, XmlDocNodePtr const &node);

	template<typename T>
	void unserialize_fundamental(T &value, XmlDocNodePtr const &node);
}

namespace io
{
	template<typename T>
	struct functions
	{
		static_assert(sizeof(T) == -1, "io functions must be specialized");

		static auto constexpr name() { return ""; }
		static auto to_string(T const &) { return ""; }
		static auto from_string(std::string const &str) { return T{}; }
		static void serialize(T const &, XmlDocNodePtr const &) {}
		static void unserialize(T &, XmlDocNodePtr const &) {}
	};

	template<>
	struct functions<int>
	{
		static auto constexpr name() { return "int"; }
		static auto to_string(int value) { return std::to_string(value); }
		static auto from_string(std::string const &str) { return std::stoi(str); }
		static void serialize(int value, XmlDocNodePtr const &node) { serialize_fundamental(value, node); }
		static void unserialize(int &value, XmlDocNodePtr const &node) { unserialize_fundamental(value, node); }
	};

} // namespace io

namespace
{
	template<typename T>
	void serialize_fundamental(T const &value, XmlDocNodePtr const &node)
	{
		node->set_value(io::functions<T>::to_string(value));
	}

	template<typename T>
	void unserialize_fundamental(T &value, XmlDocNodePtr const &node)
	{
		value = io::functions<T>::from_string(node->get_value());
	}
}
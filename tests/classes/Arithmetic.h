#pragma once
#include "interfaces/XmlDocNode.h"

namespace test
{
	struct ArithmeticTypes
	{
		char ch{};
		short sh{};
		unsigned int uns{};
		int i{};
		float f{};
		double d{};

		bool operator==(ArithmeticTypes const &rhs) const;

		void serialize(XmlDocNodePtr const &node) const;
		bool unserialize(XmlDocNodePtr const &node);
	};


} // namespace test
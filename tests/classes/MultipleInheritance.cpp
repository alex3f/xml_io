#include "main/pch.h"
#include "tests/classes/MultipleInheritance.h"
#include "io/XmlIOStream.h"

namespace test
{
	namespace multiple_inheritance
	{
		void Base::serialize(XmlDocNodePtr const &node) const
		{
		}

		bool Base::unserialize(XmlDocNodePtr const &node)
		{
			return true;
		}

		void Derived1::serialize(XmlDocNodePtr const &node) const
		{
		}

		bool Derived1::unserialize(XmlDocNodePtr const &node)
		{
			return true;
		}

		void Pointers::serialize(XmlDocNodePtr const &node) const
		{
		}

		void Pointers::unserialize(XmlDocNodePtr const &node)
		{
		}

	} // namespace multiple_inheritance

} // namespace test
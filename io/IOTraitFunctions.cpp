#include "main/pch.h"
#include "io/IOTraitFunctions.h"

namespace test
{
	namespace multiple_inheritance
	{
		class Base;
	}

	namespace virtual_inheritance
	{
		struct B;
	}

} // namespace test

namespace io
{

	template<> std::string get_class_name<test::virtual_inheritance::B>()
	{
		return AS_TEXT(virtual_inheritance::B);
	}

	template<> std::string get_class_name<test::multiple_inheritance::Base>()
	{
		return AS_TEXT(multiple_inheritance::Base);
	}

} // namespace io

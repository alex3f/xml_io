#include "main/pch.h"
#include "io/IOTraitFunctions.h"

namespace test
{
	namespace multiple_inheritance
	{
		class Base;
	}
}

namespace io
{
	template<> std::string get_class_name<test::multiple_inheritance::Base>() 
	{ 
		return AS_TEXT(multiple_inheritance::Base); 
	}

} // namespace io

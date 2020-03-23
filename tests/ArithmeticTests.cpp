#include "main/pch.h"
#include "tests/SerializationTests.h"
#include "tests/classes/Arithmetic.h"

namespace serialization_tests
{
	namespace arithmetic
	{
		void struct_with_arithmetic_types()
		{
			std::string const filename("results/arithmetic_types_serialization.xml");

			test::ArithmeticTypes const saved{'a', 0xCD, 3, -4, -2.1f, 3.1415926};

			test_common_helpers::serialize(saved, filename);

			test::ArithmeticTypes loaded{};
			loaded.unserialize(xml::Doc::make_by_file(filename));

			assert(loaded == saved);
		}

	} // namespace arithmetic

} // namespace serialization_tests
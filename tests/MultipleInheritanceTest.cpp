#include "main/pch.h"
#include "tests/SerializationTests.h"
#include "tests/classes/MultipleInheritance.h"

namespace serialization_tests
{
	namespace inheritance
	{
		void multiple()
		{
			using namespace test::multiple_inheritance;

			std::string const filename("results/multiple_inheritance_serialization.xml");

			Pointers const saved{};
			test_common_helpers::serialize(saved, filename);

			Pointers loaded{};
			loaded.unserialize(xml::Doc::make_by_file(filename));
		}

	} // namespace inheritance

} // namespace test
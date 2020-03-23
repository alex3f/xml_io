#include "main/pch.h"
#include "tests/SerializationTests.h"
#include "tests/classes/Ints.h"

namespace
{
	template<typename T>
	auto unserialize(std::string const &filename)
	{
		auto doc = xml::Doc::make_by_file(filename);
		assert(doc);

		return T::unserialize(doc);
	}

} // namespace

namespace serialization_tests
{
	namespace ints
	{
		void structs_with_ints()
		{
			test::Ints const init(test::IntWithId::test_range[1], 21, -98, 13);

			std::string const filename("results/int_serialization.xml");

			test_common_helpers::serialize(init, filename);
			auto loaded = ::unserialize<test::Ints>(filename);

			assert(loaded && (*loaded == init));
		}

		void nested_int_structs()
		{
			test::Ints const init_val(test::IntWithId::test_range[0], 5, 6, 7);
			test::Ints const init_ptr(test::IntWithId::test_range[1], 13, 14, 15);
			auto const &init_ref = test::IntWithId::test_range[2];

			std::string const filename("results/nested_int_serialization.xml");

			test::NestedInts const nested_ints(init_ref, init_val, init_ptr);

			test_common_helpers::serialize(nested_ints, filename);
			auto loaded = ::unserialize<test::NestedInts>(filename);

			assert(loaded && loaded->ptr);
			assert((loaded->val == init_val) && (*(loaded->ptr) == init_ptr) && (loaded->ref == init_ref));
		}

	} // namespace ints

} // namespace serialization_tests
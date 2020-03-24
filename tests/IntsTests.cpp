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

		void int_pointers()
		{
			int constexpr init_value1 = 193;
			int constexpr init_value2 = 0;

			std::string const filename("results/int_pointers.xml");

			test::PointersToInts saved{};

			saved.p1 = factory::create<int>(init_value1);
			saved.p2 = factory::create<int>(init_value2);
			saved.p3 = saved.p1;
			saved.p4 = nullptr;

			test_common_helpers::serialize(saved, filename);

			test::PointersToInts loaded{};
			loaded.unserialize(xml::Doc::make_by_file(filename));

			assert(loaded.p1 && *(loaded.p1) == init_value1);
			assert(loaded.p2 && *(loaded.p2) == init_value2);
			assert(loaded.p3 == loaded.p1);
			assert(loaded.p4 == nullptr);
		}

	} // namespace ints

} // namespace serialization_tests
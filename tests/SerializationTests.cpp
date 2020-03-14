#include "main/pch.h"
#include "tests/SerializationTests.h"
#include "tests/classes/Ints.h"
#include "xml/XmlDoc.h"

namespace
{
	template<typename T>
	void serizlize(T const &value, std::string const &filename)
	{
		auto doc = xml::Doc::make_empty();

		value.serialize(doc);

		doc->save_to_file(filename);
	}

	template<typename T>
	auto unserizlize(std::string const &filename)
	{
		auto doc = xml::Doc::make_by_file(filename);
		assert(doc);

		return T::unserialize(doc);
	}

} // namespace

namespace serialization_tests
{
	void ints()
	{
		test::Ints const init(test::IntWithId::test_range[1], 21, -98, 13);

		std::string const filename("results/int_serialization.xml");

		serizlize(init, filename);
		auto loaded = unserizlize<test::Ints>(filename);

		assert(loaded && (*loaded == init));
	}

	void nested_int_structs()
	{
		test::Ints const init_val(test::IntWithId::test_range[0], 5, 6, 7);
		test::Ints const init_ptr(test::IntWithId::test_range[1], 13, 14, 15);
		auto const &init_ref = test::IntWithId::test_range[2];

		std::string const filename("results/nested_int_serialization.xml");

		test::NestedInts const nested_ints(init_ref, init_val, init_ptr);

		serizlize(nested_ints, filename);
		auto loaded = unserizlize<test::NestedInts>(filename);

		assert(loaded && loaded->ptr);
		assert((loaded->val == init_val) && (*(loaded->ptr) == init_ptr) && (loaded->ref == init_ref));
	}

} // namespace serialization_tests
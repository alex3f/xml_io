#pragma once
#include "xml/XmlDoc.h"

namespace serialization_tests
{
	namespace ints
	{
		void structs_with_ints();
		void nested_int_structs();

	} // namespace ints

	namespace arithmetic
	{
		void struct_with_arithmetic_types();

	} // namespace arithmetic

} // namespace serialization_tests

namespace test_common_helpers
{
	template<typename T>
	void serialize(T const &value, std::string const &filename)
	{
		auto doc = xml::Doc::make_empty();

		value.serialize(doc);

		doc->save_to_file(filename);
	}

} // namespace test_helpers
#pragma once
#include "xml/XmlDoc.h"

namespace serialization_tests
{
	namespace ints
	{
		void structs_with_ints();
		void nested_int_structs();
		void int_pointers();

	} // namespace ints

	namespace arithmetic
	{
		void struct_with_arithmetic_types();

	} // namespace arithmetic

	namespace inheritance
	{
		void multiple();
		void diamond();
		void double_diamond();

	} // namespace inheritance

	void collection();

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
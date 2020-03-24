#include "pch.h"
#include "tests/SerializationTests.h"

int main()
{
	serialization_tests::ints::structs_with_ints();
	serialization_tests::ints::nested_int_structs();
	serialization_tests::ints::int_pointers();

	serialization_tests::arithmetic::struct_with_arithmetic_types();

	return 0;
}

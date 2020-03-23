#include "pch.h"
#include "tests/SerializationTests.h"

int main()
{
	serialization_tests::ints::structs_with_ints();
	serialization_tests::ints::nested_int_structs();

	return 0;
}

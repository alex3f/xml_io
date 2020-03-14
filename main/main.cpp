#include "pch.h"
#include "tests/SerializationTests.h"

int main()
{
	serialization_tests::ints();
	serialization_tests::nested_int_structs();

	return 0;
}

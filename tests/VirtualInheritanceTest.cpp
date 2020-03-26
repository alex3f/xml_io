#include "main/pch.h"
#include "tests/SerializationTests.h"
#include "tests/classes/VirtualInheritance.h"
#include "utils/PointerTable.h"

namespace serialization_tests
{
	namespace inheritance
	{
		void diamond()
		{
			using namespace test::virtual_inheritance;

			std::string const filename("results/virtual_inheritance_serialization.xml");

			D1 const d1_init(0, 1);
			Join const join_init(0, 1, 2, 3);
			JoinD2 const join_d2_init(join_init, 5);
			JoinJoin const jjoin_init(join_init, 4, 5, 6);

			Pointers saved;

			saved.b_ptr1 = factory::create<D1>(d1_init);
			saved.b_ptr2 = factory::create<Join>(join_init);
			saved.b_ptr3 = factory::create<JoinD2>(join_d2_init);
			saved.b_ptr4 = factory::create<JoinJoin>(jjoin_init);

			test_common_helpers::serialize(saved, filename);

			Pointers loaded;
			loaded.unserialize(xml::Doc::make_by_file(filename));

			auto d1 = std::dynamic_pointer_cast<D1>(loaded.b_ptr1);
			auto join = std::dynamic_pointer_cast<Join>(loaded.b_ptr2);
			auto join_d2 = std::dynamic_pointer_cast<JoinD2>(loaded.b_ptr3);
			auto jjoin = std::dynamic_pointer_cast<JoinJoin>(loaded.b_ptr4);

			assert(d1 && *d1 == d1_init);
			assert(join && *join == join_init);
			assert(join_d2 && *join_d2 == join_d2_init);
			assert(jjoin && *jjoin == jjoin_init);
		}

		void double_diamond()
		{

		}

	} // namespace inheritance

} // namespace test

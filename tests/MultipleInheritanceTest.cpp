#include "main/pch.h"
#include "tests/SerializationTests.h"
#include "tests/classes/MultipleInheritance.h"
#include "utils/PointerTable.h"

namespace serialization_tests
{
	namespace inheritance
	{
		void multiple()
		{
			using namespace test::multiple_inheritance;

			Base const base_init('b');
			Derived1 const derived1_init('b', 'd', 1);

			ptr_t<double> const double_ptr_init = factory::create<double>(3.1415926);
			Derived2 const derived2_init('b', "holds pointer", double_ptr_init);

			DerivedFromDerived2 const derived_from_derived2_init(derived2_init, 321);

			std::string const filename("results/multiple_inheritance_serialization.xml");

			Pointers saved{};

			saved.base_ptr = factory::create<Base>(base_init);
			saved.base_ptr1 = factory::create<Derived1>(derived1_init);
			saved.base_ptr2 = factory::create<Derived2>(derived2_init);
			saved.base_ptr3 = factory::create<DerivedFromDerived2>(derived_from_derived2_init);

			saved.base_ptr4 = saved.base_ptr1;
			saved.base_ptr5 = nullptr;

			test_common_helpers::serialize(saved, filename);

			PointerTable<Base>::clear();

			Pointers loaded{};
			loaded.unserialize(xml::Doc::make_by_file(filename));

			auto base = std::dynamic_pointer_cast<Base>(loaded.base_ptr);
			auto derived1 = std::dynamic_pointer_cast<Derived1>(loaded.base_ptr1);
			auto derived2 = std::dynamic_pointer_cast<Derived2>(loaded.base_ptr2);
			auto derived_from_derived2 = std::dynamic_pointer_cast<DerivedFromDerived2>(loaded.base_ptr3);

			assert(base && *base == base_init);
			assert(derived1 && *derived1 == derived1_init);
			assert(derived2 && *derived2 == derived2_init);
			assert(derived_from_derived2 && *derived_from_derived2 == derived_from_derived2_init);

			assert(derived2->get_double_ptr() == derived_from_derived2->get_double_ptr());

			assert(loaded.base_ptr4 == loaded.base_ptr1);
			assert(loaded.base_ptr5 == nullptr);
		}

	} // namespace inheritance

} // namespace test
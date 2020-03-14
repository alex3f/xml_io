#include "main/pch.h"
#include "tests/classes/Ints.h"
#include "io/XmlIOStream.h"

namespace
{
	auto constexpr ints_typename ="Ints";

	auto unserialize_reference(char const *name, XmlDocNodePtr const &node)
	{
		auto constexpr undefined_id{9999};

		int id = undefined_id;

		io::XmlIOStream{node} >> IO_REFERENCE_OUTPUT(id, AS_TEXT(ref.value));

		return id;
	}

	auto find_in_test_range(int id)
	{
		return std::find_if(test::IntWithId::test_range.cbegin(), test::IntWithId::test_range.cend(),
								[id](auto const &i) { return i.id == id; });
	}

	void serialize_nested(char const *name, test::Ints const &var, XmlDocNodePtr const &node)
	{
		auto child = node->add_child(ints_typename, {{xml::attributes::var_name, name}});
		assert(child);
		var.serialize(child);
	}

	auto unserialize_nested(char const *name, XmlDocNodePtr const &node)
	{
		auto child = node->find_child(ints_typename, {xml::attributes::var_name, name});
		assert(child);
		return test::Ints::unserialize(child);
	}

} // namespace

namespace test
{
	IntWithId::TestRange const IntWithId::test_range{IntWithId{-1, 1}, IntWithId{-2, 2}, IntWithId{-3, 3}};

	bool IntWithId::operator==(IntWithId const &rhs) const
	{
		if (&rhs == this)
		{
			return true;
		}

		return (id == rhs.id) && (value == rhs.value);
	}

	Ints::Ints(IntWithId const &r, int v1, int v2, int v_for_ptr)
		: val_1(v1)
		, val_2(v2)
		, ptr(new int(v_for_ptr))
		, ref(r)
	{
	}

	Ints::Ints(Ints const &rhs)
		: val_1(rhs.val_1)
		, val_2(rhs.val_2)
		, ptr(new int((*rhs.ptr)))
		, ref(rhs.ref)
	{
	}

	Ints::~Ints()
	{
		delete ptr;
	}

	void Ints::serialize(XmlDocNodePtr const &node) const
	{
		io::XmlIOStream{node} << IO_CONSTANT(val_1)	<< IO_CONSTANT(val_2) << IO_CONSTANT(*ptr)
			<< IO_REFERENCE_INPUT(ref.value, ref.id);
	}

	bool Ints::unserialize(io::XmlIOStream const &stream)
	{
		stream >> IO_VARIABLE(val_1) >> IO_VARIABLE(val_2) >> IO_VARIABLE(*ptr);
		return true;
	}

	std::unique_ptr<Ints> Ints::unserialize(XmlDocNodePtr const &node)
	{
		int id = unserialize_reference(AS_TEXT(ref.value), node);

		auto it = find_in_test_range(id);

		if (it != test::IntWithId::test_range.cend())
		{
			auto loaded = std::make_unique<Ints>(*it);

			if (loaded->unserialize(io::XmlIOStream{node}))
			{
				return loaded;
			}
		}

		return nullptr;
	}

	bool Ints::operator==(Ints const &rhs) const
	{
		if (&rhs == this)
		{
			return true;
		}

		return (val_1 == rhs.val_1) && (val_2 == rhs.val_2) && (*ptr == *rhs.ptr) && (ref == (rhs.ref));
	}

	NestedInts::NestedInts(IntWithId const &r, Ints const &v, Ints const &p)
		: ref(r)
		, val(v)
		, ptr(new Ints(p))
	{
	}

	NestedInts::~NestedInts()
	{
		delete ptr;
	}

	void NestedInts::serialize(XmlDocNodePtr const &node) const
	{
		serialize_nested(AS_TEXT(val), val, node);
		serialize_nested(AS_TEXT(*ptr), *ptr, node);
		io::XmlIOStream{node} << IO_REFERENCE_INPUT(ref.value, ref.id);
	}

	std::unique_ptr<NestedInts> NestedInts::unserialize(XmlDocNodePtr const &node)
	{
		auto const v = unserialize_nested(AS_TEXT(val), node);
		auto const p = unserialize_nested(AS_TEXT(*ptr), node);

		auto const ref_id = unserialize_reference(AS_TEXT(ref.value), node);
		auto const r = find_in_test_range(ref_id);

		if (v && p && (r != test::IntWithId::test_range.cend()))
		{	
			return std::make_unique<NestedInts>(*r, *v, *p);		
		}

		return nullptr;
	}

} // namespace test

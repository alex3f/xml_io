#pragma once
#include "interfaces/XmlDocNode.h"

namespace io
{
	class XmlIOStream;
}

namespace test
{
	// Структура с id используется для проверки сериализации ссылок.
	struct IntWithId
	{
		using TestRange = std::array<IntWithId, 3>;
		static TestRange const test_range;

		int id{};
		int value{};

		bool operator==(IntWithId const &rhs) const;
	};

	struct Ints
	{
		Ints(IntWithId const &ref, int v1 = {}, int v2 = {}, int v_for_ptr = {});
		Ints(Ints const &rhs);
		~Ints();

		Ints &operator=(Ints const &) = delete;

		bool operator==(Ints const &rhs) const;

		void serialize(XmlDocNodePtr const &node) const;
		static std::unique_ptr<Ints> unserialize(XmlDocNodePtr const &node);

		int val_1{}, val_2{};
		int *ptr{}; 
		IntWithId const &ref;

	private:
		bool unserialize(io::XmlIOStream const &stream);
	};

	struct NestedInts
	{
		explicit NestedInts(IntWithId const &r, Ints const &v, Ints const &p);
		~NestedInts();

		IntWithId const &ref;
		Ints val;
		Ints* ptr{};

		void serialize(XmlDocNodePtr const &node) const;
		static std::unique_ptr<NestedInts> unserialize(XmlDocNodePtr const &node);
	};

	struct PointersToInts
	{
		ptr_t<int> p1{}, p2{}, p3{}, p4{};

		void serialize(XmlDocNodePtr const &node) const;
		void unserialize(XmlDocNodePtr const &node);
	};

} // namespace test
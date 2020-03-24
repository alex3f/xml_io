#pragma once
#include "interfaces/XmlDocNode.h"

namespace test
{
	namespace multiple_inheritance
	{
		class Base
		{
		public:
			virtual ~Base() = default;

			virtual void serialize(XmlDocNodePtr const &node) const;
			virtual bool unserialize(XmlDocNodePtr const &node);

		private:
			char ch{'b'};
		};

		class Derived1 : public Base
		{
		public:
			~Derived1() override = default;

			void serialize(XmlDocNodePtr const &node) const;
			bool unserialize(XmlDocNodePtr const &node);

		private:
			char ch{'d'};
		};

		using BasePtr = ptr_t<Base>;

		// TODO (опционально): добавить пример с массивом указателей

		struct Pointers
		{
			BasePtr base_ptr1{}, base_ptr2{};

			void serialize(XmlDocNodePtr const &node) const;
			void unserialize(XmlDocNodePtr const &node);
		};

	} // namespace multiple_inheritance

} // namespace test

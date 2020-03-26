#pragma once
#include "interfaces/XmlDocNode.h"

namespace test
{
	namespace multiple_inheritance
	{
		class Base
		{
		public:
			Base(char b = {});
			virtual ~Base() = default;

			bool operator==(Base const &rhs) const;

			virtual void serialize(XmlDocNodePtr const &node) const;
			virtual bool unserialize(XmlDocNodePtr const &node);

		private:
			char ch{};
		};

		class Derived1 : public Base
		{
		public:
			Derived1(char b = {}, char d = {}, int num = {});
			~Derived1() override = default;

			bool operator==(Derived1 const &rhs) const;

			void serialize(XmlDocNodePtr const &node) const override;
			bool unserialize(XmlDocNodePtr const &node) override;

		private:
			char ch{};
			int i{};
		};

		class Derived2 : public Base
		{
		public:
			Derived2(char b = {}, std::string const &s = {}, ptr_t<double> const &p = {});
			~Derived2() override = default;

			bool operator==(Derived2 const &rhs) const;

			void serialize(XmlDocNodePtr const &node) const override;
			bool unserialize(XmlDocNodePtr const &node) override;

			ptr_t<double> get_double_ptr() const { return ptr; }

		private:
			std::string str;
			ptr_t<double> ptr;
		};

		class DerivedFromDerived2 : public Derived2
		{
		public:
			DerivedFromDerived2(Derived2 const &d2 = {}, unsigned short u = {});
			~DerivedFromDerived2() override = default;

			bool operator==(DerivedFromDerived2 const &rhs) const;

			void serialize(XmlDocNodePtr const &node) const override;
			bool unserialize(XmlDocNodePtr const &node) override;

		private:
			unsigned short ush{};
		};

		using BasePtr = ptr_t<Base>;

		// TODO (опционально): добавить пример с массивом указателей

		struct Pointers
		{
			BasePtr base_ptr{}, base_ptr1{}, base_ptr2{}, base_ptr3{}, 
					base_ptr4{}, base_ptr5{};

			void serialize(XmlDocNodePtr const &node) const;
			void unserialize(XmlDocNodePtr const &node);
		};

	} // namespace multiple_inheritance

} // namespace test

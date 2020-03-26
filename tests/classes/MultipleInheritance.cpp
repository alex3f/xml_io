#include "main/pch.h"
#include "tests/classes/MultipleInheritance.h"
#include "utils/InheritanceGuards.h"
#include "io/XmlIOStream.h"

namespace
{
	auto create_double_ptr()
	{
		return factory::create<double>();
	}
}

namespace test
{
	namespace multiple_inheritance
	{
		#define MULTIPLE_INHERITANCE_IDENTITY(ClassName) \
				{AS_TEXT(ClassName), []()->ptr_t<test::multiple_inheritance::Base>{ return factory::create<ClassName>(); }}

		using BaseCreateFunc = ptr_t<test::multiple_inheritance::Base>(*)();

		BaseCreateFunc unserialize_identity(std::string const &identity)
		{
			static std::map<std::string, BaseCreateFunc> const identities
			{
				MULTIPLE_INHERITANCE_IDENTITY(Base),
				MULTIPLE_INHERITANCE_IDENTITY(Derived1),
				MULTIPLE_INHERITANCE_IDENTITY(Derived2),
				MULTIPLE_INHERITANCE_IDENTITY(DerivedFromDerived2),
			};

			auto it = identities.find(identity);

			assert((it != identities.cend()) && L"Неизвестный идентификатор класса");

			return (it != identities.cend()) ? it->second : nullptr;
		}

		#undef MULTIPLE_INHERITANCE_IDENTITY

		Base::Base(char b)
			: ch(b)
		{
		}

		bool Base::operator==(Base const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return ch == rhs.ch;
		}

		void Base::serialize(XmlDocNodePtr const &node) const
		{
			auto const guard = inheritance::IdentityGuard::get(AS_TEXT(Base), node);
			io::XmlIOStream{node} << IO_CONSTANT(ch);
		}

		bool Base::unserialize(XmlDocNodePtr const &node)
		{
			io::XmlIOStream{node} >> IO_VARIABLE(ch);
			return true;
		}

		Derived1::Derived1(char b, char d, int num)
			: Base(b)
			, ch(d)
			, i(num)
		{
		}

		bool Derived1::operator==(Derived1 const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return Base::operator==(rhs) && (ch == rhs.ch) && (i == rhs.i);
		}

		void Derived1::serialize(XmlDocNodePtr const &node) const
		{
			auto const guard = inheritance::IdentityGuard::get(AS_TEXT(Derived1), node);
			Base::serialize(node);
			io::XmlIOStream{node} 
				/*
					Имя переменной ch совпадает с именем переменной в базовом классе - 
					чтобы избежать неоднозначностей при чтении,
					можно использовать явное указание области видимости переменной.
				*/
				<< IO_CONSTANT(Derived1::ch) 
				<< IO_CONSTANT(i);
		}

		bool Derived1::unserialize(XmlDocNodePtr const &node)
		{
			Base::unserialize(node);
			io::XmlIOStream{node} >> IO_VARIABLE(Derived1::ch) >> IO_VARIABLE(i);
			return true;
		}

		Derived2::Derived2(char b, std::string const &s, ptr_t<double> const &p)
			: Base(b)
			, str(s)
			, ptr(p)
		{
		}

		bool Derived2::operator==(Derived2 const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			if ((!ptr && rhs.ptr) || (ptr && !rhs.ptr))
			{
				return false;
			}

			return Base::operator==(rhs) && (str == rhs.str) && 
					((!ptr && !rhs.ptr) || (is_equal(*ptr,*rhs.ptr)));
		}

		void Derived2::serialize(XmlDocNodePtr const &node) const
		{
			auto const guard = inheritance::IdentityGuard::get(AS_TEXT(Derived2), node);
			Base::serialize(node);
			io::XmlIOStream{node} << IO_CONSTANT(str) << IO_POINTER_INPUT(ptr);
		}

		bool Derived2::unserialize(XmlDocNodePtr const &node)
		{
			Base::unserialize(node);
			io::XmlIOStream{node} >> IO_VARIABLE(str) >> IO_POINTER_OUTPUT(ptr, create_double_ptr);
			return true;
		}

		DerivedFromDerived2::DerivedFromDerived2(Derived2 const &d2, unsigned short u)
			: Derived2(d2)
			, ush(u)
		{
		}

		bool DerivedFromDerived2::operator==(DerivedFromDerived2 const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return Derived2::operator==(rhs) && (ush == rhs.ush);
		}


		void DerivedFromDerived2::serialize(XmlDocNodePtr const &node) const
		{
			auto const guard = inheritance::IdentityGuard::get(AS_TEXT(DerivedFromDerived2), node);
			Derived2::serialize(node);
			io::XmlIOStream{node} << IO_CONSTANT(ush);
		}

		bool DerivedFromDerived2::unserialize(XmlDocNodePtr const &node)
		{
			Derived2::unserialize(node);
			io::XmlIOStream{node} >> IO_VARIABLE(ush);
			return true;
		}

		void Pointers::serialize(XmlDocNodePtr const &node) const
		{
			io::XmlIOStream{node} << IO_INHERITANCE_POINTER_INPUT(base_ptr)
				<< IO_INHERITANCE_POINTER_INPUT(base_ptr1) << IO_INHERITANCE_POINTER_INPUT(base_ptr2)
				<< IO_INHERITANCE_POINTER_INPUT(base_ptr3) << IO_INHERITANCE_POINTER_INPUT(base_ptr4)
				<< IO_INHERITANCE_POINTER_INPUT(base_ptr5);
		}

		void Pointers::unserialize(XmlDocNodePtr const &node)
		{
			io::XmlIOStream{node} >> IO_INHERITANCE_POINTER_OUTPUT(base_ptr, unserialize_identity)
				>> IO_INHERITANCE_POINTER_OUTPUT(base_ptr1, unserialize_identity)
				>> IO_INHERITANCE_POINTER_OUTPUT(base_ptr2, unserialize_identity)
				>> IO_INHERITANCE_POINTER_OUTPUT(base_ptr3, unserialize_identity)
				>> IO_INHERITANCE_POINTER_OUTPUT(base_ptr4, unserialize_identity)
				>> IO_INHERITANCE_POINTER_OUTPUT(base_ptr5, unserialize_identity);
		}


	} // namespace multiple_inheritance

} // namespace test
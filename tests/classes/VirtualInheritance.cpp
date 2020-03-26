#include "main/pch.h"
#include "tests/classes/VirtualInheritance.h"
#include "utils/InheritanceGuards.h"
#include "io/XmlIOStream.h"

namespace test
{
	namespace virtual_inheritance
	{
		#define VIRTUAL_INHERITANCE_IDENTITY(ClassName) \
				{AS_TEXT(ClassName), []()->ptr_t<test::virtual_inheritance::B>{ return factory::create<ClassName>(); }}

		using BaseCreateFunc = ptr_t<test::virtual_inheritance::B>(*)();

		BaseCreateFunc unserialize_identity(std::string const &identity)
		{
			static std::map<std::string, BaseCreateFunc> const identities
			{
				VIRTUAL_INHERITANCE_IDENTITY(B),
				VIRTUAL_INHERITANCE_IDENTITY(D1),
				VIRTUAL_INHERITANCE_IDENTITY(D2),
				VIRTUAL_INHERITANCE_IDENTITY(Join),
				VIRTUAL_INHERITANCE_IDENTITY(JoinD1),
				VIRTUAL_INHERITANCE_IDENTITY(JoinD2),
				VIRTUAL_INHERITANCE_IDENTITY(JoinJoin),
			};

			auto it = identities.find(identity);

			assert((it != identities.cend()) && L"Неизвестный идентификатор класса");

			return (it != identities.cend()) ? it->second : nullptr;
		}

		#undef VIRTUAL_INHERITANCE_IDENTITY

		bool B::operator==(B const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return b == rhs.b;
		}

		void B::serialize(XmlDocNodePtr const &node) const
		{
			auto const guard = inheritance::IdentityGuard::get(AS_TEXT(B), node);
			io::XmlIOStream{node} << IO_CONSTANT(b);
		}

		bool B::unserialize(XmlDocNodePtr const &node)
		{
			io::XmlIOStream{node} >> IO_VARIABLE(b);
			return true;
		}

		inheritance::VirtualGuard<B> B::get_virtual_guard(XmlDocNodePtr const &node) const
		{
			return inheritance::VirtualGuard<B>([this, &node]{ return this->B::serialize(node); });
		}

		bool D1::operator==(D1 const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return B::operator==(rhs) && (d1 == rhs.d1);
		}

		void D1::serialize(XmlDocNodePtr const &node) const
		{
			auto const identity_guard = inheritance::IdentityGuard::get(AS_TEXT(D1), node);
			auto const virtual_guard = B::get_virtual_guard(node);	
			io::XmlIOStream{node} << IO_CONSTANT(d1);
		}

		bool D1::unserialize(XmlDocNodePtr const &node)
		{
			B::unserialize(node);
			io::XmlIOStream{node} >> IO_VARIABLE(d1);
			return true;
		}

		bool D2::operator==(D2 const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return B::operator==(rhs) && (d2 == rhs.d2);
		}

		void D2::serialize(XmlDocNodePtr const &node) const
		{
			auto const identity_guard = inheritance::IdentityGuard::get(AS_TEXT(D2), node);
			auto const virtual_guard = B::get_virtual_guard(node);
			io::XmlIOStream{node} << IO_CONSTANT(d2);
		}

		bool D2::unserialize(XmlDocNodePtr const &node)
		{
			B::unserialize(node);
			io::XmlIOStream{node} >> IO_VARIABLE(d2);
			return true;
		}

		bool Join::operator==(Join const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return D1::operator==(rhs) && D2::operator==(rhs) && (join == rhs.join);
		}

		void Join::serialize(XmlDocNodePtr const &node) const
		{
			auto const identity_guard = inheritance::IdentityGuard::get(AS_TEXT(Join), node);
			auto const virtual_guard = B::get_virtual_guard(node);

			D1::serialize(node);
			D2::serialize(node);

			io::XmlIOStream{node} << IO_CONSTANT(join);
		}

		bool Join::unserialize(XmlDocNodePtr const &node)
		{
			D1::unserialize(node);
			D2::unserialize(node);
			io::XmlIOStream{node} >> IO_VARIABLE(join);
			return true;
		}

		inheritance::VirtualGuard<Join> Join::get_virtual_guard(XmlDocNodePtr const &node) const
		{
			return inheritance::VirtualGuard<Join>([this, &node]{ return this->Join::serialize(node); });
		}

		bool JoinD1::operator==(JoinD1 const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return Join::operator==(rhs) && (jd1 == rhs.jd1);
		}

		void JoinD1::serialize(XmlDocNodePtr const &node) const
		{
			auto const identity_guard = inheritance::IdentityGuard::get(AS_TEXT(JoinD1), node);
			auto const virtual_guard = Join::get_virtual_guard(node);
			io::XmlIOStream{node} << IO_CONSTANT(jd1);
		}

		bool JoinD1::unserialize(XmlDocNodePtr const &node)
		{
			B::unserialize(node);
			io::XmlIOStream{node} >> IO_VARIABLE(jd1);
			return true;
		}

		bool JoinD2::operator==(JoinD2 const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return Join::operator==(rhs) && (jd2 == rhs.jd2);
		}

		void JoinD2::serialize(XmlDocNodePtr const &node) const
		{
			auto const identity_guard = inheritance::IdentityGuard::get(AS_TEXT(JoinD2), node);
			auto const virtual_guard = Join::get_virtual_guard(node);
			io::XmlIOStream{node} << IO_CONSTANT(jd2);
		}

		bool JoinD2::unserialize(XmlDocNodePtr const &node)
		{
			B::unserialize(node);
			io::XmlIOStream{node} >> IO_VARIABLE(jd2);
			return true;
		}

		bool JoinJoin::operator==(JoinJoin const &rhs) const
		{
			if (&rhs == this)
			{
				return true;
			}

			return JoinD1::operator==(rhs) && JoinD2::operator==(rhs) && (jjoin == rhs.jjoin);
		}

		void JoinJoin::serialize(XmlDocNodePtr const &node) const
		{
			auto const identity_guard = inheritance::IdentityGuard::get(AS_TEXT(JoinJoin), node);
			auto const virtual_guard = Join::get_virtual_guard(node);

			JoinD1::serialize(node);
			JoinD2::serialize(node);

			io::XmlIOStream{node} << IO_CONSTANT(jjoin);
		}

		bool JoinJoin::unserialize(XmlDocNodePtr const &node)
		{
			JoinD1::unserialize(node);
			JoinD2::unserialize(node);
			io::XmlIOStream{node} >> IO_VARIABLE(jjoin);
			return true;
		}

		void Pointers::serialize(XmlDocNodePtr const &node) const
		{
			io::XmlIOStream{node} << IO_INHERITANCE_POINTER_INPUT(b_ptr1)
				<< IO_INHERITANCE_POINTER_INPUT(b_ptr2)
				<< IO_INHERITANCE_POINTER_INPUT(b_ptr3)
				<< IO_INHERITANCE_POINTER_INPUT(b_ptr4);
		}

		void Pointers::unserialize(XmlDocNodePtr const &node)
		{
			io::XmlIOStream{node} >> IO_INHERITANCE_POINTER_OUTPUT(b_ptr1, unserialize_identity)
				>> IO_INHERITANCE_POINTER_OUTPUT(b_ptr2, unserialize_identity)
				>> IO_INHERITANCE_POINTER_OUTPUT(b_ptr3, unserialize_identity)
				>> IO_INHERITANCE_POINTER_OUTPUT(b_ptr4, unserialize_identity);
		}

	} // namespace virtual_inheritance

} // namespace test

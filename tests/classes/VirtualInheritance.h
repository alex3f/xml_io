#pragma once
#include "interfaces/XmlDocNode.h"

namespace inheritance
{
	template<typename VirtualInheritanceBase>
	class VirtualGuard;
}

namespace test
{
	namespace virtual_inheritance
	{
		struct B
		{
			B(int i = {}) : b(i) {}
			virtual ~B() = default;

			bool operator==(B const &rhs) const;

			virtual void serialize(XmlDocNodePtr const &node) const;
			virtual bool unserialize(XmlDocNodePtr const &node);

			int b{};

		protected:
			inheritance::VirtualGuard<B> get_virtual_guard(XmlDocNodePtr const &node) const;
		};

		struct D1 : public virtual B
		{
			D1(int i = {}, int d = {}) : B(i), d1(d) {}
			~D1() override = default;

			bool operator==(D1 const &rhs) const;

			void serialize(XmlDocNodePtr const &node) const override;
			bool unserialize(XmlDocNodePtr const &node) override;

			int d1{};
		};

		struct D2 : public virtual B
		{
			D2(int i = {}, int d = {}) : B(i), d2(d) {}
			~D2() override = default;

			bool operator==(D2 const &rhs) const;

			void serialize(XmlDocNodePtr const &node) const override;
			bool unserialize(XmlDocNodePtr const &node) override;

			int d2{};
		};

		struct Join : public D1, public D2
		{
			Join(int i = {}, int d1 = {}, int d2 = {}, int j = {}) 
				: B(i), D1(i, d1), D2(i, d2), join(j) 
			{
			}
			~Join() override = default;

			bool operator==(Join const &rhs) const;

			void serialize(XmlDocNodePtr const &node) const override;
			bool unserialize(XmlDocNodePtr const &node) override;

			int join{};

		protected:
			inheritance::VirtualGuard<Join> get_virtual_guard(XmlDocNodePtr const &node) const;
		};

		struct JoinD1 : public virtual Join
		{
			JoinD1(Join const &j = {}, int d = {}) : Join(j), jd1(d) {}
			~JoinD1() override = default;

			bool operator==(JoinD1 const &rhs) const;

			void serialize(XmlDocNodePtr const &node) const override;
			bool unserialize(XmlDocNodePtr const &node) override;

			int jd1{};
		};

		struct JoinD2 : public virtual Join
		{
			JoinD2(Join const &j = {}, int d = {}) : Join(j), jd2(d) {}
			~JoinD2() override = default;

			bool operator==(JoinD2 const &rhs) const;

			void serialize(XmlDocNodePtr const &node) const override;
			bool unserialize(XmlDocNodePtr const &node) override;

			int jd2{};
		};

		struct JoinJoin : public JoinD1, public JoinD2
		{
			JoinJoin(Join const &j = {}, int d1 = {}, int d2 = {}, int jj = {})
				: Join(j), JoinD1(j, d1), JoinD2(j, d2), jjoin(jj)
			{
			}
			~JoinJoin() override = default;

			bool operator==(JoinJoin const &rhs) const;

			void serialize(XmlDocNodePtr const &node) const override;
			bool unserialize(XmlDocNodePtr const &node) override;

			int jjoin{};
		};

		struct Pointers
		{
			ptr_t<B> b_ptr1{}, b_ptr2{}, b_ptr3{}, b_ptr4{};

			void serialize(XmlDocNodePtr const &node) const;
			void unserialize(XmlDocNodePtr const &node);
		};

	} // namespace virtual_inheritance

} // namespace test

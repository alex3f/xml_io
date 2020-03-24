#pragma once
#include "io/IOTypes.h"
#include "io/IOTraitFunctions.h"
#include "interfaces/XmlDocNode.h"
#include "xml/XmlAttributes.h"
#include "utils/PointerTable.h"

namespace io
{
	class XmlIOStream
	{
	public:
		XmlIOStream(XmlDocNodePtr const &node) : m_node(node) {}

		template<typename T>
		XmlIOStream& operator<<(Constant<T> const &c);

		template<typename T, typename BaseObjId>
		XmlIOStream& operator<<(ReferenceInput<T, BaseObjId> const &r);

		template<typename T>
		XmlIOStream& operator<<(PointerInput<T> const &p);

		template<typename T>
		XmlIOStream const& operator>>(Variable<T> const &v) const;

		template<typename BaseObjId>
		XmlIOStream const& operator>>(ReferenceOutput<BaseObjId> const &r) const;

		template<typename T, typename CreateFunc>
		XmlIOStream const& operator>>(PointerOutput<T, CreateFunc> const &p) const;

	private:
		template<typename T>
		static auto get_ptr_name()
		{
			std::string ptr_name(io::trait_functions<T>::name());
			return ptr_name.append("_ptr");
		}

		XmlDocNodePtr m_node;
	};

	template<typename T>
	XmlIOStream& XmlIOStream::operator<<(Constant<T> const &c)
	{
		if (auto child_node = m_node->add_child(io::trait_functions<T>::name(), {{xml::attributes::var_name, c.name}}))
		{
			io::trait_functions<T>::serialize(c.value, child_node);
		}

		return *this;
	}

	template<typename T, typename BaseObjId>
	XmlIOStream& XmlIOStream::operator<<(ReferenceInput<T, BaseObjId> const &r)
	{
		if (auto ref_node = m_node->add_child(io::trait_functions<T>::name(), {{xml::attributes::var_name, r.ref_name}}))
		{
			if (auto base_obj_id_node = ref_node->add_child(io::trait_functions<BaseObjId>::name()))
			{
				io::trait_functions<BaseObjId>::serialize(r.base_obj_id, base_obj_id_node);
			}
		}

		return *this;
	}

	template<typename T>
	XmlIOStream& XmlIOStream::operator<<(PointerInput<T> const &p)
	{
		if (auto ptr_node = m_node->add_child(get_ptr_name<T>(),
											  {{xml::attributes::var_name, p.name},
												{xml::attributes::ptr_id, PointerTable<T>::get_pointer_id(p.ptr)}}))
		{
			if (p.ptr)
			{
				io::trait_functions<T>::serialize(*(p.ptr), ptr_node);
			}
		}

		return *this;
	}

	template<typename T>
	XmlIOStream const& XmlIOStream::operator>>(Variable<T> const &v) const
	{
		if (auto child_node = m_node->find_child(io::trait_functions<T>::name(), {xml::attributes::var_name, v.name}))
		{
			io::trait_functions<T>::unserialize(v.value, child_node);
		}

		return *this;
	}

	template<typename BaseObjId>
	XmlIOStream const& XmlIOStream::operator>>(ReferenceOutput<BaseObjId> const &r) const
	{
		if (auto ref_node = m_node->find_child({xml::attributes::var_name, r.ref_name}))
		{
			if (auto base_obj_id_node = ref_node->find_child(io::trait_functions<BaseObjId>::name()))
			{
				io::trait_functions<BaseObjId>::unserialize(r.base_obj_id, base_obj_id_node);
			}
		}

		return *this;
	}

	template<typename T, typename CreateFunc>
	XmlIOStream const& XmlIOStream::operator>>(PointerOutput<T, CreateFunc> const &p) const
	{
		if (auto ptr_node = m_node->find_child(get_ptr_name<T>(), {xml::attributes::var_name, p.name}))
		{
			auto const id = ptr_node->get_attribute_value(xml::attributes::ptr_id);

			p.ptr = PointerTable<T>::get_pointer_by_id(id, p.create_func);

			if (p.ptr)
			{
				io::trait_functions<T>::unserialize(*(p.ptr), ptr_node);
			}
		}

		return *this;
	}

} // namespace io
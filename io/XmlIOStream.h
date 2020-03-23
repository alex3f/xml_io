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
		XmlIOStream const& operator>>(Variable<T> const &v) const;

		template<typename BaseObjId>
		XmlIOStream const& operator>>(ReferenceOutput<BaseObjId> const &r) const;

	private:
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

} // namespace io
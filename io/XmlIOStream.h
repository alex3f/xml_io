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
		XmlIOStream& operator<<(InheritancePointerInput<T> const &p);

		template<typename Coll>
		XmlIOStream& operator<<(CollectionInput<Coll> const &c);

		template<typename T>
		XmlIOStream const& operator>>(Variable<T> const &v) const;

		template<typename BaseObjId>
		XmlIOStream const& operator>>(ReferenceOutput<BaseObjId> const &r) const;

		template<typename T, typename CreateFunc>
		XmlIOStream const& operator>>(PointerOutput<T, CreateFunc> const &p) const;

		template<typename T, typename CreateByIdentityFunc>
		XmlIOStream const& operator>>(InheritancePointerOutput<T, CreateByIdentityFunc> const &p) const;

		template<typename Coll, typename InsertItemFunc>
		XmlIOStream const& operator>>(CollectionOutput<Coll, InsertItemFunc> const &c) const;

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
	XmlIOStream& XmlIOStream::operator<<(InheritancePointerInput<T> const &p)
	{
		return operator<<(PointerInput<T>{p.name, p.ptr});
	}

	template<typename Coll>
	XmlIOStream& XmlIOStream::operator<<(CollectionInput<Coll> const &c)
	{
		using CollValueType = typename Coll::value_type;

		if (auto coll_node = m_node->add_child(io::collection_trait_functions<Coll>::name(), 
											   {{xml::attributes::var_name, c.name}, 
											    {xml::attributes::value_type, 
													io::trait_functions<CollValueType>::name()},
												{xml::attributes::items_count, std::to_string(c.coll.size())}}))
		{
			int index{0};

			for (auto const &coll_item : c.coll)
			{
				if (auto coll_item_node = coll_node->add_child(io::trait_functions<CollValueType>::name(), 
															   {{xml::attributes::index, std::to_string(index++)}}))
				{
					io::trait_functions<CollValueType>::serialize(coll_item, coll_item_node);
				}
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

	template<typename T, typename CreateByIdentityFunc>
	XmlIOStream const& XmlIOStream::operator>>(InheritancePointerOutput<T, CreateByIdentityFunc> const &p) const
	{
		if (auto ptr_node = m_node->find_child(get_ptr_name<T>(), {xml::attributes::var_name, p.name}))
		{
			auto const identity = ptr_node->get_attribute_value(xml::attributes::ptr_identity);

			if (!identity.empty())
			{
				auto create_func = p.create_func_by_identity(identity);
				assert(create_func);
				if (create_func)
				{
					return operator>>(PointerOutput<T, decltype(create_func)>{p.name, p.ptr, create_func});
				}
			}		
		}

		return *this;
	}

	template<typename Coll, typename InsertItemFunc>
	XmlIOStream const& XmlIOStream::operator>>(CollectionOutput<Coll, InsertItemFunc> const &c) const
	{
		using CollValueType = typename Coll::value_type;

		if (auto coll_node = m_node->find_child(io::collection_trait_functions<Coll>::name(), 
												{xml::attributes::var_name, c.name}))
		{
			auto const count = std::stoi(coll_node->get_attribute_value(xml::attributes::items_count));
			auto const value_type_name = coll_node->get_attribute_value(xml::attributes::value_type);
			assert(count >= 0 && !value_type_name.empty());

			CollValueType tmp{};

			for (int i = 0; i < count; ++i)
			{
				if (auto coll_value_node = coll_node->find_child(value_type_name, 
																{xml::attributes::index, std::to_string(i)}))
				{
					io::trait_functions<CollValueType>::unserialize(tmp, coll_value_node);
					c.insert_item_func(c.coll, tmp);
				}
			}

		}

		return *this;
	}

} // namespace io
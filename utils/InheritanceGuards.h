#pragma once
#include "interfaces/XmlDocNode.h"
#include "xml/XmlAttributes.h"

namespace inheritance
{
	template<typename Tag>
	class NestedObjectsCounter
	{
	public:
		virtual ~NestedObjectsCounter() { --objects_count; }

	protected:
		NestedObjectsCounter() { ++objects_count; }

		int get_objects_count() const { return objects_count; }

	private:
		static int objects_count;
	};

	template<typename Tag>
	int NestedObjectsCounter<Tag>::objects_count = 0;

	struct IdentityTag {};

	/*
		Выполняет сериализацию признака класса для первого объекта из цепочки вложенных объектов.
	*/
	class IdentityGuard : public NestedObjectsCounter<IdentityTag>
	{
	public:
		static IdentityGuard get(std::string const &identity, XmlDocNodePtr const &node) 
		{ 
			return IdentityGuard(identity, node); 
		}

	private:
		IdentityGuard(std::string const &identity, XmlDocNodePtr const &node)
		{
			if (get_objects_count() == 1)
			{
				node->add_attributes({{xml::attributes::ptr_identity, identity}});
			}
		}
	};

	/*
		Выполняет функцию сериализации для первого объекта из цепочки вложенных объектов.
	*/
	template<typename VirtualInheritanceBase>
	class VirtualGuard : public NestedObjectsCounter<VirtualInheritanceBase>
	{
	public:
		VirtualGuard(std::function<void()> serialization_func) 
		{ 
			if (NestedObjectsCounter<VirtualInheritanceBase>::get_objects_count() == 1)
			{
				serialization_func();
			}
		}
	};

} // namespace inheritance
#pragma once
#include "interfaces/XmlDocNode.h"
#include "xml/XmlAttributes.h"

namespace inheritance
{
	struct IdentityTag {};
	struct VirtualInheritanceTag {}; // NOTE: будет использовано для виртуального наследования.

	template<typename Tag, std::enable_if_t<std::is_same<Tag, IdentityTag>::value ||
											std::is_same<Tag, VirtualInheritanceTag>::value, int> = 0>
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

	int NestedObjectsCounter<IdentityTag>::objects_count = 0;
	int NestedObjectsCounter<VirtualInheritanceTag>::objects_count = 0;

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

} // namespace inheritance
#include "main/pch.h"
#include "interfaces/impl/PugiXmlDocNode.h"

namespace
{
	void append_attributes(pugi::xml_node node, IXmlDocNode::Attributes const &attributes)
	{
		if (!node)
		{
			return;
		}

		for (auto const &attr : attributes)
		{
			node.append_attribute(attr.name.data()).set_value(attr.value.data());
		}
	}

} // namespace


XmlDocNodePtr PugiXmlDocNode::get(pugi::xml_node node)
{
	return std::make_shared<PugiXmlDocNode>(std::move(node));
}

PugiXmlDocNode::PugiXmlDocNode(pugi::xml_node node)
	: m_node(std::move(node))
{
}

XmlDocNodePtr PugiXmlDocNode::add_child(std::string const &name, Attributes const &attributes)
{
	auto child_node = m_node.append_child(name.data());
	append_attributes(child_node, attributes);
	return PugiXmlDocNode::get(std::move(child_node));
}

XmlDocNodePtr PugiXmlDocNode::find_child(std::string const &name, Attribute const &attribute) const
{
	auto child_node = m_node.find_child_by_attribute(name.data(), attribute.name.data(), attribute.value.data());
	return child_node ? PugiXmlDocNode::get(std::move(child_node)) : nullptr;
}

XmlDocNodePtr PugiXmlDocNode::find_child(std::string const &name) const
{
	auto child_node = m_node.find_child([&name](auto const &node) { return std::string(node.name()) == name; });
	return child_node ? PugiXmlDocNode::get(std::move(child_node)) : nullptr;
}

XmlDocNodePtr PugiXmlDocNode::find_child(Attribute const &attribute) const
{
	auto child_node = m_node.find_child_by_attribute(attribute.name.data(), attribute.value.data());
	return child_node ? PugiXmlDocNode::get(std::move(child_node)) : nullptr;
}

void PugiXmlDocNode::set_value(std::string const &value)
{
	auto value_node = m_node.append_child(pugi::xml_node_type::node_pcdata);
	value_node.set_value(value.data());
}

std::string PugiXmlDocNode::get_value() const
{
	return m_node.child_value();
}

std::string PugiXmlDocNode::get_attribute_value(std::string const &attr_name) const
{
	auto attr = m_node.find_attribute([&attr_name](auto const &attr){ return std::string(attr.name()) == attr_name; });
	return attr ? attr.value() : "";
}

#pragma once
#include "interfaces/XmlDocNode.h"
#include "utils/pugixml/pugixml.hpp"

class PugiXmlDocNode : public IXmlDocNode
{
public:
	static XmlDocNodePtr get(pugi::xml_node node);

	PugiXmlDocNode(pugi::xml_node node);
	~PugiXmlDocNode() override = default;

	XmlDocNodePtr add_child(std::string const &name, Attributes const &attributes = {}) override;

	XmlDocNodePtr find_child(std::string const &name, Attribute const &attribute) const override;

	XmlDocNodePtr find_child(std::string const &name) const override;

	XmlDocNodePtr find_child(Attribute const &attribute) const override;

	void set_value(std::string const &value) override;
	std::string get_value() const override;

	void add_attributes(Attributes const &attributes) const;
	std::string get_attribute_value(std::string const &attribute_name) const override;

private:
	pugi::xml_node m_node;
};
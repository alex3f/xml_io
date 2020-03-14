#pragma once
#include "interfaces/XmlDoc.h"
#include "utils/pugixml/pugixml.hpp"

class PugiXmlDoc : public IXmlDoc
{
public:
	PugiXmlDoc();
	~PugiXmlDoc() override = default;

	void save_to_file(std::string const &filename) const override;
	bool load_from_file(std::string const &filename) override;

	XmlDocNodePtr add_child(std::string const &name, Attributes const &attributes = {}) override;

	XmlDocNodePtr find_child(std::string const &name, Attribute const &attribute) const override;
	XmlDocNodePtr find_child(std::string const &name) const override;
	XmlDocNodePtr find_child(Attribute const &attribute) const override;

	void set_value(std::string const &value) override;
	std::string get_value() const override;

private:
	pugi::xml_document m_doc;
};
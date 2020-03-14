#include "main/pch.h"
#include "interfaces/impl/PugiXmlDoc.h"
#include "interfaces/impl/PugiXmlDocNode.h"

PugiXmlDoc::PugiXmlDoc()
	: m_doc(pugi::xml_document())
{
}

void PugiXmlDoc::save_to_file(std::string const &filename) const
{
	m_doc.save_file(filename.data());
}

bool PugiXmlDoc::load_from_file(std::string const &filename)
{
	auto const parse_status = m_doc.load_file(filename.data()).status;

	// status_no_document_element - считаем документ без элементов валидным, 
	// но на данный кейс стоит особое внимание.
	assert(parse_status != pugi::xml_parse_status::status_no_document_element &&
			L"Обратить внимание: документ без элементов");

	return (parse_status == pugi::xml_parse_status::status_ok) || 
			(parse_status == pugi::xml_parse_status::status_no_document_element);
}

XmlDocNodePtr PugiXmlDoc::add_child(std::string const &name, Attributes const &attributes)
{
	return PugiXmlDocNode(m_doc).add_child(name, attributes);
}

XmlDocNodePtr PugiXmlDoc::find_child(std::string const &name, Attribute const &attribute) const
{
	return PugiXmlDocNode(m_doc).find_child(name, attribute);
}

XmlDocNodePtr PugiXmlDoc::find_child(std::string const &name) const
{
	return PugiXmlDocNode(m_doc).find_child(name);
}

XmlDocNodePtr PugiXmlDoc::find_child(Attribute const &attribute) const
{
	return PugiXmlDocNode(m_doc).find_child(attribute);
}

void PugiXmlDoc::set_value(std::string const &value)
{
	PugiXmlDocNode(m_doc).set_value(value);
}

std::string PugiXmlDoc::get_value() const
{
	return PugiXmlDocNode(m_doc).get_value();
}

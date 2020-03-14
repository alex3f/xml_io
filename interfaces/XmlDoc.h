#pragma once

#include "interfaces/XmlDocNode.h"

class IXmlDoc : public IXmlDocNode
{
public:
	virtual ~IXmlDoc() = default;

	virtual void save_to_file(std::string const &filename) const = 0;
	virtual bool load_from_file(std::string const &filename) = 0;
};

using XmlDocPtr = std::shared_ptr<IXmlDoc>;
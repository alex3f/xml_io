#include "main/pch.h"
#include "xml/XmlDoc.h"
#include "interfaces/impl/PugiXmlDoc.h"

namespace xml
{
	XmlDocPtr Doc::make_empty()
	{
		return std::make_shared<PugiXmlDoc>();
	}

	XmlDocPtr Doc::make_by_file(std::string const &filename)
	{
		auto doc = Doc::make_empty();
		
		if (doc && doc->load_from_file(filename))
		{
			return doc;
		}

		assert(false && "document load error");
		return nullptr;
	}

} // namespace xml
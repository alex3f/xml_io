#pragma once
#include"interfaces/XmlDoc.h"

namespace xml
{
	struct Doc
	{
		static XmlDocPtr make_empty();
		static XmlDocPtr make_by_file(std::string const &filename);
	};

} // namespace xml

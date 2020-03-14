#pragma once

class IXmlDocNode;
using XmlDocNodePtr = std::shared_ptr<IXmlDocNode>;

class IXmlDocNode
{
public:
	virtual ~IXmlDocNode() = default;

	struct Attribute
	{
		std::string name;
		std::string value;
	};

	using Attributes = std::vector<Attribute>;

	virtual XmlDocNodePtr add_child(std::string const &name, Attributes const &attributes = {}) = 0;

	virtual XmlDocNodePtr find_child(std::string const &name, Attribute const &attribute) const = 0;
	virtual XmlDocNodePtr find_child(std::string const &name) const = 0;
	virtual XmlDocNodePtr find_child(Attribute const &attribute) const = 0;

	virtual void set_value(std::string const &value) = 0;
	virtual std::string get_value() const = 0;
};

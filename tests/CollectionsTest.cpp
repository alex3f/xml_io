#include "main/pch.h"
#include "tests/SerializationTests.h"
#include "io/XmlIOStream.h"

namespace serialization_tests
{
	struct IntColl
	{
		IntColl(std::vector<int> const &i = {}) : ints(i) {}

		std::vector<int> ints;

		void serialize(XmlDocNodePtr const &node) const
		{
			io::XmlIOStream{node} << IO_COLLECTION_INPUT(ints);
		}

		bool unserialize(XmlDocNodePtr const &node)
		{
			io::XmlIOStream{node} >> IO_COLLECTION_OUTPUT(ints, [](auto &coll, auto const &item){ coll.push_back(item); });
			return true;
		}
	};

	void collection()
	{
		std::string const filename("results/collections_serialization.xml");

		IntColl saved{{1, 3, 5, -1, 0}};

		test_common_helpers::serialize(saved, filename);

		IntColl loaded{};
		loaded.unserialize(xml::Doc::make_by_file(filename));

		assert(loaded.ints == saved.ints);
	}

} // namespace serialization_tests

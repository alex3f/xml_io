#include "main/pch.h"
#include "tests/classes/Arithmetic.h"
#include "io/XmlIOStream.h"

namespace test
{
	bool ArithmeticTypes::operator==(ArithmeticTypes const &rhs) const
	{
		if (&rhs == this)
		{
			return true;
		}

		return (ch == rhs.ch) && (sh == rhs.sh) && (uns == rhs.uns) && (i == rhs.i) && 
				is_equal(f, rhs.f) && is_equal(d, rhs.d);
	}

	void ArithmeticTypes::serialize(XmlDocNodePtr const &node) const
	{
		io::XmlIOStream{node} << IO_CONSTANT(ch) << IO_CONSTANT(sh) << IO_CONSTANT(uns)
			<< IO_CONSTANT(i) << IO_CONSTANT(f) << IO_CONSTANT(d);
	}

	bool ArithmeticTypes::unserialize(XmlDocNodePtr const &node)
	{
		io::XmlIOStream{node} >> IO_VARIABLE(ch) >> IO_VARIABLE(sh) >> IO_VARIABLE(uns)
			>> IO_VARIABLE(i) >> IO_VARIABLE(f) >> IO_VARIABLE(d);
		return true;
	}

} // namespace test
#pragma once

namespace
{
	using PointerId = std::string;

	auto constexpr nullptr_id = "nullptr";

	template<typename T>
	PointerId generate_id(ptr_t<T> const &p)
	{
		if (!p)
		{
			return nullptr_id;
		}

		std::stringstream s;
		s << std::addressof(*p);
		return s.str();
	}

} // namespace

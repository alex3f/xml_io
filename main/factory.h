#pragma once

// [23.03.2020] NOTE: для корректной работы с сериализацией указателей
// необходимо работать с типами/фабричным методом, представленными ниже.

template<typename T>
using ptr_t = std::shared_ptr<T>;

template<typename T>
using wptr_t = std::weak_ptr<T>;

namespace factory
{
	template<typename T, typename... Args>
	auto create(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

} // namespace factory
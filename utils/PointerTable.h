#pragma once
#include "utils/PointerIdGenerator.h"

template<typename T>
class PointerTable
{
public:
	static PointerId get_pointer_id(ptr_t<T> const &ptr);

	// Функция пытается найти в таблице указатель по id. Если указатель не найден,
	// то с помощью create_func будет создан новый указатель, которому будет присвоен идентификатор id.
	template<typename CreateFunc>
	static ptr_t<T> get_pointer_by_id(PointerId const &id, CreateFunc create_func);

	static void clear() { get_table().m_pointers.clear(); }

private:
	static PointerTable& get_table();

	PointerTable() = default;

	using Pointers = std::map<PointerId, wptr_t<T>>;
	using PointersIterator = typename PointerTable<T>::Pointers::const_iterator;

	PointersIterator find(ptr_t<T> const &ptr) const;
	PointersIterator emplace(PointerId const &id, ptr_t<T> const &ptr);

	void remove_expired_pointers();

	Pointers m_pointers;
};

/**/

template<typename T>
PointerTable<T>& PointerTable<T>::get_table()
{
	static PointerTable<T> table;
	table.remove_expired_pointers();
	return table;
}

template<typename T>
PointerId PointerTable<T>::get_pointer_id(ptr_t<T> const &ptr)
{
	if (!ptr)
	{
		return nullptr_id;
	}

	auto& table = get_table();

	auto it = table.find(ptr);

	if (it == table.m_pointers.cend())
	{
		it = table.emplace(generate_id(ptr), ptr);
	}

	return it->first;
}

template<typename T>
template<typename CreateFunc>
ptr_t<T> PointerTable<T>::get_pointer_by_id(PointerId const &id, CreateFunc create_func)
{
	if (id.empty())
	{
		assert(false && L"Ошибка: попытка получить указатель по пустому id");
		return nullptr;
	}

	if (id == nullptr_id)
	{
		return nullptr;
	}

	auto& table = get_table();

	auto it = table.m_pointers.find(id);

	ptr_t<T> ptr{};

	if (it != table.m_pointers.cend())
	{
		ptr = it->second.lock();
		assert(ptr);
	}
	else
	{
		ptr = create_func();
		assert(ptr && L"Был создан нулевой указатель");

		if (ptr)
		{
			table.emplace(id, ptr);
		}
	}

	return ptr;
}

template<typename T>
typename PointerTable<T>::PointersIterator PointerTable<T>::find(ptr_t<T> const &ptr) const
{
	assert(ptr && L"Ошибка: попытка найти нулевой указатель в таблице");

	return std::find_if(m_pointers.cbegin(), m_pointers.cend(), [&ptr](auto const &pair)
	{
		auto ptr_in_table = pair.second;
		assert(!ptr_in_table.expired() && L"Expired-указатели должны быть удалены при вызове get_table");
		return ptr_in_table.lock() == ptr;
	});
}

template<typename T>
typename PointerTable<T>::PointersIterator PointerTable<T>::emplace(PointerId const &id, ptr_t<T> const &ptr)
{
	assert(ptr && L"Ошибка: попытка добавить нулевой указатель в таблицу");
	assert((id != nullptr_id) && L"Ошибка: попытка присвоить nullptr_id ненулевому указателю");

	auto pair = m_pointers.emplace(id, ptr);
	assert(pair.second && L"Указатель не был добавлен в таблицу");
	return pair.first;
}

template<typename T>
void PointerTable<T>::remove_expired_pointers()
{
	for (auto it = m_pointers.begin(); it != m_pointers.end(); )
	{
		(it->second.expired()) ? it = m_pointers.erase(it) : ++it;
	}
}

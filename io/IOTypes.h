#pragma once

namespace io
{
	template<typename T>
	struct Constant
	{
		std::string name;
		T const &value;
	};

	template<typename T>
	struct Variable
	{
		std::string name;
		T &value;
	};

	template<typename BaseObj, typename BaseObjId>
	struct ReferenceInput
	{
		std::string ref_name;
		BaseObjId const &base_obj_id;
	};

	template<typename BaseObjId>
	struct ReferenceOutput
	{
		BaseObjId &base_obj_id;
		std::string ref_name;
	};

	template<typename T>
	struct PointerInput
	{
		std::string name;
		ptr_t<T> const &ptr;
	};

	template<typename T, typename CreateFunc>
	struct PointerOutput
	{
		std::string name;
		ptr_t<T> &ptr;
		CreateFunc create_func;
	};

	template<typename T>
	struct InheritancePointerInput
	{
		std::string name;
		ptr_t<T> const &ptr;
	};

	template<typename T, typename CreateByIdentityFunc>
	struct InheritancePointerOutput
	{
		std::string name;
		ptr_t<T> &ptr;
		CreateByIdentityFunc create_func_by_identity;
	};

	template<typename Coll>
	struct CollectionInput
	{
		std::string name;
		Coll const &coll;
	};

	template<typename Coll, typename InsertItemFunc>
	struct CollectionOutput
	{
		std::string name;
		Coll &coll;
		InsertItemFunc insert_item_func;
	};

	// TODO: убрать или перенести хелперные методы.

	template<typename T>
	auto constant(char const *name, T const &value)
	{
		return io::Constant<T>{name, value};
	}

	template<typename T>
	auto variable(char const *name, T &value)
	{
		return io::Variable<T>{name, value};
	}

	template<typename BaseObj, typename BaseObjId>
	auto reference_input(BaseObj const &ref, char const *ref_name, BaseObjId const &base_obj_id)
	{
		return io::ReferenceInput<BaseObj, BaseObjId>{ref_name, base_obj_id};
	}

	template<typename BaseObjId>
	auto reference_output(BaseObjId &base_obj_id, char const *ref_name)
	{
		return io::ReferenceOutput<BaseObjId>{base_obj_id, ref_name};
	}

	template<typename T>
	auto pointer_input(char const *ptr_name, ptr_t<T> const &ptr)
	{
		return io::PointerInput<T>{ptr_name, ptr};
	}

	template<typename T, typename CreateFunc>
	auto pointer_output(char const *ptr_name, ptr_t<T> &ptr, CreateFunc create_func)
	{
		return io::PointerOutput<T, CreateFunc>{ptr_name, ptr, create_func};
	}

	template<typename T>
	auto inheritance_pointer_input(char const *ptr_name, ptr_t<T> const &ptr)
	{
		return io::InheritancePointerInput<T>{ptr_name, ptr};
	}

	template<typename T, typename CreateByIdentityFunc>
	auto inheritance_pointer_output(char const *ptr_name, ptr_t<T> &ptr, CreateByIdentityFunc create_by_identity_func)
	{
		return io::InheritancePointerOutput<T, CreateByIdentityFunc>{ptr_name, ptr, create_by_identity_func};
	}

	template<typename Coll>
	auto collection_input(char const *name, Coll const &coll)
	{
		return io::CollectionInput<Coll>{name, coll};
	}

	template<typename Coll, typename InsertItemFunc>
	auto collection_output(char const *name, Coll &coll, InsertItemFunc insert_item_func)
	{
		return io::CollectionOutput<Coll, InsertItemFunc>{name, coll, insert_item_func};
	}

	#define IO_CONSTANT(c) io::constant(#c, c)
	#define IO_VARIABLE(v) io::variable(#v, v)

	#define IO_REFERENCE_INPUT(ref, base_obj_id) io::reference_input(ref, #ref, base_obj_id)
	#define IO_REFERENCE_OUTPUT(base_obj_id, ref_name) io::reference_output(base_obj_id, ref_name)

	#define IO_POINTER_INPUT(ptr) io::pointer_input(#ptr, ptr)
	#define IO_POINTER_OUTPUT(ptr, create_func) io::pointer_output(#ptr, ptr, create_func)

	#define IO_INHERITANCE_POINTER_INPUT(ptr) io::inheritance_pointer_input(#ptr, ptr)
	#define IO_INHERITANCE_POINTER_OUTPUT(ptr, create_func) io::inheritance_pointer_output(#ptr, ptr, create_func)

	#define IO_COLLECTION_INPUT(coll) io::collection_input(#coll, coll)
	#define IO_COLLECTION_OUTPUT(coll, insert_item_func) io::collection_output(#coll, coll, insert_item_func)

} // namespace io
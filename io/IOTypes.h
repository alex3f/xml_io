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

	#define IO_CONSTANT(c) io::constant(#c, c)
	#define IO_VARIABLE(v) io::variable(#v, v)

	#define IO_REFERENCE_INPUT(ref, base_obj_id) io::reference_input(ref, #ref, base_obj_id)
	#define IO_REFERENCE_OUTPUT(base_obj_id, ref_name) io::reference_output(base_obj_id, ref_name)

	#define IO_POINTER_INPUT(ptr) io::pointer_input(#ptr, ptr)
	#define IO_POINTER_OUTPUT(ptr, create_func) io::pointer_output(#ptr, ptr, create_func)

} // namespace io
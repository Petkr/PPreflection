#pragma once
#include "../dynamic_reference.h"
#include "../types/class_type.h"
#include "../types/make_reference_type.h"
#include "../types/reference_type.h"
#include "../types/referencable_type.hpp"
#include "args_to_arg_types.hpp"
#include "function.h"
#include "member_function.h"

constexpr void PPreflection::member_function::print_name_after_parent(PP::simple_ostream& out) const noexcept
{
	print_name_basic(out);

	print_cv(get_cv_qualifier(), out);

	switch (get_ref_qualifier())
	{
	case PP::ref_qualifier::none:
		break;
	case PP::ref_qualifier::lvalue:
		out.write("&"); break;
	case PP::ref_qualifier::rvalue:
		out.write("&&"); break;
	}

	print_noexcept(out);
}

constexpr bool PPreflection::member_function::can_invoke(const reference_type& caller_arg_type) const noexcept
{
	cv_type<referencable_type> caller_par_type(get_parent(), get_cv_qualifier());

	switch (get_ref_qualifier())
	{
	//case PP::ref_qualifier::none:
	case PP::ref_qualifier::lvalue:
		return make_reference_type(PP::value_false, caller_par_type).can_be_initialized(caller_arg_type);
	case PP::ref_qualifier::rvalue:
		return make_reference_type(PP::value_true , caller_par_type).can_be_initialized(caller_arg_type);
	default:
		return
			make_reference_type(PP::value_false, caller_par_type).can_be_initialized(caller_arg_type) ||
			make_reference_type(PP::value_true , caller_par_type).can_be_initialized(caller_arg_type);
	}
}

inline PPreflection::dynamic_variable PPreflection::member_function::invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, const dynamic_reference&> arg_iterator) const noexcept
{
	return invoke_unsafe_member(*arg_iterator, PP::iterator_next(arg_iterator));
}

constexpr bool PPreflection::member_function::can_invoke(PP::any_view<PP::iterator_category::ra, const reference_type&> argument_types) const noexcept
{
	return
		!PP::view_empty(argument_types) &&
		can_invoke(argument_types.begin()[0]) &&
		function::can_invoke(1_s >> argument_types);
}

inline PPreflection::dynamic_variable PPreflection::member_function::invoke(dynamic_reference caller, PP::any_view<PP::iterator_category::ra, const dynamic_reference&> args) const
{
	if (can_invoke(caller.get_type()) && function::can_invoke(args_to_arg_types(args)))
		return invoke_unsafe_member(caller, PP::view_begin(args));
	else
		return dynamic_variable::create_invalid(dynamic_object::invalid_code::implicit_conversion_error);
}

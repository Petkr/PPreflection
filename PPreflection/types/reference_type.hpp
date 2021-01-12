#pragma once
#include "reference_type.h"
#include "referencable_type.h"
#include "dynamic_reference_type.h"

template <bool rvalue>
constexpr auto reference_type::make_reference() const noexcept
{
	return remove_reference().make_reference<rvalue>();
}
constexpr auto reference_type::make_reference(bool lvalue) const noexcept
{
	return dynamic_reference_type(remove_reference(), lvalue);
}
constexpr auto reference_type::make_reference() const noexcept
{
	return make_reference(is_lvalue());
}
constexpr void reference_type::print_name_prefix(PP::simple_ostream& out) const noexcept
{
	remove_reference().print_name_prefix(out);

	out.write("(&");
	if (!is_lvalue())
		out.write("&");
}
constexpr void reference_type::print_name_suffix(PP::simple_ostream& out) const noexcept
{
	out.write(")");
	remove_reference().print_name_suffix(out);
}

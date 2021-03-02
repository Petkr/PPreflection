#pragma once
#include "dynamic_reference.h"

#include "PP/add_pointer.hpp"
#include "PP/add_reference.hpp"
#include "PP/concepts/rvalue_reference.hpp"
#include "PP/overloaded.hpp"
#include "PP/reinterpret_cast.hpp"
#include "PP/remove_reference.hpp"

#include "reflect.h"
#include "types/reference_type.h"
#include "types/type.h"

inline auto PPreflection::dynamic_reference::cast_unsafe(PP::concepts::type auto t) const noexcept -> PP_GET_TYPE(t)&&
{
	return (PP_GET_TYPE(t)&&)(*PP::reinterpret__cast(!PP::add_pointer(t), ptr));
}

inline auto PPreflection::dynamic_reference::cast(PP::concepts::type auto t) const -> PP_GET_TYPE(t)&&
{
	constexpr auto T = PP_COPY_TYPE(t) + PP::add_rvalue_tag;

	if (type::reflect(T).can_be_initialized(type_.make_reference(PP::value<!PP::is_rvalue_reference(T)>)))
		return cast_unsafe(t);
	else
		throw bad_cast_exception{};
}

inline auto* PPreflection::dynamic_reference::get_ptr(PP::concepts::type auto t) const
{
	if (type::reflect(t).can_be_pointer_initialized(type_.remove_reference()))
		return PP::reinterpret__cast(PP::add_pointer(t), ptr);
	else
		return nullptr;
}

inline auto& PPreflection::dynamic_reference::get_ref(PP::concepts::type auto t) const&
{
	return cast(t + PP::add_lvalue_tag);
}
inline auto&& PPreflection::dynamic_reference::get_ref(PP::concepts::type auto t) const&&
{
	return cast(t + PP::add_rvalue_tag);
}

constexpr PPreflection::dynamic_reference::dynamic_reference(auto&& r) noexcept
requires ((
	!PP::is_same_except_cvref* PP::type<dynamic_reference> &&
	!PP::is_same_except_cvref* PP::type<dynamic_object> &&
	!PP::is_same_except_cvref* PP::type<dynamic_variable>)(PP_DECLTYPE(r)))

	: dynamic_reference(&r, type::reflect(PP_DECLTYPE(r)))
{}

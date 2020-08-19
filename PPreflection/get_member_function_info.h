#pragma once
#include "get_function_info.h"
#include "add_cv.h"
#include "add_ref.h"

template <typename T>
struct get_member_function_info {};
template <typename F, typename C>
struct get_member_function_info<F C::*>
{
	using function_type = F;
	using class_ = C;
	using caller_type = add_ref<get_function_info<F>::ref, add_cv<get_function_info<F>::cv, C>>;
};

#pragma once
#include "overloaded_member_like_function.h"

class member_function;

class overloaded_member_function : public overloaded_member_like_function<member_function>
{
public:
	constexpr dynamic_object invoke(const dynamic_reference& caller, simple_range<const dynamic_reference> args = {}) const;
};
#pragma once
#include "namespace_function.h"
#include "overloaded_namespace_function.h"

constexpr const namespace_t& namespace_function::get_enclosing_namespace() const noexcept
{
	return get_overloaded_function().get_enclosing_namespace();
}

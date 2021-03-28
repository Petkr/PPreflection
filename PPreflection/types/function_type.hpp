#pragma once
#include "function_type.h"

#include "../conversion_sequence.hpp"
#include "pointer_type.h"

constexpr PPreflection::standard_conversion_sequence PPreflection::function_type::make_standard_conversion_sequence(const non_array_object_type& target, void*) const noexcept
{
	auto sequence = get_pointer_type().make_standard_conversion_sequence(target);
	sequence.set_to_pointer(function_to_pointer_conversion());
	return sequence;
}
#pragma once
#include "enum_type.h"

constexpr PPreflection::standard_conversion_sequence PPreflection::enum_type::make_standard_conversion_sequence(const non_array_object_type& target) const noexcept
{
	standard_conversion_sequence sequence(*this);

	if (is_scoped())
		return sequence;

	if (const auto* target_arithmetic_ptr = dynamic_cast<const arithmetic_type*>(&target); target_arithmetic_ptr)
	{
		sequence.set_validity(target);

		const integral_type& underlying_type = get_underlying_type();
		if (!has_fixed_underlying_type())
		{
			sequence.set_rank(underlying_type == target ? conversion_sequence_rank::promotion : conversion_sequence_rank::conversion);
		}
		else
		{
			sequence.set_enum_fixed_type();
			if (underlying_type == target)
				sequence.set_rank(conversion_sequence_rank::promotion);
			else if (underlying_type.promoted_type() == target)
			{
				sequence.set_rank(conversion_sequence_rank::promotion);
				sequence.set_enum_promoted_fixed_type();
			}
			else
				sequence.set_rank(conversion_sequence_rank::conversion);
		}

		sequence.set_promotion_conversion(conversion(*target_arithmetic_ptr));
	}

	return sequence;
}

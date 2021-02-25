#pragma once
#include "../../basic_named_descriptor.h"
#include "../type.h"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_named_type : public basic_named_descriptor<T, Base>
	{
		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
		{
			out.write(this->get_name());
		}
		constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
		{}
	};
}
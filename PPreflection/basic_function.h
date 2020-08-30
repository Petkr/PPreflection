#pragma once
#include <string_view>
#include "simple_ostream.h"
#include "pointer_view.hpp"
#include "cref_t.h"

class type;

namespace detail
{
	template <typename Overload, typename P, typename R, bool Noexcept, typename Base>
	class basic_function : public Base
	{
	protected:
		using ParameterTypes = P;
		using ReturnType = R;

	public:
		constexpr void print_name(simple_ostream& out) const noexcept override final;
		constexpr bool has_name(std::string_view name) const noexcept override final;

		constexpr const type& return_type() const noexcept override final;
		constexpr pointer_view<const cref_t<type>> parameter_types() const noexcept override final;

		constexpr bool is_noexcept() const noexcept override final;
	};
}

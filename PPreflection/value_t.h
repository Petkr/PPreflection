#pragma once

template <auto V>
struct value_t
{
	static constexpr decltype(auto) value_f() noexcept
	{
		return V;
	}
};

#pragma once
#include <cstddef>
#include "type_pack.h"
#include "value_t"
#include "get_value.h"

template <template <typename> typename Predicate>
struct find_index_pack_helper
{
	template <typename...>
	struct help : value_t<std::size_t(0)>
	{};
	template <typename T, typename... U>
	struct help<T, U...>
	{
		static constexpr std::size_t value_f() noexcept
		{
			if constexpr (get_value<Predicate<T>>())
				return 0;
			else
				return 1 + get_value<help<U...>>();
		}
	};
};


#pragma once
#include "../member_function.h"
#include "get_member_function_info.hpp"

namespace detail
{
	template <typename Overload, auto mf, typename Base>
	using basic_member_function_helper = basic_typed_function<
		Overload,
		typename PP::get_member_function_info<decltype(mf)>::Function,
		Base>;

	template <typename Overload, auto mf, typename Base>
	class basic_member_function_base : public basic_member_function_helper<Overload, mf, Base>
	{
	protected:
		using B = basic_member_function_helper<Overload, mf, Base>;
		using FunctionType = typename B::FunctionType;
		using Caller = typename PP::get_member_function_info<decltype(mf)>::Caller;
	};

	template <typename Overload, auto mf>
	class basic_member_function : public basic_member_function_base<Overload, mf, member_function>
	{
		using B = basic_member_function_base<Overload, mf, member_function>;

	protected:
		inline dynamic_variable invoke_unsafe_member(dynamic_reference caller, PP::any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
		{
			return invoke_helper<typename B::ParameterTypes>(
				[caller]<typename... T>(T&&... xs) -> decltype(auto)
				{
					return (caller.cast_unsafe<typename B::Caller>().*mf)(std::forward<T>(xs)...);
				}, arg_iterator);
		}
	};
}
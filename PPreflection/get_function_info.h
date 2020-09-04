#pragma once
#include <type_traits>
#include "type_pack.h"
#include "cv_qualifier.h"
#include "ref_qualifier.h"

template <typename Return, bool N, cv_qualifier CV, ref_qualifier R, typename... Parameters>
struct function_info
{
	using return_type = Return;
	using parameter_types = type_pack<Parameters...>;
	static constexpr bool Noexcept = N;
	static constexpr auto cv = CV;
	static constexpr auto ref = R;
};

template <typename T>
struct get_function_info {};



template<class Ret, class... Args>
struct get_function_info<Ret(Args...)>								: function_info<Ret, false, cv_qualifier::none, ref_qualifier::none, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const>						: function_info<Ret, false, cv_qualifier::const_, ref_qualifier::none, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) volatile>						: function_info<Ret, false, cv_qualifier::volatile_, ref_qualifier::none, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const volatile>				: function_info<Ret, false, cv_qualifier::const_volatile, ref_qualifier::none, Args...> {};

template<class Ret, class... Args>
struct get_function_info<Ret(Args...) &>							: function_info<Ret, false, cv_qualifier::none, ref_qualifier::lvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const&>						: function_info<Ret, false, cv_qualifier::const_, ref_qualifier::lvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) volatile&>					: function_info<Ret, false, cv_qualifier::volatile_, ref_qualifier::lvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const volatile&>				: function_info<Ret, false, cv_qualifier::const_volatile, ref_qualifier::lvalue, Args...> {};

template<class Ret, class... Args>
struct get_function_info<Ret(Args...) &&>							: function_info<Ret, false, cv_qualifier::none, ref_qualifier::rvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const&&>						: function_info<Ret, false, cv_qualifier::const_, ref_qualifier::rvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) volatile&&>					: function_info<Ret, false, cv_qualifier::volatile_, ref_qualifier::rvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const volatile&&>				: function_info<Ret, false, cv_qualifier::const_volatile, ref_qualifier::rvalue, Args...> {};



template<class Ret, class... Args>
struct get_function_info<Ret(Args...) noexcept>						: function_info<Ret, true , cv_qualifier::none, ref_qualifier::none, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const noexcept>				: function_info<Ret, true, cv_qualifier::const_, ref_qualifier::none, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) volatile noexcept>			: function_info<Ret, true, cv_qualifier::volatile_, ref_qualifier::none, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const volatile noexcept>		: function_info<Ret, true, cv_qualifier::const_volatile, ref_qualifier::none, Args...> {};

template<class Ret, class... Args>
struct get_function_info<Ret(Args...) & noexcept>					: function_info<Ret, true , cv_qualifier::none, ref_qualifier::lvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const& noexcept>				: function_info<Ret, true, cv_qualifier::const_, ref_qualifier::lvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) volatile& noexcept>			: function_info<Ret, true, cv_qualifier::volatile_, ref_qualifier::lvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const volatile& noexcept>		: function_info<Ret, true, cv_qualifier::const_volatile, ref_qualifier::lvalue, Args...> {};

template<class Ret, class... Args>
struct get_function_info<Ret(Args...) && noexcept>					: function_info<Ret, true , cv_qualifier::none, ref_qualifier::rvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const&& noexcept>				: function_info<Ret, true, cv_qualifier::const_, ref_qualifier::rvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) volatile&& noexcept>			: function_info<Ret, true, cv_qualifier::volatile_, ref_qualifier::rvalue, Args...> {};
template<class Ret, class... Args>
struct get_function_info<Ret(Args...) const volatile&& noexcept>	: function_info<Ret, true, cv_qualifier::const_volatile, ref_qualifier::rvalue, Args...> {};

#pragma once
#include "apply_template.hpp"
#include "dynamic_object.hpp"
#include "dynamic_reference.hpp"
#include "functional/id.hpp"
#include "fundamental_type_pack.h"
#include "get_type_class.hpp"
#include "reflect.h"
#include "template_tuple.hpp"
#include "transform_view.hpp"
#include "tuple_map.hpp"
#include "type_t.hpp"
#include "value_t.hpp"

#include "types/types.hpp"
#include "types/implementations/implementations.hpp"

#include "basic_namespace.h"
#include "Namespace.hpp"

#include "functions/functions.h"
#include "functions/implementations/implementations.h"

#include "descriptor.hpp"

#include "functions/function.hpp"
#include "functions/member_function.hpp"

#include "types/dynamic_function_type.h"
#include "make_array.h"
#include "types/dynamic_enum_type.h"

#include "parent_descriptor_reference.hpp"

namespace PPreflection
{
	namespace detail
	{
		struct overload_caster__no_specialization {};

		template <typename Overload, size_t Index>
		constexpr inline overload_caster__no_specialization overload_caster = {};

		constexpr inline auto basic_types = PP::template_tuple<
			basic_reference_type,
			basic_void_type,
			basic_function_type,
			basic_unknown_bound_array_type,
			basic_known_bound_array_type,
			basic_non_void_fundamental_type,
			basic_pointer_type,
			basic_pointer_to_member_type,
			basic_non_union_class_type,
			basic_union_type,
			basic_enum_type>;

		template <typename T>
		constexpr inline auto metadata = detail::basic_types[PP::value_t_static_cast(PP::type_size_t, get_type_class_value_t(PP::type<T>))](PP::type<T>)();

		template <> constexpr inline auto metadata<Namespace::global> = PPreflection::detail::basic_namespace<Namespace::global>{};

		constexpr auto&& reflect_helper(PP::concepts::type auto t) noexcept
		{
			return metadata<PP_GET_TYPE(t)>;
		}
	}

	constexpr inline const Namespace& global_namespace = reflect(PP::type<Namespace::global>);
}

using namespace PP::literals;

template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<PPreflection::Namespace::global>> = "global'"_sv;

template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<void					>> = "void"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<decltype(nullptr)		>> = "decltype(nullptr)"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<float					>> = "float"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<double				>> = "double"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<long double			>> = "long double"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<bool					>> = "bool"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<char					>> = "char"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<signed char			>> = "signed char"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned char			>> = "unsigned char"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<wchar_t				>> = "wchar_t"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<short int				>> = "short int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<int					>> = "int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<long int				>> = "long int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<long long int			>> = "long long int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned short int	>> = "unsigned short int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned int			>> = "unsigned int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned long int		>> = "unsigned long int"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<unsigned long long int>> = "unsigned long long int"_sv;
#ifdef __cpp_char8_t
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<char8_t				>> = "char8_t"_sv;
#endif
#ifdef __cpp_unicode_characters
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<char16_t				>> = "char16_t"_sv;
template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::name<char32_t				>> = "char32_t"_sv;
#endif

template <typename Class, typename... Parameters> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::is_explicit<Class, Parameters...>> = false;
template <typename Class, typename... Parameters> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::constructor<Class, Parameters...>>
	= detail::basic_constructor<Class, Parameters...>{};

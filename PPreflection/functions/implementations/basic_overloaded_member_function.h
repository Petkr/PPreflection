#pragma once
#include "basic_overloaded_function.h"
#include "../member_function.h"
#include "basic_overloaded_named_function.h"

namespace detail
{
	template <typename ID, typename Base>
	class basic_overloaded_member_function_base : public basic_overloaded_function<ID, Base>
	{
	protected:
		static constexpr auto member_function_base_overloads = reflect_many(
			basic_overloaded_function<ID, Base>::raw_overloads,
			PP::type_v<const Base&>);

		constexpr PP::any_view<const member_function&> get_member_function_overloads() const noexcept override final
		{
			return member_function_base_overloads;
		}
	};

	template <typename ID>
	class basic_overloaded_member_function final
		: public basic_overloaded_named_function<ID, basic_overloaded_member_function_base<ID, member_function>>
	{
		constexpr const class_type& get_parent() const noexcept override final
		{
			for (const member_function& mf : this->get_member_function_overloads())
				return mf.get_parent();

			std::terminate();
		}
	};
}

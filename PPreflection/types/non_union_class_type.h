#pragma once
#include "class_type.h"

namespace PPreflection
{
	class non_union_class_type : public class_type
	{
	public:
		//constexpr virtual PP::any_view<PP::iterator_category::ra, const non_union_class_type&> get_base_classes() const noexcept = 0;
		constexpr const non_union_class_type* as_non_union_class() const noexcept override final
		{
			return this;
		}
	};
}

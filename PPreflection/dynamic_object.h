#pragma once
#include "concepts/invocable.hpp"
#include "concepts/same_except_cvref.hpp"
#include "get_type.hpp"
#include "scoped.hpp"
#include "simple_view.hpp"
#include "unique.hpp"

namespace PPreflection
{
	class complete_object_type;
	class dynamic_reference;

	class dynamic_object
	{
	public:
		enum class invalid_code
		{
			none,

			implicit_conversion_error,
			indestructible_return_value,
		};

	private:
		struct void_tag {};

		union data
		{
			alignas(max_align_t) char* ptr;
			invalid_code code;

			constexpr data() noexcept
				: ptr(nullptr)
			{}
			explicit constexpr data(invalid_code code) noexcept
				: code(code)
			{}
			explicit constexpr data(char* ptr) noexcept
				: ptr(ptr)
			{}
		};

		class deleter
		{
			PP::unique<const complete_object_type*> type_;

		public:
			constexpr deleter(const complete_object_type* ptr) noexcept
				: type_(PP::unique_in_place_tag, ptr)
			{}
			constexpr void operator()(PP::unique<data>& u) const;

			constexpr const complete_object_type* get_type() const
			{
				return type_.get_object();
			}
		};

		PP::scoped<PP::unique<data>, deleter> x;

		constexpr void* get_address_helper(PP::concepts::value auto reference) noexcept;
		constexpr const void* get_address_helper(PP::concepts::value auto reference) const noexcept;

		constexpr void* get_address() noexcept;
		constexpr const void* get_address() const noexcept;

		static constexpr void* get_address(PP::concepts::value auto reference, PP::unique<data>& p, const complete_object_type& t) noexcept;
		static constexpr const void* get_address(PP::concepts::value auto reference, const PP::unique<data>& p, const complete_object_type& t) noexcept;

		constexpr dynamic_reference reference_cast_helper(PP::concepts::value auto rvalue) noexcept;
		constexpr dynamic_reference reference_cast_helper(PP::concepts::value auto rvalue) const noexcept;

		static constexpr char* allocate_and_initialize(PP::concepts::invocable auto&& i) noexcept;

		explicit constexpr dynamic_object(invalid_code code) noexcept;

		constexpr const complete_object_type* get_type_helper() const noexcept;

		constexpr bool invalid_check_helper(invalid_code code) const noexcept;

	public:
		static constexpr dynamic_object create_invalid(invalid_code code) noexcept
		{
			return dynamic_object(code);
		}
		static constexpr dynamic_object create_void() noexcept
		{
			return dynamic_object(invalid_code::none);
		}

		static constexpr dynamic_object create(PP::concepts::type auto t, auto&&... args);

		constexpr dynamic_object() = default;

		constexpr const complete_object_type& get_type() const noexcept;

		constexpr operator dynamic_reference() & noexcept;
		constexpr operator dynamic_reference() && noexcept;
		constexpr operator dynamic_reference() const& noexcept;
		constexpr operator dynamic_reference() const&& noexcept;

		constexpr explicit operator bool() const noexcept;
		constexpr invalid_code get_error_code() const noexcept;
		constexpr bool is_void() const noexcept;

		explicit constexpr dynamic_object(PP::concepts::invocable auto&& initializer);
	};

	static constexpr PP::string_view code_to_string(dynamic_object::invalid_code code) noexcept
	{
		switch (code)
		{
		case dynamic_object::invalid_code::none:
			return "none";
		case dynamic_object::invalid_code::implicit_conversion_error:
			return "implicit_conversion_error";
		case dynamic_object::invalid_code::indestructible_return_value:
			return "indestructible_return_value";
		default:
			return "";
		}
	}
}

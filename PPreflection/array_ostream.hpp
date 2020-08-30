#pragma once
#include <cstring>
#include <algorithm>
#include "simple_ostream.h"
#include "array_ostream.h"

template <std::size_t count>
constexpr array_ostream<count>::array_ostream() noexcept
	: buffer()
	, position(0)
{}

template <std::size_t count>
constexpr void array_ostream<count>::write(std::string_view s) noexcept
{
	if (position != buffer.size())
	{
		auto c = std::min(s.length(), buffer.size() - position);
		std::memcpy(buffer.data() + position, s.data(), c);
		position += c;
	}
}

template <std::size_t count>
void array_ostream<count>::write_to_ostream(std::ostream& out) noexcept
{
	out.write(buffer.data(), position);
	position = 0;
}
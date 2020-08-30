#include "descriptor.h"
#include "unique_raw_pointer.hpp"
#include "unique_pointer.hpp"
#include "dynamic_block.hpp"
#include "simple_vector.hpp"
#include "to_chars.hpp"
#include "simple_ostream.hpp"
#include "array_ostream.hpp"
#include "to_chars.hpp"

std::ostream& operator<<(std::ostream& out, const descriptor& d)
{
	array_ostream<100> so;
	d.print_name(so);
	so.write_to_ostream(out);

	return out;
}
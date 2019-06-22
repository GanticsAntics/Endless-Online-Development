#ifndef EOMAP_EO_TYPES_HPP
#define EOMAP_EO_TYPES_HPP

#include "common.hpp"

#include <array>
#include <cstdint>
#include <limits>
//
using eo_int = std::int_least32_t;
using eo_three = eo_int;
using eo_short = std::int_least16_t;
using eo_char = unsigned char;

using eo2_int = std::int_fast32_t;
using eo2_uint = std::uint_fast32_t;
using eo2_byte = unsigned char;

static constexpr eo_int eo_int_max = 0x7FFFFFFF;
static constexpr eo_int eo_three_max = eo_int(253) * 253 * 253;
static constexpr eo_short eo_short_max = 0x7FFF;
static constexpr eo_char eo_char_max = 253;

constexpr eo2_uint eo_number_decode(eo2_uint a = 254, eo2_uint b = 254,
                                    eo2_uint c = 254, eo2_uint d = 254)
{
	if (a == 254) a = 1;
	if (b == 254) b = 1;
	if (c == 254) c = 1;
	if (d == 254) d = 1;

	--a;
	--b;
	--c;
	--d;

	return (d * eo_three_max)
	     + (c * eo_short_max)
	     + (b * eo_char_max)
	     +  a;
}

constexpr array<eo2_byte, 4> eo_encode_number(eo2_uint n)
{
	eo2_byte a = 254, b = 254, c = 254, d = 254;

	{
		constexpr eo2_uint max = eo2_uint(253) * 253 * 253;
		d = (n / max) + 1;
		n %= max;
	}

	{
		constexpr eo2_uint max = eo2_uint(253) * 253;
		c = (n / max) + 1;
		n %= max;
	}

	{
		constexpr eo2_uint max = eo2_uint(253);
		b = (n / max) + 1;
		n %= max;
	}

	// Should do this maybe for correctness:
	//  if (x == 1) x = 254;

	a = n + 1;

	return array<eo2_byte, 4>{{a, b, c, d}};;
}

#endif // EOMAP_EO_TYPES_HPP

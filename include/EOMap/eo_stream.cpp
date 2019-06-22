#include "Stdafx.h"
#include "eo_stream.hpp"

#include <cassert>
#include <utility>
//
EO_Stream_Reader::EO_Stream_Reader(const char* data, size_t size)
	: m_data(data)
	, m_size(size)
	, m_pos(0)
{ }

EO_Stream_Reader::~EO_Stream_Reader()
{ }

size_t EO_Stream_Reader::length() const
{
	return m_size;
}

size_t EO_Stream_Reader::remaining() const
{
	return m_size - m_pos;
}

eo2_byte EO_Stream_Reader::get_byte()
{
	if (remaining() < 1)
		return 0;

	eo2_byte a = m_data[m_pos++];
	return a;
}

eo_char EO_Stream_Reader::get_char()
{
	if (remaining() < 1)
		return 0;

	eo2_byte a = m_data[m_pos++];

	return eo_number_decode(a);
}

eo_short EO_Stream_Reader::get_short()
{
	if (remaining() < 2)
		return get_char();

	eo2_byte a = m_data[m_pos++];
	eo2_byte b = m_data[m_pos++];

	return eo_number_decode(a, b);
}

eo_int EO_Stream_Reader::get_three()
{
	if (remaining() < 3)
		return get_short();

	eo2_byte a = m_data[m_pos++];
	eo2_byte b = m_data[m_pos++];
	eo2_byte c = m_data[m_pos++];

	return eo_number_decode(a, b, c);
}

eo_int EO_Stream_Reader::get_int()
{
	if (remaining() < 4)
		return get_three();

	eo2_byte a = m_data[m_pos++];
	eo2_byte b = m_data[m_pos++];
	eo2_byte c = m_data[m_pos++];
	eo2_byte d = m_data[m_pos++];

	return eo_number_decode(a, b, c, d);
}

std::string EO_Stream_Reader::get_fixed_string(std::size_t length)
{
	if (remaining() < length)
		length = remaining();

	std::size_t off = m_pos;

	m_pos += length;

	return std::string(m_data + off, length);
}

std::string EO_Stream_Reader::get_break_string()
{
	std::size_t off = m_pos;
	std::size_t len;

	while (unbroken())
		++m_pos;

	len = m_pos - off;

	get_byte();

	return std::string(m_data + off, len);
}

std::string EO_Stream_Reader::get_prefix_string()
{
	std::size_t length = get_char();
	return get_fixed_string(length);
}

std::string EO_Stream_Reader::get_end_string()
{
	return get_fixed_string(remaining());
}

bool EO_Stream_Reader::unbroken() const
{
	return remaining() && eo2_byte(m_data[m_pos]) != 0xFF;
}

EO_Stream_Builder::EO_Stream_Builder(std::size_t size_guess)
{
	m_data.reserve(size_guess);
}

EO_Stream_Builder::~EO_Stream_Builder()
{ }

size_t EO_Stream_Builder::length() const
{
	return m_data.size();
}

void EO_Stream_Builder::add_byte(eo2_byte n)
{
	m_data += n;
}

void EO_Stream_Builder::add_char(eo_char n)
{
	auto a = eo_encode_number(n);
	m_data += a[0];
}

void EO_Stream_Builder::add_short(eo_short n)
{
	auto a = eo_encode_number(n);
	m_data += a[0];
	m_data += a[1];
}

void EO_Stream_Builder::add_three(eo_int n)
{
	auto a = eo_encode_number(n);
	m_data += a[0];
	m_data += a[1];
	m_data += a[2];
}

void EO_Stream_Builder::add_int(eo_int n)
{
	auto a = eo_encode_number(n);
	m_data += a[0];
	m_data += a[1];
	m_data += a[2];
	m_data += a[3];
}

void EO_Stream_Builder::add_string(const std::string& str)
{
	m_data += str;
}

void EO_Stream_Builder::add_break_string(const std::string& str)
{
	m_data += str;
	add_byte(0xFF);
}

void EO_Stream_Builder::add_prefix_string(const std::string& str)
{
	add_char(str.size());
	add_string(str);
}

std::string& EO_Stream_Builder::get()
{
	return m_data;
}

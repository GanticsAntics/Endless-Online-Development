#ifndef EOMAP_EO_STREAM_HPP
#define EOMAP_EO_STREAM_HPP

#include "common.hpp"
#include "eo_types.hpp"
//
class EO_Stream_Reader
{
	private:
		const char* m_data;
		size_t m_size;
		size_t m_pos;

	public:
		EO_Stream_Reader(const char* data, size_t size);
		~EO_Stream_Reader();

		size_t length() const;
		size_t remaining() const;

		eo2_byte get_byte();
		eo_char get_char();
		eo_short get_short();
		eo_int get_three();
		eo_int get_int();

		std::string get_fixed_string(size_t length);
		std::string get_break_string();
		std::string get_prefix_string();
		std::string get_end_string();

		bool unbroken() const;
};

class EO_Stream_Builder
{
	private:
		std::string m_data;
		size_t m_pos;

	public:
		EO_Stream_Builder(size_t size_guess = 0);
		~EO_Stream_Builder();

		size_t length() const;

		void add_byte(eo2_byte n);
		void add_char(eo_char n);
		void add_short(eo_short n);
		void add_three(eo_int n);
		void add_int(eo_int n);

		void add_string(const std::string& str);
		void add_break_string(const std::string& str);
		void add_prefix_string(const std::string& str);

		std::string& get();
};

#endif // EOMAP_EO_STREAM_HPP

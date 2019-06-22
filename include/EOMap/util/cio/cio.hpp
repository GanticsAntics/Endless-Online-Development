#ifndef CIO_CIO_HPP
#define CIO_CIO_HPP

#include <array>
#include <cstdio>
#include <functional>
#include <limits>
#include <string>
#include <type_traits>
#include <utility>
//
namespace cio
{

namespace impl
{
	std::array<char, 5> flags_to_modestr(int flags);
}

class stream
{
	private:
		FILE* fh;
		bool m_unowned = false;

	public:
		struct no_ownership_t { };
		static constexpr no_ownership_t no_ownership = {};

		typedef FILE* element_type;

		enum mode_t
		{
			mode_read         = 1 << 0,
			mode_write        = 1 << 1,
			mode_append       = 1 << 2,
			mode_text         = 1 << 3,
			mode_no_overwrite = 1 << 4
		};

		stream(FILE*&& fh)
			: fh(fh)
		{ }

		stream(FILE* fh, no_ownership_t)
			: fh(fh)
			, m_unowned(true)
		{ }

		explicit stream(const char* filename, int flags = 0)
			: fh(nullptr)
		{
			open(filename, flags);
		}

		stream(const char* filename, const char* modestr)
			: fh(nullptr)
		{
			open(filename, modestr);
		}

		stream(stream&& other)
		{
			fh = other.fh;
			other.fh = nullptr;
		}

		stream(const stream&) = delete;
		stream& operator=(const stream&) = delete;

		bool open(const char* filename, int flags)
		{
			if (fh)
				fclose(fh);

			fh = fopen(filename, impl::flags_to_modestr(flags).data());

			return (fh != nullptr);
		}

		bool open(const char* filename, const char* modestr)
		{
			if (fh)
				fclose(fh);

			fh = fopen(filename, modestr);

			return (fh != nullptr);
		}
		
		void close()
		{
			fclose(fh);
			fh = nullptr;
		}

		FILE* handle()
		{
			return fh;
		}

		const FILE* handle() const
		{
			return fh;
		}

		FILE* release()
		{
			FILE* temp_fh = fh;
			fh = nullptr;
			return temp_fh;
		}

		void reset(FILE* new_fh = nullptr)
		{
			fh = new_fh;
		}

		void swap(stream& other)
		{
			std::swap(fh, other.fh);
		}

		bool is_open() const
		{
			return fh != nullptr;
		}

		bool eof() const
		{
			return std::feof(fh);
		}

		bool error() const
		{
			return std::ferror(fh);
		}

		void clear()
		{
			std::clearerr(fh);
		}

		explicit operator bool() const
		{
			return is_open() && !error();
		}

		bool put(char c)
		{
			int result = std::fputc(static_cast<int>(c), fh);
			return (result != EOF);
		}

		bool put(signed char c)
		{
			int result = std::fputc(static_cast<int>(c), fh);
			return (result != EOF);
		}

		bool put(unsigned char c)
		{
			int result = std::fputc(static_cast<int>(c), fh);
			return (result != EOF);
		}

		bool get(char& c)
		{
			int result = std::fgetc(fh);
			bool ok = (result != EOF);

			if (ok)
				c = static_cast<char>(result);

			return ok;
		}

		bool get(signed char& c)
		{
			int result = std::fgetc(fh);
			bool ok = (result != EOF);

			if (ok)
				c = static_cast<signed char>(result);

			return ok;
		}

		bool get(unsigned char& c)
		{
			int result = std::fgetc(fh);
			bool ok = (result != EOF);

			if (ok)
				c = static_cast<unsigned char>(result);

			return ok;
		}

		bool unget(char c)
		{
			int result = std::ungetc(static_cast<int>(c), fh);
			return (result != EOF);
		}

		bool unget(signed char c)
		{
			int result = std::ungetc(static_cast<int>(c), fh);
			return (result != EOF);
		}

		bool unget(unsigned char c)
		{
			int result = std::ungetc(static_cast<int>(c), fh);
			return (result != EOF);
		}

		bool write(const char* data)
		{
			int result = std::fputs(data, fh);
			return (result > 0);
		}

		std::size_t write(const char* data, std::size_t n)
		{
			return std::fwrite(data, 1, n, fh);
		}

		std::size_t read(char* data, std::size_t n)
		{
			return std::fread(data, 1, n, fh);
		}

		void rewind()
		{
			std::rewind(fh);
		}

		bool seek(long offset)
		{
			int result = std::fseek(fh, offset, SEEK_SET);
			return (result == 0);
		}

		bool skip(long offset)
		{
			int result = std::fseek(fh, offset, SEEK_CUR);
			return (result == 0);
		}

		bool seek_reverse(long offset)
		{
			int result = std::fseek(fh, offset, SEEK_END);
			return (result == 0);
		}

		long tell()
		{
			return std::ftell(fh);
		}

		void flush()
		{
			std::fflush(fh);
		}

		~stream()
		{
			if (!m_unowned && fh)
				close();
		}
};

struct io_flush_term_t { };
struct io_endl_term_t { };

constexpr io_flush_term_t flush;
constexpr io_endl_term_t endl;

inline stream& operator <<(stream& io, bool b)
{
	io.write(b ? "true" : "false");
	return io;
}

inline stream& operator <<(stream& io, void* p)
{
	fprintf(io.handle(), "%p", p);
	return io;
}

inline stream& operator <<(stream& io, char c)
{
	io.put(c);
	return io;
}

inline stream& operator <<(stream& io, signed char c)
{
	io.put(c);
	return io;
}

inline stream& operator <<(stream& io, unsigned char c)
{
	io.put(c);
	return io;
}

stream& operator <<(stream& io, int i);
stream& operator <<(stream& io, unsigned int i);

inline stream& operator <<(stream& io, short i)
{
	return (io << static_cast<int>(i));
}

inline stream& operator <<(stream& io, unsigned short i)
{
	return (io << static_cast<unsigned int>(i));
}

inline stream& operator <<(stream& io, int i)
{
	std::fprintf(io.handle(), "%i", i);
	return io;
}

inline stream& operator <<(stream& io, unsigned int i)
{
	std::fprintf(io.handle(), "%u", i);
	return io;
}

inline stream& operator <<(stream& io, long i)
{
	std::fprintf(io.handle(), "%li", i);
	return io;
}

inline stream& operator <<(stream& io, unsigned long i)
{
	std::fprintf(io.handle(), "%lu", i);
	return io;
}

inline stream& operator <<(stream& io, long long i)
{
	std::fprintf(io.handle(), "%lli", i);
	return io;
}

inline stream& operator <<(stream& io, unsigned long long i)
{
	std::fprintf(io.handle(), "%llu", i);
	return io;
}

inline stream& operator <<(stream& io, float f)
{
	std::fprintf(io.handle(), "%f", double(f));
	return io;
}

inline stream& operator <<(stream& io, double f)
{
	std::fprintf(io.handle(), "%f", f);
	return io;
}

inline stream& operator <<(stream& io, long double f)
{
	std::fprintf(io.handle(), "%Lf", f);
	return io;	
}

inline stream& operator <<(stream& io, const char* s)
{
	io.write(s);
	return io;
}

template <std::size_t Sz> stream& operator <<(stream& io, const char s[Sz])
{
	io.write(s, Sz);
	return io;
}

inline stream& operator <<(stream& io, const std::string& s)
{
	io.write(s.data(), s.size());
	return io;
}

inline stream& operator <<(stream& io, const io_flush_term_t&)
{
	io.flush();
	return io;
}

inline stream& operator <<(stream& io, const io_endl_term_t&)
{
	io.put('\n');
	io.flush();
	return io;
}

// C++17 soon (tm)
// inline stream& operator <<(stream& io, const std::string_view& sv);

inline void swap(stream& a, stream& b)
{
	a.swap(b);
}

extern stream in;
extern stream out;
extern stream err;

}

namespace std
{
	template <> struct hash<::cio::stream>
	{
		typedef ::cio::stream argument_type;
		typedef ::std::size_t result_type;
		
		::std::size_t operator()(const ::cio::stream& io) const
		{
			return ::std::hash<const FILE*>()(io.handle());
		}
	};

	template <> struct hash<::cio::stream::mode_t>
		: public hash<std::underlying_type<::cio::stream::mode_t>::type>
	{ };
}

#endif // CIO_CIO_HPP

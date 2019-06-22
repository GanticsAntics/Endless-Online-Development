#include "Stdafx.h"
#include "cio.hpp"
//
namespace cio
{

namespace impl
{

	std::array<char, 5> flags_to_modestr(int flags)
	{
		std::array<char, 5> modestr_buf;
		int off = 0;

		int read = flags & cio::stream::mode_read;
		int write = flags & cio::stream::mode_write;
		int append = flags & cio::stream::mode_append;
		int text = flags & cio::stream::mode_text;
		int no_overwrite = flags & cio::stream::mode_no_overwrite;

		int rwa = append ? 2 : (write ? 1 : 0);

		modestr_buf[off++] = "rwa"[rwa];

		if (read && (write || append))
			modestr_buf[off++] = '+';

		if (!text)
			modestr_buf[off++] = 'b';

		if (no_overwrite)
			modestr_buf[off++] = 'x';

		modestr_buf[off++] = '\0';

		return modestr_buf;
	}
}
/*
stream in(stdin, cio::stream::no_ownership);
stream out(stdout, cio::stream::no_ownership);
stream err(stderr, cio::stream::no_ownership);
*/
}

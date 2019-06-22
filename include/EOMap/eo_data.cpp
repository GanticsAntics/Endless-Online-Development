#include "Stdafx.h"
#include "eo_data.hpp"

#include "eo_stream.hpp"

void Full_EMF::decode_str(char* data, size_t n)
{
	for (size_t i = 0; i < n / 2; ++i)
		std::swap(data[i], data[n - i - 1]);

	bool flippy = n % 2 == 1;

	for (size_t i = 0; i < n; ++i)
	{
		unsigned char c = data[i];

		unsigned char f = 0x2E * flippy * ((c >= 0x50) ? -1 : 1);

		if (c >= 0x22 && c <= 0x7E)
			data[i] = 0x9F - c - f;

		flippy = !flippy;
	}
}
//
void Full_EMF::unserialize(EO_Stream_Reader& reader)
{
	header.unserialize(reader);
	decode_str(&header.name[0], header.name.length());
	header.name = header.name.substr(0, header.name.find_first_of(0xFF));

	m_meta.resize(header.width * header.height);
	m_gfx.resize(header.width * header.height);

	{
		int rows = reader.get_char();
		for (int i = 0; i < rows; ++i)
		{
			int y = reader.get_char();
			int tiles = reader.get_char();
			for (int ii = 0; ii < tiles; ++ii)
			{
				int x = reader.get_char();
				int c = reader.get_char();

				if (x < header.width && y < header.height)
					meta(x, y).spec = static_cast<EMF_Tile_Spec>(c);
			}
		}
	}

	{
		int rows = reader.get_char();
		for (int i = 0; i < rows; ++i)
		{
			int y = reader.get_char();
			int tiles = reader.get_char();
			for (int ii = 0; ii < tiles; ++ii)
			{
				int x = reader.get_char();
				EMF_Warp warp(reader);

				if (x < header.width && y < header.height)
					meta(x, y).warp = warp;
			}
		}
	}

	for (int layer = 0; layer < 9; ++layer)
	{
		int rows = reader.get_char();
		for (int i = 0; i < rows; ++i)
		{
			int y = reader.get_char();
			int tiles = reader.get_char();
			for (int ii = 0; ii < tiles; ++ii)
			{
				int x = reader.get_char();
				int s = reader.get_short();
				if (layer == 0 && s == 0)
				{
					s = -1;
				}
				if (x < header.width && y < header.height)
					gfx(x, y)[layer] = s;
			}
		}
	}

	if (reader.remaining() > 0)
	{
		int signs = reader.get_char();
		for (int i = 0; i < signs; ++i)
		{
			int x = reader.get_char();
			int y = reader.get_char();
			int length = reader.get_short() - 1;
			string data = reader.get_fixed_string(length);
			decode_str(&data[0], data.size());
			int title_length = reader.get_char();
			string title = data.substr(0, title_length);
			string message = data.substr(title_length);

			if (x < header.width && y < header.height)
				meta(x, y).sign = pair<string, string>{title, message};
		}
	}
}

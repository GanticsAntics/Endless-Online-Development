#ifndef EOMAP_EO_DATA_HPP
#define EOMAP_EO_DATA_HPP

#include "common.hpp"
#include "eo_types.hpp"
#include "pub_structs.hpp"

#include <map>

//// Wraps the auto-generated eo::EMF_File with code to read the sparse array data
struct Full_EMF
{
	EMF_File header;

	struct TileMeta
	{
		EMF_Tile_Spec spec = EMF_Tile_Spec::None;
		EMF_Warp warp;
		pair<std::string, std::string> sign;
	};

	std::vector<TileMeta> m_meta;
	std::vector<std::array<eo_short, 9>> m_gfx;

	TileMeta& meta(int x, int y)
		{ return m_meta[y * header.width + x]; }

	std::array<eo_short, 9>& gfx(int x, int y)
	{
		return m_gfx[y * header.width + x];
	}

	const TileMeta& meta(int x, int y) const
		{ return m_meta[y * header.width + x]; }

	const std::array<eo_short, 9>& gfx(int x, int y) const
		{ return m_gfx[y * header.width + x]; }

	static void decode_str(char* data, size_t n);
	std::array<eo2_byte, 4U> rid;
	unsigned int MapFileSize;
	Full_EMF() = default;
	Full_EMF(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

#endif // EOMAP_EO_DATA_HPP

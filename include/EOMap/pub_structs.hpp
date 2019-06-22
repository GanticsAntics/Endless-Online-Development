#ifndef EOMAP_PUB_STRUCTS_HPP
#define EOMAP_PUB_STRUCTS_HPP

#include "eo_types.hpp"

#include "pub_enums.hpp"

#include <array>
#include <numeric>
#include <string>
#include <vector>
//
class EO_Stream_Reader;
class EO_Stream_Builder;

struct ECF_Class
{
	std::string name;
	eo_char parent_type;
	ECF_Class_Type type;
	eo_short str;
	eo_short intl;
	eo_short wis;
	eo_short agi;
	eo_short con;
	eo_short cha;

	ECF_Class() = default;
	ECF_Class(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct EIF_Item
{
	std::string name;
	eo_short graphic_id;
	EIF_Item_SubType type;
	EIF_Item_SubType subtype;
	EIF_Item_Special special;
	eo_short hp;
	eo_short tp;
	eo_short min_damage;
	eo_short max_damage;
	eo_short accuracy;
	eo_short evade;
	eo_short armor;
	eo_char str;
	eo_char intl;
	eo_char wis;
	eo_char agi;
	eo_char con;
	eo_char cha;
	eo_three spec1;
	eo_char spec2;
	eo_char spec3;
	eo_short level_req;
	eo_short class_req;
	eo_short str_req;
	eo_short int_req;
	eo_short wis_req;
	eo_short agi_req;
	eo_short con_req;
	eo_short cha_req;
	eo_char element;
	eo_char element_power;
	eo_char weight;
	EIF_Item_Size size;

	EIF_Item() = default;
	EIF_Item(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct EMF_NPC
{
	eo_char x;
	eo_char y;
	eo_short id;
	eo_char spawn_type;
	eo_short spawn_time;
	eo_char amount;

	EMF_NPC() = default;
	EMF_NPC(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct EMF_Unknown
{
	eo_char unknown1;
	eo_char unknown2;
	eo_char unknown3;
	eo_char unknown4;

	EMF_Unknown() = default;
	EMF_Unknown(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct EMF_Item
{
	eo_char x;
	eo_char y;
	eo_short key_required;
	eo_char chest_slot;
	eo_short item_id;
	eo_short spawn_time;
	eo_three item_amount;

	EMF_Item() = default;
	EMF_Item(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct ENF_NPC
{
	std::string name;
	eo_short graphic_id;
	eo_short boss;
	eo_short child;
	ENF_NPC_Type type;
	eo_short vendor_id;
	eo_three hp;
	eo_short min_damage;
	eo_short max_damage;
	eo_short accuracy;
	eo_short evade;
	eo_short armor;
	eo_short element_weak;
	eo_short element_weak_power;
	eo_three experience;

	ENF_NPC() = default;
	ENF_NPC(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct ESF_Spell
{
	std::string name;
	std::string shout;
	eo_short icon_id;
	eo_short graphic_id;
	eo_short tp_cost;
	eo_short sp_cost;
	eo_char cast_time;
	ESF_Spell_Type type;
	eo_char element;
	eo_short element_power;
	ESF_Spell_Target_Restrict target_restrict;
	ESF_Spell_Target_Type target_type;
	eo_short min_damage;
	eo_short max_damage;
	eo_short accuracy;
	eo_short hp;

	ESF_Spell() = default;
	ESF_Spell(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct ECF_File
{
	std::string magic;
	std::array<eo2_byte, 4> hash;
	eo_short num_classes;
	std::vector<ECF_Class> classes;

	ECF_File() = default;
	ECF_File(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct EIF_File
{
	std::string magic;
	std::array<eo2_byte, 4> hash;
	eo_short num_items;
	std::vector<EIF_Item> items;

	EIF_File() = default;
	EIF_File(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct EMF_File
{
	std::string magic;
	std::array<eo2_byte, 4> hash;
	std::string name;
	EMF_Type type;
	EMF_Effect effect;
	eo_char music_id;
	eo_char music_extra;
	eo_short ambient_sound_id;
	eo_char width;
	eo_char height;
	eo_short fill_tile;
	eo_char map_available;
	eo_char can_scroll;
	eo_char relog_x;
	eo_char relog_y;
	eo_char num_npcs;
	std::vector<EMF_NPC> npcs;
	eo_char num_unknowns;
	std::vector<EMF_Unknown> unknowns;
	eo_char num_items;
	std::vector<EMF_Item> items;

	EMF_File() = default;
	EMF_File(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct EMF_Warp
{
	eo_short warp_map;
	eo_char warp_x;
	eo_char warp_y;
	eo_char level_required;
	eo_short door;

	EMF_Warp() = default;
	EMF_Warp(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct ENF_File
{
	std::string magic;
	std::array<eo2_byte, 4> hash;
	eo_short num_npcs;
	std::vector<ENF_NPC> npcs;

	ENF_File() = default;
	ENF_File(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

struct ESF_File
{
	std::string magic;
	std::array<eo2_byte, 4> hash;
	eo_short num_spells;
	std::vector<ESF_Spell> spells;

	ESF_File() = default;
	ESF_File(EO_Stream_Reader& reader) { unserialize(reader); }
	std::size_t byte_size() const;
	void serialize(EO_Stream_Builder& builder) const;
	void unserialize(EO_Stream_Reader& reader);
};

#endif // EOMAP_PUB_STRUCTS_HPP


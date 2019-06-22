#include "Stdafx.h"
#include "pub_structs.hpp"

#include "eo_stream.hpp"
//
std::size_t ECF_Class::byte_size() const
{
	return 15
	      + name.size();
}

void ECF_Class::serialize(EO_Stream_Builder& builder) const
{
	builder.add_prefix_string(name);
	builder.add_char(parent_type);
	builder.add_char(static_cast<eo_char>(type));
	builder.add_short(str);
	builder.add_short(intl);
	builder.add_short(wis);
	builder.add_short(agi);
	builder.add_short(con);
	builder.add_short(cha);
}

void ECF_Class::unserialize(EO_Stream_Reader& reader)
{
	name = reader.get_prefix_string();
	parent_type = reader.get_char();
	type = static_cast<ECF_Class_Type>(reader.get_char());
	str = reader.get_short();
	intl = reader.get_short();
	wis = reader.get_short();
	agi = reader.get_short();
	con = reader.get_short();
	cha = reader.get_short();
}

std::size_t ECF_File::byte_size() const
{
	return 3
	      + magic.size()
	      + (1 * hash.size())
	      + std::accumulate(classes.begin(), classes.end(), std::size_t(0), [](std::size_t i, const auto& x) { return i + x.byte_size(); });
}

void ECF_File::serialize(EO_Stream_Builder& builder) const
{
	builder.add_string(magic);
	for (std::size_t i = 0; i < hash.size(); ++i)
		builder.add_byte(hash[i]);
	builder.add_short(num_classes);
	builder.add_char(0);
	for (std::size_t i = 0; i < classes.size(); ++i)
		classes[i].serialize(builder);
}

void ECF_File::unserialize(EO_Stream_Reader& reader)
{
	magic = reader.get_fixed_string(3);
	for (std::size_t i = 0; i < 4; ++i)
		hash[i] = reader.get_byte();
	num_classes = reader.get_short();
	reader.get_char();
	classes.resize(num_classes);
	for (std::size_t i = 0; i < num_classes; ++i)
		classes[i].unserialize(reader);
}

std::size_t EIF_File::byte_size() const
{
	return 3
	      + magic.size()
	      + (1 * hash.size())
	      + std::accumulate(items.begin(), items.end(), std::size_t(0), [](std::size_t i, const auto& x) { return i + x.byte_size(); });
}

void EIF_File::serialize(EO_Stream_Builder& builder) const
{
	builder.add_string(magic);
	for (std::size_t i = 0; i < hash.size(); ++i)
		builder.add_byte(hash[i]);
	builder.add_short(num_items);
	builder.add_char(0);
	for (std::size_t i = 0; i < items.size(); ++i)
		items[i].serialize(builder);
}

void EIF_File::unserialize(EO_Stream_Reader& reader)
{
	magic = reader.get_fixed_string(3);
	for (std::size_t i = 0; i < 4; ++i)
		hash[i] = reader.get_byte();
	num_items = reader.get_short();
	reader.get_char();
	items.resize(num_items);
	for (std::size_t i = 0; i < num_items; ++i)
		items[i].unserialize(reader);
}

std::size_t EIF_Item::byte_size() const
{
	return 59
	      + name.size();
}

void EIF_Item::serialize(EO_Stream_Builder& builder) const
{
	builder.add_prefix_string(name);
	builder.add_short(graphic_id);
	builder.add_char(static_cast<eo_char>(type));
	builder.add_char(static_cast<eo_char>(subtype));
	builder.add_char(static_cast<eo_char>(special));
	builder.add_short(hp);
	builder.add_short(tp);
	builder.add_short(min_damage);
	builder.add_short(max_damage);
	builder.add_short(accuracy);
	builder.add_short(evade);
	builder.add_short(armor);
	builder.add_char(0);
	builder.add_char(str);
	builder.add_char(intl);
	builder.add_char(wis);
	builder.add_char(agi);
	builder.add_char(con);
	builder.add_char(cha);
	builder.add_char(0);
	builder.add_char(0);
	builder.add_char(0);
	builder.add_char(0);
	builder.add_char(0);
	builder.add_char(0);
	builder.add_three(spec1);
	builder.add_char(spec2);
	builder.add_char(spec3);
	builder.add_short(level_req);
	builder.add_short(class_req);
	builder.add_short(str_req);
	builder.add_short(int_req);
	builder.add_short(wis_req);
	builder.add_short(agi_req);
	builder.add_short(con_req);
	builder.add_short(cha_req);
	builder.add_char(element);
	builder.add_char(element_power);
	builder.add_char(weight);
	builder.add_char(0);
	builder.add_char(static_cast<eo_char>(size));
}

void EIF_Item::unserialize(EO_Stream_Reader& reader)
{
	name = reader.get_prefix_string();
	graphic_id = reader.get_short();
	type = static_cast<EIF_Item_SubType>(reader.get_char());
	subtype = static_cast<EIF_Item_SubType>(reader.get_char());
	special = static_cast<EIF_Item_Special>(reader.get_char());
	hp = reader.get_short();
	tp = reader.get_short();
	min_damage = reader.get_short();
	max_damage = reader.get_short();
	accuracy = reader.get_short();
	evade = reader.get_short();
	armor = reader.get_short();
	reader.get_char();
	str = reader.get_char();
	intl = reader.get_char();
	wis = reader.get_char();
	agi = reader.get_char();
	con = reader.get_char();
	cha = reader.get_char();
	reader.get_char();
	reader.get_char();
	reader.get_char();
	reader.get_char();
	reader.get_char();
	reader.get_char();
	spec1 = reader.get_three();
	spec2 = reader.get_char();
	spec3 = reader.get_char();
	level_req = reader.get_short();
	class_req = reader.get_short();
	str_req = reader.get_short();
	int_req = reader.get_short();
	wis_req = reader.get_short();
	agi_req = reader.get_short();
	con_req = reader.get_short();
	cha_req = reader.get_short();
	element = reader.get_char();
	element_power = reader.get_char();
	weight = reader.get_char();
	reader.get_char();
	size = static_cast<EIF_Item_Size>(reader.get_char());
}

std::size_t EMF_File::byte_size() const
{
	return 18
	      + magic.size()
	      + (1 * hash.size())
	      + name.size()
	      + std::accumulate(npcs.begin(), npcs.end(), std::size_t(0), [](std::size_t i, const auto& x) { return i + x.byte_size(); })
	      + std::accumulate(unknowns.begin(), unknowns.end(), std::size_t(0), [](std::size_t i, const auto& x) { return i + x.byte_size(); })
	      + std::accumulate(items.begin(), items.end(), std::size_t(0), [](std::size_t i, const auto& x) { return i + x.byte_size(); });
}

void EMF_File::serialize(EO_Stream_Builder& builder) const
{
	builder.add_string(magic);
	for (std::size_t i = 0; i < hash.size(); ++i)
		builder.add_byte(hash[i]);
	builder.add_string(name);
	builder.add_char(static_cast<eo_char>(type));
	builder.add_char(static_cast<eo_char>(effect));
	builder.add_char(music_id);
	builder.add_char(music_extra);
	builder.add_short(ambient_sound_id);
	builder.add_char(width);
	builder.add_char(height);
	builder.add_short(fill_tile);
	builder.add_char(map_available);
	builder.add_char(can_scroll);
	builder.add_char(relog_x);
	builder.add_char(relog_y);
	builder.add_char(0);
	builder.add_char(num_npcs);
	for (std::size_t i = 0; i < npcs.size(); ++i)
		npcs[i].serialize(builder);
	builder.add_char(num_unknowns);
	for (std::size_t i = 0; i < unknowns.size(); ++i)
		unknowns[i].serialize(builder);
	builder.add_char(num_items);
	for (std::size_t i = 0; i < items.size(); ++i)
		items[i].serialize(builder);
}

void EMF_File::unserialize(EO_Stream_Reader& reader)
{
	magic = reader.get_fixed_string(3);
	for (std::size_t i = 0; i < 4; ++i)
		hash[i] = reader.get_byte();
	name = reader.get_fixed_string(24);
	type = static_cast<EMF_Type>(reader.get_char());
	effect = static_cast<EMF_Effect>(reader.get_char());
	music_id = reader.get_char();
	music_extra = reader.get_char();
	ambient_sound_id = reader.get_short();
	width = reader.get_byte();
	height = reader.get_byte();
	fill_tile = reader.get_short();
	map_available = reader.get_char();
	can_scroll = reader.get_char();
	relog_x = reader.get_char();
	relog_y = reader.get_char();
	reader.get_char();
	num_npcs = reader.get_char();
	npcs.resize(num_npcs);
	for (std::size_t i = 0; i < num_npcs; ++i)
		npcs[i].unserialize(reader);
	num_unknowns = reader.get_char();
	unknowns.resize(num_unknowns);
	for (std::size_t i = 0; i < num_unknowns; ++i)
		unknowns[i].unserialize(reader);
	num_items = reader.get_char();
	items.resize(num_items);
	for (std::size_t i = 0; i < num_items; ++i)
		items[i].unserialize(reader);
}

std::size_t EMF_Item::byte_size() const
{
	return 12;
}

void EMF_Item::serialize(EO_Stream_Builder& builder) const
{
	builder.add_char(x);
	builder.add_char(y);
	builder.add_short(key_required);
	builder.add_char(chest_slot);
	builder.add_short(item_id);
	builder.add_short(spawn_time);
	builder.add_three(item_amount);
}

void EMF_Item::unserialize(EO_Stream_Reader& reader)
{
	x = reader.get_char();
	y = reader.get_char();
	key_required = reader.get_short();
	chest_slot = reader.get_char();
	item_id = reader.get_short();
	spawn_time = reader.get_short();
	item_amount = reader.get_three();
}

std::size_t EMF_NPC::byte_size() const
{
	return 8;
}

void EMF_NPC::serialize(EO_Stream_Builder& builder) const
{
	builder.add_char(x);
	builder.add_char(y);
	builder.add_short(id);
	builder.add_char(spawn_type);
	builder.add_short(spawn_time);
	builder.add_char(amount);
}

void EMF_NPC::unserialize(EO_Stream_Reader& reader)
{
	x = reader.get_char();
	y = reader.get_char();
	id = reader.get_short();
	spawn_type = reader.get_char();
	spawn_time = reader.get_short();
	amount = reader.get_char();
}

std::size_t EMF_Unknown::byte_size() const
{
	return 4;
}

void EMF_Unknown::serialize(EO_Stream_Builder& builder) const
{
	builder.add_char(0);
	builder.add_char(0);
	builder.add_char(0);
	builder.add_char(0);
	//builder.add_char(0);
}

void EMF_Unknown::unserialize(EO_Stream_Reader& reader)
{
	unknown1 = reader.get_char();
	unknown2 = reader.get_char();
	unknown3 = reader.get_char();
	unknown4 = reader.get_char();
	//reader.get_char();
}

std::size_t EMF_Warp::byte_size() const
{
	return 7;
}

void EMF_Warp::serialize(EO_Stream_Builder& builder) const
{
	builder.add_short(warp_map);
	builder.add_char(warp_x);
	builder.add_char(warp_y);
	builder.add_char(level_required);
	builder.add_short(door);
}

void EMF_Warp::unserialize(EO_Stream_Reader& reader)
{
	warp_map = reader.get_short();
	warp_x = reader.get_char();
	warp_y = reader.get_char();
	level_required = reader.get_char();
	door = reader.get_short();
}

std::size_t ENF_File::byte_size() const
{
	return 3
	      + magic.size()
	      + (1 * hash.size())
	      + std::accumulate(npcs.begin(), npcs.end(), std::size_t(0), [](std::size_t i, const auto& x) { return i + x.byte_size(); });
}

void ENF_File::serialize(EO_Stream_Builder& builder) const
{
	builder.add_string(magic);
	for (std::size_t i = 0; i < hash.size(); ++i)
		builder.add_byte(hash[i]);
	builder.add_short(num_npcs);
	builder.add_char(0);
	for (std::size_t i = 0; i < npcs.size(); ++i)
		npcs[i].serialize(builder);
}

void ENF_File::unserialize(EO_Stream_Reader& reader)
{
	magic = reader.get_fixed_string(3);
	for (std::size_t i = 0; i < 4; ++i)
		hash[i] = reader.get_byte();
	num_npcs = reader.get_short();
	reader.get_char();
	npcs.resize(num_npcs);
	for (std::size_t i = 0; i < num_npcs; ++i)
		npcs[i].unserialize(reader);
}

std::size_t ENF_NPC::byte_size() const
{
	return 40
	      + name.size();
}

void ENF_NPC::serialize(EO_Stream_Builder& builder) const
{
	builder.add_prefix_string(name);
	builder.add_short(graphic_id);
	builder.add_char(0);
	builder.add_short(boss);
	builder.add_short(child);
	builder.add_short(static_cast<eo_short>(type));
	builder.add_short(vendor_id);
	builder.add_three(hp);
	builder.add_short(0);
	builder.add_short(min_damage);
	builder.add_short(max_damage);
	builder.add_short(accuracy);
	builder.add_short(evade);
	builder.add_short(armor);
	builder.add_char(0);
	builder.add_short(0);
	builder.add_short(0);
	builder.add_short(element_weak);
	builder.add_short(element_weak_power);
	builder.add_char(0);
	builder.add_three(experience);
}

void ENF_NPC::unserialize(EO_Stream_Reader& reader)
{
	name = reader.get_prefix_string();
	graphic_id = reader.get_short();
	reader.get_char();
	boss = reader.get_short();
	child = reader.get_short();
	type = static_cast<ENF_NPC_Type>(reader.get_short());
	vendor_id = reader.get_short();
	hp = reader.get_three();
	reader.get_short();
	min_damage = reader.get_short();
	max_damage = reader.get_short();
	accuracy = reader.get_short();
	evade = reader.get_short();
	armor = reader.get_short();
	reader.get_char();
	reader.get_short();
	reader.get_short();
	element_weak = reader.get_short();
	element_weak_power = reader.get_short();
	reader.get_char();
	experience = reader.get_three();
}

std::size_t ESF_File::byte_size() const
{
	return 3
	      + magic.size()
	      + (1 * hash.size())
	      + std::accumulate(spells.begin(), spells.end(), std::size_t(0), [](std::size_t i, const auto& x) { return i + x.byte_size(); });
}

void ESF_File::serialize(EO_Stream_Builder& builder) const
{
	builder.add_string(magic);
	for (std::size_t i = 0; i < hash.size(); ++i)
		builder.add_byte(hash[i]);
	builder.add_short(num_spells);
	builder.add_char(0);
	for (std::size_t i = 0; i < spells.size(); ++i)
		spells[i].serialize(builder);
}

void ESF_File::unserialize(EO_Stream_Reader& reader)
{
	magic = reader.get_fixed_string(3);
	for (std::size_t i = 0; i < 4; ++i)
		hash[i] = reader.get_byte();
	num_spells = reader.get_short();
	reader.get_char();
	spells.resize(num_spells);
	for (std::size_t i = 0; i < num_spells; ++i)
		spells[i].unserialize(reader);
}

std::size_t ESF_Spell::byte_size() const
{
	return 53
	      + name.size()
	      + shout.size();
}

void ESF_Spell::serialize(EO_Stream_Builder& builder) const
{
	builder.add_prefix_string(name);
	builder.add_prefix_string(shout);
	builder.add_short(icon_id);
	builder.add_short(graphic_id);
	builder.add_short(tp_cost);
	builder.add_short(sp_cost);
	builder.add_char(cast_time);
	builder.add_char(0);
	builder.add_char(0);
	builder.add_three(static_cast<eo_three>(type));
	builder.add_char(element);
	builder.add_short(element_power);
	builder.add_char(static_cast<eo_char>(target_restrict));
	builder.add_char(static_cast<eo_char>(target_type));
	builder.add_char(0);
	builder.add_char(0);
	builder.add_short(0);
	builder.add_short(min_damage);
	builder.add_short(max_damage);
	builder.add_short(accuracy);
	builder.add_short(0);
	builder.add_short(0);
	builder.add_char(0);
	builder.add_short(hp);
	builder.add_short(0);
	builder.add_char(0);
	builder.add_short(0);
	builder.add_short(0);
	builder.add_short(0);
	builder.add_short(0);
	builder.add_short(0);
	builder.add_short(0);
}

void ESF_Spell::unserialize(EO_Stream_Reader& reader)
{
	name = reader.get_prefix_string();
	shout = reader.get_prefix_string();
	icon_id = reader.get_short();
	graphic_id = reader.get_short();
	tp_cost = reader.get_short();
	sp_cost = reader.get_short();
	cast_time = reader.get_char();
	reader.get_char();
	reader.get_char();
	type = static_cast<ESF_Spell_Type>(reader.get_three());
	element = reader.get_char();
	element_power = reader.get_short();
	target_restrict = static_cast<ESF_Spell_Target_Restrict>(reader.get_char());
	target_type = static_cast<ESF_Spell_Target_Type>(reader.get_char());
	reader.get_char();
	reader.get_char();
	reader.get_short();
	min_damage = reader.get_short();
	max_damage = reader.get_short();
	accuracy = reader.get_short();
	reader.get_short();
	reader.get_short();
	reader.get_char();
	hp = reader.get_short();
	reader.get_short();
	reader.get_char();
	reader.get_short();
	reader.get_short();
	reader.get_short();
	reader.get_short();
	reader.get_short();
	reader.get_short();
}

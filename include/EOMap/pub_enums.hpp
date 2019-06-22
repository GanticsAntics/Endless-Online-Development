#ifndef EOMAP_PUB_ENUMS_HPP
#define EOMAP_PUB_ENUMS_HPP

#include "eo_types.hpp"
//
enum class ECF_Class_Type : eo_char
{
	Melee = 0,
	Rogue = 1,
	Magic = 2,
	Archer = 3,
	Peasant = 4,
};

enum class EIF_Item_Size : eo_char
{
	Size1x1 = 0,
	Size1x2 = 1,
	Size1x3 = 2,
	Size1x4 = 3,
	Size2x1 = 4,
	Size2x2 = 5,
	Size2x3 = 6,
	Size2x4 = 7,
};

enum class EIF_Item_Special : eo_char
{
	Normal = 0,
	Rare = 1,
	Unique = 3,
	Lore = 4,
	Cursed = 5,
};

enum class EIF_Item_SubType : eo_char
{
	None = 0,
	Ranged = 1,
	Arrows = 2,
	Wings = 3,
	TwoHanded = 4,
};

enum class EIF_Item_Type : eo_char
{
	Static = 0,
	Money = 2,
	Heal = 3,
	Teleport = 4,
	Spell = 5,
	EXPReward = 6,
	StatReward = 7,
	SkillReward = 8,
	Key = 9,
	Weapon = 10,
	Shield = 11,
	Armor = 12,
	Hat = 13,
	Boots = 14,
	Gloves = 15,
	Accessory = 16,
	Belt = 17,
	Necklace = 18,
	Ring = 19,
	Armlet = 20,
	Bracer = 21,
	Beer = 22,
	EffectPotion = 23,
	HairDye = 24,
	CureCurse = 25,
};

enum class EMF_Effect : eo_char
{
	None = 0,
	HPDrain = 1,
	TPDrain = 2,
	Quake = 3,
};

enum class EMF_Tile_Spec : eo_char
{
	None = -1,
	Wall = 0,
	ChairDown = 1,
	ChairLeft = 2,
	ChairRight = 3,
	ChairUp = 4,
	ChairDownRight = 5,
	ChairUpLeft = 6,
	ChairAll = 7,
	Chest = 9,
	BankVault = 16,
	NPCBoundary = 17,
	MapEdge = 18,
	FakeWall = 19,
	Board1 = 20,
	Board2 = 21,
	Board3 = 22,
	Board4 = 23,
	Board5 = 24,
	Board6 = 25,
	Board7 = 26,
	Board8 = 27,
	Jukebox = 28,
	Jump = 29,
	Water = 30,
	SpecUnknown7 = 31,
	Arena = 32,
	AmbientSource = 33,
	Spikes1 = 34,
	Spikes2 = 35,
	Spikes3 = 36,
};

enum class EMF_Type : eo_char
{
	Default = 0,
	PK = 3,
};

enum class ENF_NPC_Type : eo_short
{
	NPC = 0,
	Passive = 1,
	Aggressive = 2,
	Shop = 6,
	Inn = 7,
	Bank = 9,
	Barber = 10,
	Guild = 11,
	Priest = 12,
	Law = 13,
	Skills = 14,
	Quest = 15,
};

enum class ESF_Spell_Target_Restrict : eo_char
{
	NPC = 0,
	Friendly = 1,
	Opponent = 2,
};

enum class ESF_Spell_Target_Type : eo_char
{
	Normal = 0,
	Self = 1,
	Group = 3,
};

enum class ESF_Spell_Type : eo_three
{
	Heal = 0,
	Damage = 1,
	Bard = 2,
};

#endif // EOMAP_PUB_ENUMS_HPP


#pragma once
#include "CharacterModel.h"
class Map_Player : public CharacterModel
{
	int FindWalkDirection(int dest_x, int dest_y);
public:
	std::string PlayerName = "";
	int x = 0;
	int y = 0;
	int destination_x = -1;
	int destination_y = -1;
	void Update(int FPS);
	/**
 * One type of item in a Characters inventory
 */
	struct Character_Item
	{
		short id;
		int amount;

		Character_Item() = default;
		Character_Item(short id, int amount) : id(id), amount(amount) { }
	};

	/**
	 * One spell that a Character knows
	 */
	struct Character_Spell
	{
		short id;
		unsigned char level;

		Character_Spell() = default;
		Character_Spell(short id, unsigned char level) : id(id), level(level) { }
	};
	void SetStance(PlayerStance m_Stance);
	void MovePlayer(int FPS, int dest_x, int dest_y);

	void Initialize(LPVOID* M_Game);
	int login_time;
	bool online;
	bool nowhere;
	unsigned int CharacterID;
	//AdminLevel admin;
	std::string guildname;
	std::string guildtag;
	std::string guildrank;
	std::string real_name;
	std::string title;
	std::string home;
	std::string fiance;
	std::string partner;
	unsigned char clas;
	short mapid;
	int fpscounter = 0;
	int moveFPS = 0;
	int WalkCounter = 0;
	//Direction direction;
	unsigned char level;
	int exp = 0;
	short hp, tp;
	short str, intl, wis, agi, con, cha;
	short adj_str, adj_intl, adj_wis, adj_agi, adj_con, adj_cha;
	short statpoints, skillpoints;
	short weight, maxweight;
	short karma;
	//SitState sitting;
	int hidden;
	int nointeract;
	bool whispers;
	int bankmax;
	int goldbank;
	int usage;
	int muted_until;
	short maxsp;
	short maxhp, maxtp;
	short accuracy, evade, armor;
	short mindam, maxdam;

	std::list<Character_Item> bank;

	std::list<Character_Spell> spells;
	int time = 0;
	int Deathcounter = 0;
	std::vector<BYTE> Damage;
	void DealDamage(int Damage);
	void PlayerKill();
	bool isattacked = false;
	void Map_PlayerRender(ID3DXSprite* _Sprite, int x, int y, float depth, D3DCOLOR _Color = D3DCOLOR_ARGB(255, 255, 255, 255));
	Map_Player();
	~Map_Player();
};


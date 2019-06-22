#pragma once
#include <d3d9types.h>
#include <d3d9types.h>
class Map_NPC
{
	int FindWalkDirection(int dest_x, int dest_y);
public:
	Map_NPC();
	int Index;
	int ID;
	int x, y, direction;
	int FrameID = 0;
	int FrameCounter = 0;
	int HP;
	int MaxHP;
	int destination_x = -1;
	int destination_y = -1;
	int moveFPS = 0;
	int yoffset = 0;
	int xoffset = 0;
	int WalkCounter = 0;

	bool isattacked = false;
	int time = 0;

	int Deathcounter = 0;
	std::vector<BYTE> Damage;

	void NPCKill();
	enum NPC_Stance
	{
		Standing,
		Walking,
		Attacking,
		Dead
	};
	//D3DCOLOR_ARGB Color;
	NPC_Stance Stance;
	void Initialize(LPVOID* m_game);
	void SetStance(NPC_Stance m_Stance);
	void MoveNPC(int FPS, int DestX,int DestY);
	void DealDamage(short HpLeft, int damage);
	void Update(int FPS);
	void Render(ID3DXSprite* _Sprite, int x, int y, float depth, D3DCOLOR m_color = D3DCOLOR_ARGB(255,255,255,255));
	~Map_NPC();
};


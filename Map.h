#pragma once
#include "World.h"
#include "include/EOMap/eo_data.hpp"
#include "include/EOMap/eo_stream.hpp"
#include "Map_Player.h"
#include "Map_NPC.h"
#include <mutex>   
#include <map>
class Map
{
	//void ClearPlayerQueue();
	//void AddPlayers();
public:
	std::mutex ThreadLock;
	Map();
	World* world;
	ID3DXSprite* Sprite;
	ID3DXSprite* m_OverlaySprite;
	EMF_File* newemf;
	
	Full_EMF m_emf;
	//std::map<int, int> test;
	std::map<int, Map_Player*> m_Players;
	std::map<int, Map_NPC*> m_NPCs;
	std::string MainPlayerName = "";
	bool IsVisible = false;
	int MapID = 0;
	int MapAnimIndex = 0;
	const char* m_map_filename = nullptr;
	int xsub = 0, ysub = 0, xoff = 0, yoff= 0;
	int	xpos = 0, ypos = 0;
	struct Map_Item
	{
		public:
			unsigned short ItemID = -1;
			unsigned char x = -1;
			unsigned char y = -1;
			unsigned int amount = -1;
	};
	std::map<int, Map_Item> m_Items;
	void AddItem(int m_Index, unsigned short m_ItemID, unsigned char m_x, unsigned char m_y, unsigned int m_amount)
	{
		this->ThreadLock.lock();
		Map_Item newitem;
		newitem.amount = m_amount;
		newitem.x = m_x;
		newitem.y = m_y;
		newitem.ItemID = m_ItemID;
		this->m_Items[m_Index] = newitem;
		this->ThreadLock.unlock();
	}
	void AddItem(int Index, Map_Item newitem)
	{
		this->ThreadLock.lock();
		this->m_Items[Index] = newitem;
		this->ThreadLock.unlock();
	}
	void RemoveItem(int Index) { this->ThreadLock.lock(); this->m_Items.erase(Index); this->ThreadLock.unlock();
	}
	int FindDepthOffset(int X, int Y, int Width, int Height);
	void OnKeyPress(WPARAM args);
	void RemovePlayer(int ID);
	void AddPlayer(Map_Player* m_Player);
	void RemoveNPC(int ID);
	void AddNPC(Map_NPC* Map_NPC);
	void KillNPC(int ID);
	void ClearMap();
	void ChangeAvatar(int ID, short ShoeID, short HatID, short WeaponID, short ShieldID, short ArmorID);
	void WalkPlayer(int ID, int direction , int FromX, int FromY);
	void WalkGameCharacter(int ID, int direction, int _X, int _Y);
	void WalkNPC(int ID, int direction, int FromX, int FromY);
	void Initialize(World* _World, IDirect3DDevice9Ptr m_Device, LPVOID* m_game);
	void LoadMap(int ID);
	void Do_Open(const char* filename);
	void Render();
	void Update();
	virtual ~Map();
};


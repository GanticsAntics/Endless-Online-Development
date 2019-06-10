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
	EMF_File* newemf;
	
	Full_EMF m_emf;
	//std::map<int, int> test;
	std::map<int, Map_Player*> m_Players;
	std::map<int, Map_NPC*> m_NPCs;
	std::string MainPlayerName = "";
	bool IsVisible = false;
	int MapID = 0;
	const char* m_map_filename = nullptr;
	int xsub = 0, ysub = 0, xoff = 0, yoff= 0;
	int	xpos = 0, ypos = 0;
	void OnKeyPress(WPARAM args);
	void RemovePlayer(int ID);
	void AddPlayer(Map_Player* m_Player);
	void RemoveNPC(int ID);
	void AddNPC(Map_NPC* Map_NPC);
	void KillNPC(int ID);
	void ClearMap();
	void WalkPlayer(int ID, int direction , int FromX, int FromY);
	void WalkNPC(int ID, int direction, int FromX, int FromY);
	void Initialize(World* _World, IDirect3DDevice9Ptr m_Device, LPVOID* m_game);
	void LoadMap(int ID);
	void Do_Open(const char* filename);
	void Render();
	void Update();
	virtual ~Map();
};


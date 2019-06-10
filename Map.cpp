#include "stdafx.h"
#include "Map.h"
#include "include/EOMap/Util/cio/cio.hpp"
#include "Game.h"
#include "Map_Player.h"
#include "Send/SFace.h"
#include "Send/SWalk.h"
#include "Send/SAttack.h"
#include "Send/SRefresh.h"
IDirect3DDevice9* map_d3d_Device;
Game* map_game;

Map::Map()
{

}
void TextPadTo(std::wstring& str, const size_t num, const char paddingChar = ' ')
{
	if (num > str.size())
		str.insert(0, num - str.size(), paddingChar);
}

void Map::Do_Open(const char* filename)
{
	m_map_filename = filename;

	cio::stream file(filename);
	if (!file)
	{
		World::DebugPrint("Failed to load Map file");
		this->IsVisible = false;
		return;
	}
	file.seek_reverse(0);
	long filesize = file.tell();
	file.seek(0x03);
	char checkrid[4];
	file.read(checkrid, 4);
	std::array<eo2_byte, 4U> RID;
	for (int i = 0; i < 4; i++)
	{
		RID[i] = checkrid[i];
	}
	file.seek(0);
	shared_ptr<char[]> data(new char[filesize]);
	file.read(data.get(), filesize);
	

	EO_Stream_Reader reader(data.get(), filesize);
	m_emf = Full_EMF{};
	m_emf.unserialize(reader);
	m_emf.rid = RID;
	m_emf.MapFileSize = filesize;
	this->IsVisible = true;
}
void Map::LoadMap(int ID)
{
	int mapid = ID;
	this->MapID = ID;
	wchar_t* st = new wchar_t[8];
	_itow(mapid, st, 10);
	this->xsub = 0;
	this->ysub = 0;

	wchar_t* buffer = new wchar_t[1024];
	GetCurrentDirectory(1024, buffer);

	std::wstring Path = L"";
	Path += buffer;
	Path += L"\\Maps\\";
	wstring NumberPath = st;
	TextPadTo(NumberPath, 5, '0');
	Path += NumberPath += L".emf";

	std::string str_proc(Path.begin(), Path.end());
	this->Do_Open(str_proc.c_str());

	this->xoff = 0;
	this->yoff = 0;
}
int MapID = 5;
void Map::Initialize(World* _world, IDirect3DDevice9Ptr m_Device, LPVOID* m_game)
{
	world = _world;
	map_d3d_Device = m_Device;
	D3DXCreateSprite(map_d3d_Device, &this->Sprite);
	map_game = (Game*)m_game;

	int mapid = 5;
	wchar_t* st = new wchar_t[8];
	_itow(mapid, st, 10);

	wchar_t* buffer = new wchar_t[1024];
	GetCurrentDirectory(1024, buffer);

	std::wstring Path = L"";
	Path += buffer;
	Path += L"\\Maps\\";
	wstring NumberPath = st;
	TextPadTo(NumberPath, 5, '0');
	Path += NumberPath += L".emf";
	
	// your new String
	std::string str_proc(Path.begin(), Path.end());
	this->Do_Open(str_proc.c_str());
	//this->newemf = new EMF_File();
	/*this->m_Players.resize(1);
	this->m_Players[0] = new Map_Player();
	this->m_Players[0]->Initialize(m_game);
	this->m_Players[0]->x = 10;
	this->m_Players[0]->y = 4;
	this->m_Players[0]->ArmorID = (std::rand() % 25);
	this->m_Players[0]->HairCol = (std::rand() % 5);
	this->m_Players[0]->HairStyle = (std::rand() % 20);
	this->m_Players[0]->WeaponID = (std::rand() % 25);
	this->m_Players[0]->ShoeID = (std::rand() % 25);
	this->m_Players[0]->SkinCol = (std::rand() % 5);*/
}
//std::vector<int> PlayerRemoveQueue;
void Map::ClearMap()
{
	this->ThreadLock.lock();
	for (auto p : m_Players)
	{
		delete p.second;
	}
	for (auto p : m_NPCs)
	{
		delete  p.second;
	}
	m_Players.clear();
	m_NPCs.clear();
	this->ThreadLock.unlock();
}
int map_UpdateFPS = 0;
void Map::Update()
{
	map_UpdateFPS++;
	if (map_UpdateFPS > map_game->FPS / 4)
	{
		this->ThreadLock.lock();
		if (!IsVisible || World::WorldCharacterID == -1)
		{
			this->ThreadLock.unlock();
			return;
		}

		for (std::map<int, Map_Player*>::iterator player = this->m_Players.begin(); player != m_Players.end(); ++player)
		{
			player->second->Update(map_game->FPS);
		}
		for (std::map<int, Map_NPC*>::iterator NPC = this->m_NPCs.begin(); NPC != m_NPCs.end(); ++NPC)
		{
			NPC->second->Update(map_game->FPS);
		}

		this->ThreadLock.unlock();
	}
}

void Map::RemovePlayer(int ID)
{
	this->ThreadLock.lock();
	this->m_Players.erase(ID);
	this->ThreadLock.unlock();
}

void Map::AddPlayer(Map_Player* m_Player)
{
	this->ThreadLock.lock();
	this->m_Players[m_Player->ID] = m_Player;
	this->ThreadLock.unlock();
}
void Map::KillNPC(int ID)
{
	this->ThreadLock.lock();
	this->m_NPCs.erase(ID);
	this->ThreadLock.unlock();
}
void Map::RemoveNPC(int ID)
{
	this->ThreadLock.lock();
	this->m_NPCs.erase(ID);
	this->ThreadLock.unlock();
}

void Map::AddNPC(Map_NPC * m_NPC)
{
	this->ThreadLock.lock();
	this->m_NPCs[m_NPC->Index] = m_NPC;
	this->ThreadLock.unlock();
}

void Map::WalkPlayer(int ID, int direction, int DestX, int DestY)
{
	int m_PlayerID = ID;
	int FromX = DestX;
	int FromY = DestY;
	if (m_PlayerID >= 0)
	{
		if (direction == 0)
		{
			///Down
			//this->m_Players[m_PlayerID]->direction = 0;
			FromY--;
		}
		if (direction == 1)
		{
			///Left
			//this->m_Players[m_PlayerID]->direction = 1;
			FromX++;
		}
		if (direction == 2)
		{
			///UP
			//this->m_Players[m_PlayerID]->direction = 3;
			//FromX++;
			FromY++;
		}
		if (direction == 3)
		{
			///Right
			//this->m_Players[m_PlayerID]->direction = 2;
			FromX--;
		}
		//std::string str = "Walk Request From : " + std::to_string(FromX) + " , " + std::to_string(FromY);
		//World::DebugPrint(str.c_str());

		this->m_Players[m_PlayerID]->x = FromX;
		this->m_Players[m_PlayerID]->y = FromY;
		this->m_Players[m_PlayerID]->MovePlayer(map_game->FPS, DestX, DestY);
		this->m_Players[m_PlayerID]->SetStance(CharacterModel::PlayerStance::Walking);
	}
}

void Map::WalkNPC(int ID, int direction, int DestX, int DestY)
{
	int m_NPCID = ID;
	int FromX = DestX;
	int FromY = DestY;
	if (m_NPCID >= 0)
	{
		if (direction == 0)
		{
			FromY--;
		}
		if (direction == 1)
		{
			FromX++;
		}
		if (direction == 2)
		{
			FromY++;
		}
		if (direction == 3)
		{
			FromX--;
		}

		this->m_NPCs[m_NPCID]->x = FromX;
		this->m_NPCs[m_NPCID]->y = FromY;
		this->m_NPCs[m_NPCID]->SetStance(Map_NPC::NPC_Stance::Walking);
		this->m_NPCs[m_NPCID]->MoveNPC(map_game->FPS, DestX, DestY);
	}
}

void Map::OnKeyPress(WPARAM args)
{
	int m_playerID = World::WorldCharacterID;
	int scale = 1;
	switch (args)
	{
		//case(VK_SPACE):
		{
			/*MapID++;
			this->xpos = 0;
			this->ypos = 0;
			LoadMap(MapID);
			this->m_Players[0]->x = 10;
			this->m_Players[0]->y = 4;
			break;*/
		}
		case(VK_NUMPAD0):
		{
			this->m_Players[0]->SetStance(CharacterModel::PlayerStance::Standing);
			break;
		}
		case(VK_NUMPAD1):
		{
			if (this->m_Players[0]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[0]->SetStance(CharacterModel::PlayerStance::Walking);
			}
			break;
		}
		case(VK_CONTROL):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[m_playerID]->SetStance(CharacterModel::PlayerStance::BluntAttacking);
				SAttack::SendAttack(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);

			}
			break;
		}
		case(VK_NUMPAD3):
		{
			if (this->m_Players[0]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[0]->SetStance(CharacterModel::PlayerStance::BowAttacking);
			}
			break;
		}
		case(VK_NUMPAD4):
		{
			if (this->m_Players[0]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[0]->SetStance(CharacterModel::PlayerStance::Spelling);
			}
			break;
		}
		case(VK_NUMPAD5):
		{
			this->m_Players[0]->SetStance(CharacterModel::PlayerStance::ChairSitting);
			break;
		}
		case(VK_F3):
		{
			SRefresh::RequestRefresh(map_game->world->connection->ClientStream, (LPVOID)map_game);
			break;
		}
		case(VK_F11):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::GroundSitting)
			{
				this->m_Players[m_playerID]->SetStance(CharacterModel::PlayerStance::Standing);
			}
			else if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[m_playerID]->SetStance(CharacterModel::PlayerStance::GroundSitting);
			}
			break;
		}
		case(VK_NUMPAD7):
		{
			this->m_Players[0]->direction = 0;
			break;
		}
		case(VK_NUMPAD8):
		{
			this->m_Players[0]->direction = 1;			
			break;
		}
		case(VK_NUMPAD9):
		{
			this->m_Players[0]->direction = 3;
			break;
		}
		case(VK_BACK):
		{
			/*this->m_Players[0]->Gender = (std::rand() % 2);
			this->m_Players[0]->ArmorID = (std::rand() % 25);
			this->m_Players[0]->HairCol = (std::rand() % 5);
			this->m_Players[0]->HairStyle = (std::rand() % 20);
			this->m_Players[0]->WeaponID = (std::rand() % 66);
			this->m_Players[0]->ShoeID = (std::rand() % 25);
			this->m_Players[0]->ShieldID = (std::rand() % 25);
			this->m_Players[0]->SkinCol = (std::rand() % 2);*/
				break;
		}
		case(VK_SPACE):
		{

			
			//this->m_NPCs[0]->MoveNPC(map_game->FPS, this->m_NPCs[0]->x, this->m_NPCs[0]->y);
			//this->m_NPCs[0]->SetStance(Map_NPC::NPC_Stance::Walking);
			break;
		}
		case(VK_F1):
		{

			this->m_NPCs[0]->SetStance(Map_NPC::NPC_Stance::Attacking);
			//this->m_NPCs[0]->MoveNPC(map_game->FPS, this->m_NPCs[0]->x, this->m_NPCs[0]->y);
			//this->m_NPCs[0]->SetStance(Map_NPC::NPC_Stance::Walking);
			break;
		}
		case(VK_LEFT):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[m_playerID]->MovePlayer(map_game->FPS, this->m_Players[m_playerID]->x - 1, this->m_Players[m_playerID]->y);
				this->m_Players[m_playerID]->SetStance(CharacterModel::PlayerStance::Walking);
				//SFace::SendFace(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);
				SWalk::SendWalk(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, this->m_Players[m_playerID]->x - 1, this->m_Players[m_playerID]->y, (LPVOID)map_game);
				
			}
			break;
		}
		case(VK_UP):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[m_playerID]->MovePlayer(map_game->FPS, this->m_Players[m_playerID]->x, this->m_Players[m_playerID]->y - 1);
				this->m_Players[m_playerID]->SetStance(CharacterModel::PlayerStance::Walking);
				//SFace::SendFace(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);
				SWalk::SendWalk(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, this->m_Players[m_playerID]->x, this->m_Players[m_playerID]->y - 1, (LPVOID)map_game);

			}
			break;
		}
		case(VK_RIGHT):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[m_playerID]->MovePlayer(map_game->FPS, this->m_Players[m_playerID]->x + 1, this->m_Players[m_playerID]->y);
				this->m_Players[m_playerID]->SetStance(CharacterModel::PlayerStance::Walking);
				//SFace::SendFace(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);
				SWalk::SendWalk(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, this->m_Players[m_playerID]->x+1, this->m_Players[m_playerID]->y, (LPVOID)map_game);

			}
			break;
		}
		case(VK_DOWN):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[m_playerID]->MovePlayer(map_game->FPS, this->m_Players[m_playerID]->x, this->m_Players[m_playerID]->y + 1);
				this->m_Players[m_playerID]->SetStance(CharacterModel::PlayerStance::Walking);
				//SFace::SendFace(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);
				SWalk::SendWalk(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, this->m_Players[m_playerID]->x, this->m_Players[m_playerID]->y + 1, (LPVOID)map_game);

			}
			break;
		}
	}
}

int Map_RenderFPS = 0;
void Map::Render()
{
	this->ThreadLock.lock();
	if (!IsVisible || World::WorldCharacterID < 0)
	{
		this->ThreadLock.unlock();
		return;
	}
	int PlayerIndex = World::WorldCharacterID;
	///Tempcommandtofollowplayer
	this->xpos = this->m_Players[PlayerIndex]->x;
	this->ypos = this->m_Players[PlayerIndex]->y;
	if (this->m_Players[PlayerIndex]->direction == 0 || this->m_Players[PlayerIndex]->direction == 3)
	{
		this->xoff = this->m_Players[PlayerIndex]->xoffset + (this->xpos * 32) - (this->ypos * 32) -280;
		this->yoff = this->m_Players[PlayerIndex]->yoffset + (this->xpos * 16) + (this->ypos * 16) -170;
	}
	else 
	{
		this->xoff = -this->m_Players[PlayerIndex]->xoffset + (this->xpos * 32) - (this->ypos * 32) - 280;
		this->yoff = this->m_Players[PlayerIndex]->yoffset + (this->xpos * 16) + (this->ypos * 16) - 170;
	}
	this->ThreadLock.unlock();
	///Endshittycommand
	struct LayerInfo
	{
		int file;
		int xoff;
		int yoff;
		float depth;
	};
	constexpr float ep = 0.0001f;  // gap between depth of each tile on a layer
	constexpr float epi = 0.00001f; // gap between each interleaved layer

	static constexpr LayerInfo layer_info[9] = {
		{ 3,    0,   0, 1.0f - epi * 0 }, // Ground
		{ 4,    0,   0, 0.8f - epi * 0 }, // Objects
		{ 5,   32,   64, 0.7f - epi * 0 }, // Overlay
		{ 6,    0,   0, 0.8f - epi * 1 }, // Down Wall
		{ 6,   32,   0, 0.8f - epi * 2 }, // Right Wall
		{ 7,   32, -64, 0.7f - epi * 1 }, // Roof
		{ 3,   32, -32, 0.7f - epi * 2 }, // Top
		{ 22, -54 + 32, -42 + 30, 0.7f - epi * 0 }, // Shadow
		{ 5,    0,   0, 0.7f - epi * 3 }, // Overlay 2
	};
	auto&& emfh = m_emf.header;
	
	float depth = layer_info[0].depth;
	auto next_depth = [&depth, ep]() { return depth -= ep; };
	
	this->Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	
	for (int i = 0; i < (emfh.width -1) + (emfh.height - 1); ++i)
	{
		int x, y;

		if (i < (emfh.height - 1))
		{
			x = 0;
			y = i;
		}
		else
		{
			x = i - (emfh.height - 1);
			y = (emfh.height - 1);
		}

		for (next_depth(); y >= 0 && x <= (emfh.width -1); --y, ++x, next_depth())
		{
			int xoffs = layer_info[0].xoff - xoff;
			int yoffs = layer_info[0].yoff - yoff;

			int tilex = xoffs + (x * 32) - (y * 32);
			int tiley = yoffs + (x * 16) + (y * 16);
			short tile = 0;
			tile = m_emf.gfx(x, y)[0];
	
			if (tilex < -64 || tiley < -32
				|| tilex > 700 || tiley > 500)
				continue;
			if (tile > 0)
			{
				map_game->Draw(this->Sprite, map_game->resource->CreateTexture(3, tile, true).Texture, tilex, tiley,depth, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				if (emfh.fill_tile > 0)
				{
					map_game->Draw(this->Sprite, map_game->resource->CreateTexture(3, emfh.fill_tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}
			if (map_game->MapCursor.x == x && map_game->MapCursor.y == y)
			{
				next_depth();
				map_game->MapCursor.Render(this->Sprite, depth);
			}
		}
	}	

	for (int layer = 1; layer < 7; ++layer)
	{
		depth = layer_info[layer].depth;
		for (int i = 0; i < (emfh.width - 1) + (emfh.height - 1); ++i)
		{
			int x, y;

			if (i < (emfh.height - 1))
			{
				x = 0;
				y = i;
			}
			else
			{
				x = i - (emfh.height - 1);
				y = (emfh.height - 1);
			}

			for (next_depth(); y >= 0 && x <= (emfh.width - 1); --y, ++x, next_depth())
			{
				int xoffs = layer_info[layer].xoff - xoff;
				int yoffs = layer_info[layer].yoff - yoff;

				int tilex = xoffs + (x * 32) - (y * 32);
				int tiley = yoffs + (x * 16) + (y * 16);
				short tile = 0;
				tile = m_emf.gfx(x, y)[layer];

				if (tilex < -240 || tiley < -320
					|| tilex > 700 + 240|| tiley > 500 + 320)
					continue;

				if (tile > 0)
				{
					D3DXIMAGE_INFO tile_gfx = map_game->resource->GetImageInfo(layer_info[layer].file, tile, true);
					int tile_w = tile_gfx.Width;
					int tile_h = tile_gfx.Height;
					tilex -= tile_w / (1 + (layer == 1)) - 32;
					tiley -= tile_h - 32;

					map_game->Draw(this->Sprite, map_game->resource->CreateTexture(layer_info[layer].file, tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				if (layer == 1)
				{
					this->ThreadLock.lock();
					
					for (std::map<int, Map_Player*>::iterator player = this->m_Players.begin(); player != m_Players.end(); ++player)
					{
						if(player->second->x == x && player->second->y == y)
						{
							next_depth();
							int xoffsp = layer_info[layer].xoff - xoff;
							int yoffsp = layer_info[layer].yoff - yoff;
							int tilexp = xoffsp + (x * 32) - (y * 32);
							int tileyp = yoffsp + (x * 16) + (y * 16);
							player->second->Render(this->Sprite, tilexp  + 24, tileyp - 40, depth);
						}
					}

					for (std::map<int, Map_NPC*>::iterator NPC = this->m_NPCs.begin(); NPC != m_NPCs.end(); ++NPC)
					{
						if (NPC->second->x == x && NPC->second->y == y)
						{
							next_depth();
							int xoffsp = layer_info[layer].xoff - xoff;
							int yoffsp = layer_info[layer].yoff - yoff;
							int tilexp = xoffsp + (x * 32) - (y * 32);
							int tileyp = yoffsp + (x * 16) + (y * 16);
							NPC->second->Render(this->Sprite, tilexp + 24, tileyp - 40, depth);
						}
					}
					this->ThreadLock.unlock();
				}
			}
		}
	}
	for (int i = 0; i < (emfh.width - 1) + (emfh.height - 1); ++i)
	{
		int x, y;
		depth = layer_info[7].depth;
		if (i < (emfh.height - 1))
		{
			x = 0;
			y = i;
		}
		else
		{
			x = i - (emfh.height - 1);
			y = (emfh.height - 1);
		}

		for (next_depth(); y >= 0 && x <= (emfh.width - 1); --y, ++x, next_depth())
		{
			int xoffs = layer_info[7].xoff - xoff;
			int yoffs = layer_info[7].yoff - yoff;

			int tilex = xoffs + (x * 32) - (y * 32);
			int tiley = yoffs + (x * 16) + (y * 16);
			short tile = 0;
			tile = m_emf.gfx(x, y)[7];

			if (tilex < -64 || tiley < -32
				|| tilex > 700 || tiley > 500)
				continue;
			if (tile > 0)
			{
				map_game->Draw(this->Sprite, map_game->resource->CreateTexture(layer_info[7].file, tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(50, 255, 255, 255));
			}
		}
	}

	this->world->RenderTextBoxes(this->Sprite, map_game->Stage, map_game->SubStage);
	this->Sprite->End();

}
Map::~Map()
{
}

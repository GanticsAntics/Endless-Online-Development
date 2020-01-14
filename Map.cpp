#include "stdafx.h"
#include "Map.h"
#include "include/EOMap/Util/cio/cio.hpp"
#include "Game.h"
#include "Map_Player.h"
#include "Send/SFace.h"
#include "Send/SWalk.h"
#include "Send/SAttack.h"
#include "Send/SRefresh.h"
#include "Send/SItem.h"
#include "Send/SDoor.h"
#include "Send/SWelcome.h"
IDirect3DDevice9* map_d3d_Device;
Game* map_game;
bool rendering = true;
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
	this->IsVisible = false;
	if (!file)
	{
		World::DebugPrint("Failed to load Map file");
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
	std::shared_ptr<char[]> data(new char[filesize]);
	file.read(data.get(), filesize);
	
	
	EO_Stream_Reader reader(data.get(), filesize);
	this->ThreadLock.lock();
	m_emf = Full_EMF{};
	m_emf.unserialize(reader);
	m_emf.rid = RID;
	m_emf.MapFileSize = filesize;
	//this->IsVisible = true;
	this->ThreadLock.unlock();
}
void Map::LoadMap(int ID)
{
	ClearMap();
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
	MapAnimIndex = 0;
	this->xoff = 0;
	this->yoff = 0;
	this->ThreadLock.lock();
	this->MakeLUTs(m_emf.header.width, m_emf.header.height);
	this->ThreadLock.unlock();
}

void Map::Initialize(World* _world, IDirect3DDevice9Ptr m_Device, LPVOID* m_game)
{
	world = _world;
	map_d3d_Device = m_Device;
	D3DXCreateSprite(map_d3d_Device, &this->Sprite);
	D3DXCreateSprite(map_d3d_Device, &m_OverlaySprite);
	
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
	
}
//std::vector<int> PlayerRemoveQueue;
void Map::ClearMap()
{
	this->ThreadLock.lock();
	Map_Player* MainPlayer = m_Players[World::WorldCharacterID];
	
	for (auto p : m_Players)
	{
		if (p.first != World::WorldCharacterID)
		{
			delete p.second;
		}
	}
	for (auto p : m_NPCs)
	{
		delete  p.second;
	}
	m_Players.clear();
	if (MainPlayer)
	{
		MainPlayer->x = 0;
		MainPlayer->y = 0;
		MainPlayer->destination_x = -1;
		MainPlayer->destination_y = -1;
		MainPlayer->xoffset = 0;
		MainPlayer->yoffset = 0;
		MainPlayer->WalkCounter = 0;
		MainPlayer->SetStance(Map_Player::PlayerStance::Standing);
	}
	m_Players[World::WorldCharacterID] = MainPlayer;
	m_NPCs.clear();
	m_Items.clear();
	this->ThreadLock.unlock();
}
int map_UpdateFPS = 0;
void Map::Update()
{
	map_UpdateFPS++;
	if (map_UpdateFPS > map_game->FPS / 4)
	{
		this->MapAnimIndex++;
		if (this->MapAnimIndex > 4)
		{
			this->MapAnimIndex = 0;
		}
		map_UpdateFPS = 0;
	}
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

		for (std::map<int, Map_NPC*>::iterator NPC = this->m_NPCs.begin(); NPC != m_NPCs.end(); ++NPC)
		{
			if (NPC->second->Deathcounter > (map_game->FPS / 2.5))
			{
				this->RemoveNPC(NPC->first);
				break;
			}
		}
}

void Map::RemovePlayer(int ID)
{
	this->ThreadLock.lock();
	this->m_Players.erase(ID);
	this->ThreadLock.unlock();
}

void Map::ChangeAvatar(int ID, short ShoeID, short HatID, short WeaponID, short ShieldID, short ArmorID)
{
	this->ThreadLock.lock();
	this->m_Players[ID]->ShoeID = ShoeID;
	this->m_Players[ID]->HatID = HatID;
	this->m_Players[ID]->WeaponID = WeaponID;
	this->m_Players[ID]->ShieldID = ShieldID;
	this->m_Players[ID]->ArmorID = ArmorID;
	this->ThreadLock.unlock();
}
void Map::AddPlayer(Map_Player* m_Player)
{
	m_Player->Initialize((LPVOID*)map_game);
	this->ThreadLock.lock();
	this->m_Players[m_Player->ID] = m_Player;
	this->ThreadLock.unlock();
}
void Map::KillNPC(int ID)
{
	this->ThreadLock.lock();
	this->m_NPCs.at(ID)->NPCKill();
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
		if (m_Players.count(m_PlayerID) > 0)
		{
			this->ThreadLock.lock();
			this->m_Players[m_PlayerID]->x = FromX;
			this->m_Players[m_PlayerID]->y = FromY;
			this->m_Players[m_PlayerID]->MovePlayer(map_game->FPS, DestX, DestY);
			this->m_Players[m_PlayerID]->SetStance(CharacterModel::PlayerStance::Walking);
			this->ThreadLock.unlock();
		}
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
		if (m_NPCs.count(m_NPCID) > 0 )
		{
			this->ThreadLock.lock();
			if (DestX > this->m_emf.header.width || DestY > this->m_emf.header.height)
			{
				//this->RemoveNPC(m_NPCID);
				this->ThreadLock.unlock();
				return;
			}
			this->m_NPCs[m_NPCID]->x = FromX;
			this->m_NPCs[m_NPCID]->y = FromY;
			this->m_NPCs[m_NPCID]->SetStance(Map_NPC::NPC_Stance::Walking);
			this->m_NPCs[m_NPCID]->MoveNPC(map_game->FPS, DestX, DestY);
			this->ThreadLock.unlock();
		}
	}
}
void Map::WalkGameCharacter(int ID, int direction, int _X, int _Y)
{
	this->ThreadLock.lock();
	Full_EMF::TileMeta tmeta;
	if(_X >= this->m_emf.header.width|| _Y >= this->m_emf.header.height|| _X < 0 || _Y < 0)
	{
		this->ThreadLock.unlock();
		return;
	}
	tmeta = this->m_emf.meta(_X, _Y);
	
	if (tmeta.warp.door == 1)
	{
		SDoor::SendDoorOpen(map_game->world->connection->ClientStream, _X, _Y, (LPVOID)map_game);

	}
	
	if (tmeta.spec == EMF_Tile_Spec::None || (tmeta.spec >= EMF_Tile_Spec::NPCBoundary && tmeta.spec <= EMF_Tile_Spec::FakeWall) || (tmeta.spec >= EMF_Tile_Spec::Jump))
	{
		this->m_Players[ID]->MovePlayer(map_game->FPS, _X, _Y);
		this->m_Players[ID]->SetStance(CharacterModel::PlayerStance::Walking);
		SWalk::SendWalk(map_game->world->connection->ClientStream, this->m_Players[ID]->direction, _X, _Y, (LPVOID)map_game);
	}

	this->ThreadLock.unlock();

}
clock_t m_arrowstartkeytimer, m_arrowendkeytimer;
clock_t m_standkeytimer, m_standkeyendtimer;
void Map::OnKeyPress(WPARAM args)
{
	int m_playerID = World::WorldCharacterID;
	int scale = 1;
	int delay = 100;
	int delay2 = 350;
	m_arrowendkeytimer = clock();
	m_standkeyendtimer = clock();
	switch (args)
	{
		case(VK_CONTROL):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				this->m_Players[m_playerID]->SetStance(CharacterModel::PlayerStance::BluntAttacking);
				SAttack::SendAttack(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);

			}
			break;
		}
		case(VK_F3):
		{
			if ((m_arrowendkeytimer - m_arrowstartkeytimer) > delay)
			{
				m_arrowstartkeytimer = clock();
				SRefresh::RequestRefresh(map_game->world->connection->ClientStream, (LPVOID)map_game);
			}
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
		case(VK_LEFT):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				if (this->m_Players[m_playerID]->direction != 3 )
				{
					if ((m_standkeyendtimer - m_standkeytimer) > delay2)
					{
						m_standkeytimer = clock();
						m_arrowstartkeytimer = clock();
						this->m_Players[m_playerID]->direction = 3;
						SFace::SendFace(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);
					}
				}
				else if((m_arrowendkeytimer - m_arrowstartkeytimer) > delay)
				{
					WalkGameCharacter(m_playerID, this->m_Players[m_playerID]->direction, this->m_Players[m_playerID]->x - 1, this->m_Players[m_playerID]->y);
				}
			}
			break;
		}
		case(VK_UP):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				if (this->m_Players[m_playerID]->direction != 1)
				{
					if ((m_standkeyendtimer - m_standkeytimer) > delay2)
					{
						m_standkeytimer = clock();
						m_arrowstartkeytimer = clock();
						this->m_Players[m_playerID]->direction = 1;
						SFace::SendFace(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);
					}
				}
				else if ((m_arrowendkeytimer - m_arrowstartkeytimer) > delay)
				{
					WalkGameCharacter(m_playerID, this->m_Players[m_playerID]->direction, this->m_Players[m_playerID]->x , this->m_Players[m_playerID]->y - 1);
				}
			}
			break;
		}
		case(VK_RIGHT):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				if (this->m_Players[m_playerID]->direction != 2)
				{
					if ((m_standkeyendtimer - m_standkeytimer) > delay2)
					{
						m_arrowstartkeytimer = clock();
						m_standkeytimer = clock();
						this->m_Players[m_playerID]->direction = 2;
						SFace::SendFace(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);
					}
				}
				else if ((m_arrowendkeytimer - m_arrowstartkeytimer) > delay)
				{
					WalkGameCharacter(m_playerID, this->m_Players[m_playerID]->direction, this->m_Players[m_playerID]->x + 1, this->m_Players[m_playerID]->y);
				}
			}
			break;
		}
		case(VK_DOWN):
		{
			if (this->m_Players[m_playerID]->Stance == CharacterModel::PlayerStance::Standing)
			{
				if (this->m_Players[m_playerID]->direction != 0)
				{
					if ((m_standkeyendtimer - m_standkeytimer) > delay2)
					{
						m_arrowstartkeytimer = clock();
						m_standkeytimer = clock();
						this->m_Players[m_playerID]->direction = 0;
						SFace::SendFace(map_game->world->connection->ClientStream, this->m_Players[m_playerID]->direction, (LPVOID)map_game);
					}
				}
				else if ((m_arrowendkeytimer - m_arrowstartkeytimer) > delay)
				{
					WalkGameCharacter(m_playerID, this->m_Players[m_playerID]->direction, this->m_Players[m_playerID]->x , this->m_Players[m_playerID]->y + 1);
				}
			}
			break;
		}
	}
}

void Map::MakeLUTs(int _Width, int _Height)
{
	this->OrderLUT = std::vector<Coord>(_Width * _Height);

	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;

	LUTMap.clear();
	LUTMap.resize(_Width);

	for (i = 0; i < LUTMap.size(); i++)
	{
		LUTMap[i].resize(_Height);
	}

	for (i = 0; i < _Width * _Height; ++i)
	{
		OrderLUT[i].x = x;
		OrderLUT[i].y = y;
		LUTMap[x][y] = i;
		x++;
		y--;
		if (y == -1 || x > _Width-1)
		{
			j++;
			y = j;
			x = 0;
			if (j > _Height-1)
			{
				y = _Height - 1;
				x = j - (_Height - 1);
			}
		}
	}
}

int Map_RenderFPS = 0;
///Endshittycommand
struct LayerInfo
{
	int file;
	int xoff;
	int yoff;
	float depth;
};

int Map::FindDepthOffset(int X, int Y, int Width, int Height)
{
	int XSequence = (X * (X + 1) / 2 + 1);
	int YSequence = (X + Y) * (Y + 1) - (pow(Y, 2) + (Y)-1 - floor(((Y)-1) / 2));
	if (Y == 0) { YSequence--; }

	int halfsize = (Width + Height) / 2;
	if (X + Y > halfsize)
	{
		return XSequence + (Y) * ((Y)) / 2 + YSequence - std::pow((Y - (Height / 2)) + (X - (Width / 2)), 2);
	}
	else
	{
		return XSequence + (Y) * ((Y)) / 2 + YSequence;
	}

}
void Map::Render()
{
	constexpr float ep = 0.0001f;  // gap between depth of each tile on a layer
	constexpr float epi = 0.00001f; // gap between each interleaved layer
	static constexpr LayerInfo layer_info[9] = {
	{ 3,    0,   0, 1.0f - epi * 0 }, // Ground
	{ 4,    0,   0, 0.8f - epi * 0 }, // Objects
	{ 5,   24,   0, 0.8f - epi * 0 }, // Overlay
	{ 6,    0,   0, 0.8f - epi * 1 }, // Down Wall
	{ 6,   32,   0, 0.8f - epi * 2 }, // Right Wall
	{ 7,   32, -64, 0.8f - epi * 1 }, // Roof
	{ 3,   32, -32, 0.8f - epi * 2 }, // Top
	{ 22, -54 + 32, -42 + 30, 0.9f - epi * 0  }, // Shadow
	{ 5,    0,   0, 0.8f - epi * 0 }, // Overlay 2
	};
	this->ThreadLock.lock();
	if (!IsVisible || this->m_Players.size() == 0 ||World::WorldCharacterID < 0)
	{
		this->ThreadLock.unlock();
		return;
	}
	int PlayerIndex = World::WorldCharacterID;
	
	if (m_Players.count(PlayerIndex) > 0)
	{
		this->xpos = this->m_Players[PlayerIndex]->x;
		this->ypos = this->m_Players[PlayerIndex]->y;
		if (this->m_Players[PlayerIndex]->direction == 0 || this->m_Players[PlayerIndex]->direction == 3)
		{
			this->xoff = this->m_Players[PlayerIndex]->xoffset + (this->xpos * 32) - (this->ypos * 32) - 280;
			this->yoff = this->m_Players[PlayerIndex]->yoffset + (this->xpos * 16) + (this->ypos * 16) - 170;
		}
		else
		{
			this->xoff = -this->m_Players[PlayerIndex]->xoffset + (this->xpos * 32) - (this->ypos * 32) - 280;
			this->yoff = this->m_Players[PlayerIndex]->yoffset + (this->xpos * 16) + (this->ypos * 16) - 170;
		}
	}
	//auto&& gfx = m_emf.gfx.;
	auto&& emf = m_emf;
	auto&& emfh = m_emf.header;
	
	float depth = layer_info[0].depth;
	auto next_depth = [&depth, ep]() { return depth -= ep; };
	//this->ThreadLock.unlock();

	this->Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	this->m_OverlaySprite->Begin(D3DXSPRITE_ALPHABLEND);

	int RenderWidth = emfh.width;
	int RenderHeight = emfh.height -1;
	int PlayerMinX = this->m_Players[World::WorldCharacterID]->x;
	if (PlayerMinX < 0) { PlayerMinX = 0; }
	int PlayerMinY = this->m_Players[World::WorldCharacterID]->y;
	if (PlayerMinY < 0) { PlayerMinY = 0; }
	int PlayerMaxX = this->m_Players[World::WorldCharacterID]->x;
	if (PlayerMaxX > RenderWidth) { PlayerMaxX = RenderWidth; }
	int PlayerMaxY = this->m_Players[World::WorldCharacterID]->y;
	if (PlayerMaxY > RenderHeight) { PlayerMaxY = RenderHeight; }
	int  startsuboffset = this->LUTMap[PlayerMinX][PlayerMinY];
	int  endsuboffset = this->LUTMap[PlayerMaxX][PlayerMaxY];

	for (int i = 0; i < RenderWidth + RenderHeight; ++i)
	{
		int x, y;

		if (i < RenderHeight)
		{
			x = 0;
			y = i;
		}
		else
		{
			x = i - RenderHeight;
			y = RenderHeight ;
		}
		
		for (next_depth(); y >= 0 && x < RenderWidth ; --y, ++x, next_depth())
		{
			int xoffs = layer_info[0].xoff - xoff;
			int yoffs = layer_info[0].yoff - yoff;

			int tilex = xoffs + (x * 32) - (y * 32);
			int tiley = yoffs + (x * 16) + (y * 16);
			short tile = 0;
			tile = emf.gfx(x, y)[0];

			if (tilex < -64 || tiley < -32
				|| tilex > 700 || tiley > 500)
				continue;
			Full_EMF::TileMeta tmeta = this->m_emf.meta(x, y);
			float dist = sqrt(((PlayerMaxX - x) * (PlayerMaxX - x)) + ((PlayerMaxY - y) * (PlayerMaxY - y)));
			float varo = 195;//(dist) / (float)(35) * (float)195;
			int var = 60 + varo;
			if (tile > 0)
			{
				D3DXIMAGE_INFO imginfo = map_game->resource->GetImageInfo(3, tile, true);
				int frameno = imginfo.Width / 64;
				if (frameno > 1)
				{
					RECT SrcRect;
					SrcRect.top = 0;
					SrcRect.left = 0 + (64 * (this->MapAnimIndex % frameno));
					SrcRect.right = 64 + (64 * (this->MapAnimIndex % frameno));
					SrcRect.bottom = SrcRect.top + imginfo.Height;

					D3DXVECTOR3* Pos = new D3DXVECTOR3(tilex, tiley, depth);
					D3DXVECTOR3* Center = new D3DXVECTOR3(1, 1, 0);

					this->Sprite->Draw(map_game->resource->CreateTexture(3, tile, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(var, 255, 255, 255));
					delete Pos;
					delete Center;
				}
				else
				{
					map_game->Draw(this->Sprite, map_game->resource->CreateTexture(3, tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(var, 255, 255, 255));
				}
			}
			else if (tile == -1 || tmeta.spec == EMF_Tile_Spec::MapEdge)
			{
			}
			else
			{
				if (emfh.fill_tile > 0)
				{
					map_game->Draw(this->Sprite, map_game->resource->CreateTexture(3, emfh.fill_tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(var, 255, 255, 255));
				}
			}
			if (map_game->MapCursor.x == x && map_game->MapCursor.y == y)
			{			
				map_game->MapCursor.Render(this->Sprite, depth);
			}
			next_depth();
		}

	}	
	
	for (int layer = 1; layer < 7; ++layer)
	{
		for (int i = 0; i < (RenderWidth) + (RenderHeight); ++i)
		{
			int x, y;

			if (i < (RenderHeight))
			{
				x = 0;
				y = i;
			}
			else
			{
				x = i - (RenderHeight);
				y = (RenderHeight);
			}

			for (next_depth(); y >= 0 && x < (RenderWidth); --y, ++x, next_depth())
			{
				int xoffs = layer_info[layer].xoff - xoff;
				int yoffs = layer_info[layer].yoff - yoff;

				int tilex = xoffs + (x * 32) - (y * 32);
				int tiley = yoffs + (x * 16) + (y * 16);
				short tile = 0;
				if ((y * emfh.width + x) < emfh.width * emfh.height)
				{
					tile = m_emf.gfx(x, y)[layer];
				}
				if (tilex < -240 || tiley < -320
					|| tilex > 700 + 240|| tiley > 500 + 320)
					continue;

				depth = layer_info[layer].depth;
				depth -= (this->LUTMap[x][y] * ep);
				if (tile > 0)
				{
					D3DXIMAGE_INFO tile_gfx = map_game->resource->GetImageInfo(layer_info[layer].file, tile, true);
					int tile_w = tile_gfx.Width;
					int tile_h = tile_gfx.Height;
					tilex -= tile_w / (1 + (layer == 1)) - 32;
					tiley -= tile_h - 32;
					
									
					if (layer == 3 || layer == 4)
					{
						D3DXIMAGE_INFO imginfo = map_game->resource->GetImageInfo(layer_info[layer].file, tile, true);
						int frameno = 4;//imginfo.Width / 32;
						int framewidth = imginfo.Width / 4;
						if(imginfo.Width <= 32)
						{
							frameno = 1;
						}
						if (frameno > 1)
						{
							RECT SrcRect;
							SrcRect.top = 0;
							SrcRect.left = 0 + (framewidth * (this->MapAnimIndex % frameno));
							SrcRect.right = framewidth + (framewidth * (this->MapAnimIndex % frameno));
							SrcRect.bottom = SrcRect.top + imginfo.Height;

							D3DXVECTOR3* Pos = new D3DXVECTOR3(tilex + imginfo.Width - framewidth + 32, tiley, depth);
							D3DXVECTOR3* Center = new D3DXVECTOR3(1, 1, 0);
							this->Sprite->Draw(map_game->resource->CreateTexture(layer_info[layer].file, tile, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
							//Pos->z -= 0.1;
							//this->Sprite->Draw(map_game->resource->CreateTexture(layer_info[layer].file, tile, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(150, 255, 255, 255));

							delete Pos;
							delete Center;
						}
						else
						{
							//float varo = ((float)this->LUTMap[x][y]) / (float)(endsuboffset) * (float)50;
							//int var = 50 + varo;
							map_game->Draw(this->Sprite, map_game->resource->CreateTexture(layer_info[layer].file, tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(255, 255, 255, 255));
							//map_game->Draw(this->Sprite, map_game->resource->CreateTexture(layer_info[layer].file, tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(var, 0, 0, 0));
							//map_game->Draw(this->Sprite, map_game->resource->CreateTexture(layer_info[layer].file, tile, true).Texture, tilex, tiley, depth - 0.1, D3DCOLOR_ARGB(150, 255, 255, 255));

						}
					}
					else
					{
						map_game->Draw(this->Sprite, map_game->resource->CreateTexture(layer_info[layer].file, tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(255, 255, 255, 255));
						//map_game->Draw(this->Sprite, map_game->resource->CreateTexture(layer_info[layer].file, tile, true).Texture, tilex, tiley, depth - 0.1, D3DCOLOR_ARGB(150, 255, 255, 255));

					}
				
				}
			}
		}
	}
	for (int i = 0; i < (RenderWidth)+(RenderHeight); ++i)
	{
		int x, y;
		
		if (i < (RenderHeight))
		{
			x = 0;
			y = i;
		}
		else
		{
			x = i - (RenderHeight);
			y = (RenderHeight);
		}

		for (next_depth(); y >= 0 && x < (RenderWidth); --y, ++x, next_depth())
		{
			int xoffs = layer_info[8].xoff - xoff;
			int yoffs = layer_info[8].yoff - yoff;

			int tilex = xoffs + (x * 32) - (y * 32);
			int tiley = yoffs + (x * 16) + (y * 16);
			short tile = 0;
			tile = 0;
			if ((y * emfh.width + x) < emfh.width * emfh.height)
			{
				tile = m_emf.gfx(x, y)[8];
			}
			if (tilex < -64 || tiley < -32
				|| tilex > 700 || tiley > 500)
				continue;

			depth = layer_info[8].depth;
			depth -= (this->LUTMap[x][y] * ep);
			if (tile > 0)
			{
				map_game->Draw(this->Sprite, map_game->resource->CreateTexture(layer_info[5].file, tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(50, 255, 255, 255));
			}
		}
	}
	for (int i = 0; i < (RenderWidth) + (RenderHeight); ++i)
	{
		int x, y;
		if (i < (RenderHeight))
		{
			x = 0;
			y = i;
		}
		else
		{
			x = i - (RenderHeight);
			y = (RenderHeight);
		}

		for (next_depth(); y >= 0 && x < (RenderWidth); --y, ++x, next_depth())
		{
			int xoffs = layer_info[7].xoff - xoff;
			int yoffs = layer_info[7].yoff - yoff;

			int tilex = xoffs + (x * 32) - (y * 32);
			int tiley = yoffs + (x * 16) + (y * 16);
			short tile = 0;
			tile = 0;
			if ((y * emfh.width + x) < emfh.width * emfh.height)
			{
				tile = m_emf.gfx(x, y)[7];
			}
			if (tilex < -64 || tiley < -32
				|| tilex > 700 || tiley > 500)
				continue;
			depth = layer_info[7].depth;
			depth -= (this->LUTMap[x][y] * ep);
			if (tile > 0)
			{
				map_game->Draw(this->Sprite, map_game->resource->CreateTexture(layer_info[7].file, tile, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(50, 255, 255, 255));
			}
		}
	}
	int layer = 1;
	for (std::map<int, Map_Player*>::iterator player = this->m_Players.begin(); player != m_Players.end(); ++player)
	{
		depth = layer_info[layer].depth;
		depth -= (this->LUTMap[player->second->x][player->second->y] * ep);
		if (rendering)
		{
			int xoffsp = layer_info[layer].xoff - xoff;
			int yoffsp = layer_info[layer].yoff - yoff;
			int tilexp = xoffsp + (player->second->x * 32) - (player->second->y * 32);
			int tileyp = yoffsp + (player->second->x * 16) + (player->second->y * 16);
			player->second->Map_PlayerRender(this->Sprite, tilexp + 24, tileyp - 40, depth);
		//	player->second->Map_PlayerRender(this->Sprite, tilexp + 24, tileyp - 40, depth - 0.1);
		}
	}
	for (std::map<int, Map_NPC*>::iterator NPC = this->m_NPCs.begin(); NPC != m_NPCs.end(); ++NPC)
	{
		depth = layer_info[layer].depth;
		depth -= (this->LUTMap[NPC->second->x][NPC->second->y] * ep);
		if (rendering)
		{
			next_depth();
			int xoffsp = layer_info[layer].xoff - xoff;
			int yoffsp = layer_info[layer].yoff - yoff;
			int tilexp = xoffsp + (NPC->second->x * 32) - (NPC->second->y * 32);
			int tileyp = yoffsp + (NPC->second->x * 16) + (NPC->second->y * 16);
			NPC->second->Render(this->Sprite, tilexp, tileyp, depth);
			//NPC->second->Render(this->Sprite, tilexp, tileyp, depth);
		}
	}

	for (std::map<int, Map_Item>::iterator m_item = this->m_Items.begin(); m_item != m_Items.end(); ++m_item)
	{
		depth = layer_info[layer].depth;
		depth -= (this->LUTMap[m_item->second.x][m_item->second.y] * ep);

		int xoffs = -xoff + 32;
		int yoffs = -yoff + 16;

		int graphic = World::EIF_File->Get(m_item->second.ItemID).graphic * 2;

		if (m_item->second.ItemID == 1)
		{
			if (m_item->second.amount == 1)
			{
				graphic = 270;
			}
			else if (m_item->second.amount <= 100)
			{
				graphic = 272;
			}
			else if (m_item->second.amount <= 1000)
			{
				graphic = 274;
			}
			else if (m_item->second.amount <= 100000)
			{
				graphic = 276;
			}
			else //if (m_item->second.amount <= 100000)
			{
				graphic = 278;
			}
		}

		D3DXIMAGE_INFO tile_gfx = map_game->resource->GetImageInfo(23, graphic - 1, true);
		int tile_w = tile_gfx.Width;
		int tile_h = tile_gfx.Height;


		int tilex = xoffs + (m_item->second.x * 32) - (m_item->second.y * 32) - (tile_gfx.Width / 2);
		int tiley = yoffs + (m_item->second.x * 16) + (m_item->second.y * 16) - (tile_gfx.Height / 2);
		map_game->Draw(this->Sprite, map_game->resource->CreateTexture(23, (graphic)-1, true).Texture, tilex, tiley, depth, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	this->world->RenderTextBoxes(this->Sprite, map_game->Stage, map_game->SubStage);
	this->Sprite->End();
	this->m_OverlaySprite->End();
	this->ThreadLock.unlock();
}
Map::~Map()
{
}

#include "..\..\stdafx.h"
#include "..\Map.h"
#include "..\Map_UI\Map_UI_SelectPlayer.h"
#include "..\..\Packet_Handler\Send\SItem.h"
#include "..\..\Packet_Handler\Send\SChest.h"
#include "..\..\Utilities\UI_Element.h"

#include "..\..\game.h"
#include "..\..\Packet_Handler\Send\SShop.h"
#include "Map_UI_Cursor.h"

Map_UI_Cursor::Map_UI_Cursor()
{
	//this->Initialize()
}

std::basic_string<wchar_t> cur_istring;
std::basic_string<char> scur_istring;
Map_UI_Cursor::Map_UI_Cursor(Game* m_Game, Map* m_Map, sf::RenderWindow*m_Device)
{
	this->m_game = m_Game;
	this->Initialize(this->m_game);
	this->p_Map = m_Map;
	this->p_Device = m_Device;
	//D3DXCreateSprite(m_Device, &this->p_Sprite);
	m_CursorType = CursorType::None;
	cur_istring = L"";
	
}


Map_UI_Cursor::~Map_UI_Cursor()
{
}

bool hideme = false;

void Map_UI_Cursor::Render(sf::Sprite* m_sprite, float depth)
{
	if (this->m_game->Map_UserInterface->PlayerSelect->MouseoverMenu)
	{
		this->m_CursorType = CursorType::None;
		return;
	}
	if (hideme)
	{
		return;
	}
	//D3DXMATRIX mat;
	RECT SrcRect;
	int Height = 0;
	std::string Name = "";
	cursordat = CursorDat();
	cursordat._CType = CursorType::None;
	int MapElementDepth = 0;
	//if (this->m_CursorType != CursorType::Invisible)
	{	//p_Map->ThreadLock.lock();

		for (std::map<int, Map_NPC*>::iterator NPC = this->p_Map->m_NPCs.begin(); NPC != this->p_Map->m_NPCs.end(); ++NPC)
		{
			int tilexp = ((NPC->second->x * 32) - (NPC->second->y * 32)) - this->p_Map->xoff;
			int tileyp = ((NPC->second->x * 16) + (NPC->second->y * 16)) - this->p_Map->yoff;
			if ((NPC->second->x == x && NPC->second->y == y))
			{
				if (p_Map->LUTMap[NPC->second->x][NPC->second->y] > MapElementDepth)
				{
					cursordat._CType = CursorType::NPC;
					cursordat.index = NPC->first;
					cursordat.x = NPC->second->x;
					cursordat.y = NPC->second->y;
				}
				this->m_CursorType = CursorType::Object;
				break;
			}
			else if (((tilexp >= this->m_game->MouseX - 41 && tilexp <= this->m_game->MouseX - 23) && (tileyp >= this->m_game->MouseY - 22 && tileyp <= this->m_game->MouseY + 46)))
			{
				int NPCDepth = p_Map->LUTMap[NPC->second->x][NPC->second->y];
				if (NPCDepth > MapElementDepth)
				{
					cursordat._CType = CursorType::NPC;
					cursordat.index = NPC->first;
					cursordat.x = NPC->second->x;
					cursordat.y = NPC->second->y;
					MapElementDepth = NPCDepth;
				}
			}
		}
		for (std::map<int, Map_Player*>::iterator player = this->p_Map->m_Players.begin(); player != this->p_Map->m_Players.end(); ++player)
		{
			if (player->second)
			{
				int tilexp = ((player->second->x * 32) - (player->second->y * 32)) - this->p_Map->xoff;
				int tileyp = ((player->second->x * 16) + (player->second->y * 16)) - this->p_Map->yoff;
				if ((player->second->x == x && player->second->y == y))
				{
					if (p_Map->LUTMap[player->second->x][player->second->y] > MapElementDepth)
					{
						cursordat._CType = CursorType::Player;
						cursordat.index = player->first;
						cursordat.x = player->second->x;
						cursordat.y = player->second->y;
					}

					this->m_CursorType = CursorType::Object;
				}
				else if (((tilexp >= this->m_game->MouseX - 41 && tilexp <= this->m_game->MouseX - 23) && (tileyp >= this->m_game->MouseY - 22 && tileyp <= this->m_game->MouseY + 46)))
				{
					int playerdepth = p_Map->LUTMap[player->second->x][player->second->y];
					if (playerdepth > MapElementDepth)
					{
						cursordat._CType = CursorType::Player;
						cursordat.index = player->first;
						cursordat.x = player->second->x;
						cursordat.y = player->second->y;
						MapElementDepth = playerdepth;
					}
				}
			}
			
		}
		for (std::map<int, Map::Map_Item>::iterator m_item = this->p_Map->m_Items.begin(); m_item != this->p_Map->m_Items.end(); ++m_item)
		{
			if (m_item->second.x == x && m_item->second.y == y)
			{
				std::string Itemname = World::EIF_File->Get(m_item->second.ItemID).name;
				std::string Amount = to_string(m_item->second.amount) + " ";
				Name = Amount + Itemname;
				if (m_item->second.ItemID > 1)
				{
					Amount = to_string(m_item->second.amount);
					Name = Itemname + " x " + Amount;
				}
				Name[0] = std::toupper(Name[0]);
				Height = 16;
				this->m_CursorType = CursorType::Object;
				if (this->m_game->MousePressed)
				{
					SItem::SendPickup(this->m_game->world->connection->ClientStream, m_item->first, this->m_game);
				}
				break;
			}
		}

		if (!this->m_game->RAWMousePressed)
		{
			if (this->m_game->Map_UserInterface->map_inventory->childMPindex >= 0)
			{
				int x = this->x;
				int y = this->y;
				if (abs((this->m_game->map->m_Players[World::WorldCharacterID]->x - x)) < 2 && abs((this->m_game->map->m_Players[World::WorldCharacterID]->y - y)) < 2)
				{
					if (!this->m_game->world->W_UI_Infobox->IsVisible())
					{
						int amount = 0;
						for (int i = 0; i < this->m_game->Map_UserInterface->map_inventory->inventory.size(); i++)
						{
							if (this->m_game->Map_UserInterface->map_inventory->inventory[i].id == this->m_game->Map_UserInterface->map_inventory->childMPindex)
							{
								amount = this->m_game->Map_UserInterface->map_inventory->inventory[i].amount;
							}
						}
						if (amount == 1)
						{
							SItem::SendDrop(this->m_game->world->connection->ClientStream, this->m_game->Map_UserInterface->map_inventory->childMPindex, 1, x, y, this->m_game);
							this->m_game->Map_UserInterface->map_inventory->childMPindex = -1;
						}
						else if (amount > 1)
						{
							this->m_game->Map_UserInterface->map_inventory->DisplayDropDialogue(true, amount, this->m_game->Map_UserInterface->map_inventory->childMPindex, x, y);
							this->m_game->Map_UserInterface->map_inventory->childMPindex = -1;
						}
					}
				}
			}
		}
		if (this->m_game->world->W_UI_Infobox->IsVisible() && this->m_game->world->W_UI_Infobox->MouseOver())
		{
			if (this->m_game->Map_UserInterface->map_inventory->childMPindex >= 0 && !this->m_game->Map_UserInterface->MouseHeld && World::ChestX >= 0 && World::ChestY >= 0)
			{
				SChest::SendAddChest(this->m_game->world->connection->ClientStream, this->m_game->Map_UserInterface->map_inventory->childMPindex, 1, (LPVOID)this->m_game);
			}
		}
		if (this->m_CursorType != CursorType::Invisible)
		{
			SrcRect.bottom = 32;
			SrcRect.left = 0 + (64 * this->m_CursorType);
			SrcRect.right = 64 + (64 * this->m_CursorType);
			SrcRect.top = 0;
			//D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, NULL, NULL);
			int rx = (x - this->p_Map->xpos);
			int ry = (y - this->p_Map->ypos);
			int mx = (rx * 32) - (ry * 32) + 280;
			int my = (ry * 16) + (rx * 16) + 170;


			this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 24, true), mx, my, sf::Color::White, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), depth);
		}
		if (Name != "" || cursordat._CType != CursorType::None)
		{
			RECT rct;
			int px = x;
			int py = y;
			if (cursordat._CType != CursorType::None)
			{
				px = cursordat.x;
				py = cursordat.y;
				if (cursordat._CType == CursorType::Player)
				{
					Map_Player* player = p_Map->m_Players[cursordat.index];
					Name = player->name;
					Name[0] = std::toupper(Name[0]);
					Name += "  " + player->guildtag;
					Height = 65;
					if (player->Stance == Map_Player::PlayerStance::ChairSitting || player->Stance == Map_Player::PlayerStance::GroundSitting)
					{
						Height = 45;
					}
				}
				if (cursordat._CType == CursorType::NPC)
				{
					Map_NPC* mNPC = p_Map->m_NPCs[cursordat.index];
					px = cursordat.x;
					py = cursordat.y;
					Name = this->m_game->ENF_File->data[mNPC->ID].name;
					Name[0] = std::toupper(Name[0]);

					Height = this->m_game->ResourceManager->GetResource(21, (this->m_game->ENF_File->data[mNPC->ID].graphic - 1) * 40 + 1, true)->_height;
					if (Height == 0)
					{
						Height = this->m_game->ResourceManager->GetResource(21, (this->m_game->ENF_File->data[mNPC->ID].graphic - 1) * 40 + 2, true)->_height;
					}
				}

			}
			int ax = (px - this->p_Map->xpos);
			int ay = (py - this->p_Map->ypos);
			int cx = (ax * 32) - (ay * 32) + 280;
			int cy = (ay * 16) + (ax * 16) + 170;
			if (this->m_game->map->m_Players[World::WorldCharacterID]->direction == 0 || this->m_game->map->m_Players[World::WorldCharacterID]->direction == 3)
			{
				rct.left = cx - 16 - (this->m_game->map->m_Players[World::WorldCharacterID]->xoffset);
				rct.right = rct.left + 100;
				rct.top = cy - Height - (this->m_game->map->m_Players[World::WorldCharacterID]->yoffset);
				rct.bottom = rct.top + 20;
			}
			else
			{
				rct.left = cx - 16 + (this->m_game->map->m_Players[World::WorldCharacterID]->xoffset);
				rct.right = rct.left + 100;
				rct.top = cy - Height - (this->m_game->map->m_Players[World::WorldCharacterID]->yoffset);
				rct.bottom = rct.top + 20;
			}

			std::basic_string<wchar_t> Game_istring;
			Game_istring.clear();
			std::wstring newstr = std::to_wstring(depth).c_str();
			Game_istring += newstr.substr(0, 4);

			this->m_game->DrawTextW(Name, rct.left + 50, rct.top - 5, sf::Color(255, 255, 255, 255), 11, true, 0.04, 1);
		
		}
	}


	//this->p_Sprite->End();

}

std::pair<int, int> ScreenCordToMap(std::pair<int, int> m_loc)
{
	/*int screenx = (m_loc.first - m_loc.second) * 32;
	int screeny = (m_loc.first + m_loc.second) * 16;
	return std::pair<int, int>(screenx, screeny);*/
	float PI = 3.1415;
	float x = m_loc.first - 32;
	float y = m_loc.second ;
	//# Translate one origin to the other
	float x1 = x ;
	//# Stretch the height so that it's the same as the width in the isometric
	//# This makes the rotation easier
	//# Invert the sign because y is upwards in math but downwards in graphics
	float y1 = y * - 2;

	//# Apply a counter - clockwise rotation of 45 degrees
	float xr = cos(PI / 4) * x1 - sin(PI / 4) * y1;
	float yr = sin(PI / 4) * x1 + cos(PI / 4) * y1;

	//# The side of each isometric tile(which is now a square after the stretch)
	float diag = 32 * sqrt(2);
	//# Calculate which tile the coordinate belongs to
	float x2 = int(xr / diag);
	//# Don't forget to invert the sign again
	float y2 = int(yr * -1 / diag);
	x2 = int(xr / diag);
	return std::pair<int, int>(x2, y2);
}

static const wchar_t* SpecNames[] = { L"None",	L"Wall",L"ChairDown",L"ChairLeft",L"ChairRight",L"ChairUp",L"ChairDownRight",L"ChairUpLeft",L"ChairAll",L"Unknown1", L"Unknown2", L"Chest",L"Unknown3",L"Unknown4",L"Unknown5",L"Unknown6",L"Unknown7",L"Unknown8",L"Unknown9",L"BankVault",L"NPCBoundary",L"MapEdge",L"FakeWall",L"Board1",L"Board2" ,L"Board3" ,L"Board4" ,L"Board5" ,L"Board6" ,L"Board7" ,L"Board8" ,L"Jukebox" ,L"Jump" ,L"Water",L"SpecUnknown7" ,L"Arena" ,L"AmbientSource" ,L"Spikes1",L"Spikes2",L"Spikes3" };
void Map_UI_Cursor::Update()
{
	int MouseX = this->m_game->MouseX + this->p_Map->xoff;
	int MouseY = this->m_game->MouseY + this->p_Map->yoff;

	if (this->m_game->MousePressed)
	{
		///Need to fix this up. Have two distinct identifiers for cursor type, problem arose when I added the ability to see names of players/NPCs by renderdepth.
		switch (this->cursordat._CType)
		{
			case(CursorType::NPC):
			{
				this->p_Map->ThreadLock.lock();
				Map_NPC* m_NPC = this->p_Map->m_NPCs[this->cursordat.index];
				if (m_NPC)
				{
					if (this->m_game->ENF_File->data[m_NPC->ID].type == ENF::Type::Shop && this->m_game->world->UIBox_Hidden)
					{
						SShop::SendShopOpen(this->m_game->world->connection->ClientStream, this->cursordat.index, this->m_game);
					}
				}

				this->p_Map->ThreadLock.unlock();
				break;
			}
			default:
			{
				break;
			}
		}

		switch (this->m_CursorType)
		{
			case(CursorType::Vault):
			{
				SChest::SendOpenChest(this->m_game->world->connection->ClientStream, this->x, this->y, this->m_game);
				break;
			}
			case(CursorType::Chest):
			{
				SChest::SendOpenChest(this->m_game->world->connection->ClientStream, this->x, this->y, this->m_game);
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
	if (!this->m_game->Map_UserInterface->MouseHeld)
	{
		this->m_game->Map_UserInterface->map_inventory->childMPindex = -1;
	}
	hideme = false;
	if (this->m_game->MouseY > 308 || this->m_game->MouseY < 12)
	{
		hideme = true;
		return;
	}
	std::pair<int, int> pa = ScreenCordToMap(std::pair<int, int>(MouseX, MouseY));
	x = pa.first;//+ this->p_Map->xpos;
	y = pa.second; //+ this->p_Map->ypos;
	if (x < 0 || x >= this->p_Map->m_emf.header.width) { x = -1; }
	if (y < 0 || y >= this->p_Map->m_emf.header.height) { y = -1; }
	if (x >= 0 && y >= 0)
	{
		this->p_Map->ThreadLock.lock();
		Full_EMF::TileMeta tmeta = this->p_Map->m_emf.meta(x, y);
		
		if (tmeta.sign.first != "" && this->m_game->MousePressed)
		{
			World::ThrowMessage(tmeta.sign.first, tmeta.sign.second);
			this->m_game->MousePressed = false;
		}
		if (tmeta.spec > (EMF_Tile_Spec)0 && tmeta.spec < (EMF_Tile_Spec)17)
		{
			this->m_CursorType = CursorType::Object;
		}
		if (tmeta.spec > (EMF_Tile_Spec)19 && tmeta.spec < (EMF_Tile_Spec)31)
		{
			this->m_CursorType = CursorType::Object;
		}
		switch (tmeta.spec)
		{
			case(EMF_Tile_Spec::None):
			{
				this->m_CursorType = CursorType::None;
				break;
			}
			case(EMF_Tile_Spec::NPCBoundary):
			{
				this->m_CursorType = CursorType::None;
				break;
			}
			case(EMF_Tile_Spec::BankVault):
			{
				this->m_CursorType = CursorType::Vault;
				break;
			}
			case(EMF_Tile_Spec::Chest):
			{
				this->m_CursorType = CursorType::Chest;
				break;
			}
			default:
			{
				this->m_CursorType = CursorType::Invisible;
				break;
			}
		}
		this->p_Map->ThreadLock.unlock();
	}

#ifdef DEBUG 
	cur_istring.clear();
	wchar_t xstr[12];
	cur_istring += L"MouseX = ";
	_itow_s(x, xstr, 12, 10);
	cur_istring += xstr;
	wchar_t ystr[12];
	cur_istring += L": MouseY = ";
	_itow_s(y, ystr, 12, 10);
	cur_istring += ystr;
	cur_istring += L"\nMapWarpSpec= ";
	this->p_Map->ThreadLock.lock();
	if (this->x >=0 && this->y >= 0)
	{
		Full_EMF::TileMeta tmeta = this->p_Map->m_emf.meta(x, y);
		if (((int)tmeta.spec + 1)>= 0 && ((int)tmeta.spec + 1) <= 36)
		{
			cur_istring += SpecNames[(int)tmeta.spec + 1];
		}
	}
	else
	{
		cur_istring += SpecNames[0];
	}
	if (this->x >= 0 && this->y >= 0)
	{
		Full_EMF::TileMeta tmeta = this->p_Map->m_emf.meta(x, y);
		EMF_Warp ewarp = tmeta.warp;
		
		if (ewarp.door == 1)
		{
			cur_istring += L"\nMapWarp = ";
			cur_istring += L"Door";
		}
		else if(ewarp.warp_map > 0)
		{
			cur_istring += L"\nMapWarp = ";
			cur_istring += L"Warp";
		}
		cur_istring += L"\nTileSpec = ";
		cur_istring += L"[" + to_wstring((int)tmeta.spec) + L"]";
	
		std::array<eo_short,9> GFX_array = this->p_Map->m_emf.gfx(x,y);
		cur_istring += L"\nGFX = ";
		for (int i = 0; i < 9; i++)
		{
			cur_istring += L"[" + to_wstring(GFX_array[i]) + L"]";
		}
		cur_istring += L"\nFillTile = " + to_wstring(this->p_Map->m_emf.header.fill_tile);
	}
	this->p_Map->ThreadLock.unlock();
#endif
}
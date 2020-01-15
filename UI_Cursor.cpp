#include "stdafx.h"
#include "UI_Cursor.h"
#include "Game.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */
#include "Send/SItem.h"
#include "Map_UI_Element/Map_UI_SelectPlayer.h"


Game* p_Game;
UI_Cursor::UI_Cursor()
{
	//this->Initialize()
}

std::basic_string<wchar_t> cur_istring;
std::basic_string<char> scur_istring;
UI_Cursor::UI_Cursor(VOID* m_Game, Map* m_Map, IDirect3DDevice9Ptr m_Device)
{
	p_Game = (Game*)m_Game;
	this->Initialize(p_Game);
	this->p_Map = m_Map;
	this->p_Device = m_Device;
	D3DXCreateSprite(m_Device, &this->p_Sprite);
	m_CursorType = CursorType::None;
	cur_istring = L"";
	
}


UI_Cursor::~UI_Cursor()
{
}

bool hideme = false;

void UI_Cursor::Render(ID3DXSprite* m_sprite, float depth)
{
	if (p_Game->Map_UserInterface->PlayerSelect->MouseoverMenu)
	{
		this->m_CursorType = CursorType::None;
		return;
	}
	if(hideme)
	{
		return;
	}
	D3DXMATRIX mat;
	RECT SrcRect;

	int Height = 0;
	std::string Name = "";

	if (this->m_CursorType != CursorType::Invisible)
	{	//p_Map->ThreadLock.lock();
		for (std::map<int, Map_NPC*>::iterator NPC = this->p_Map->m_NPCs.begin(); NPC != this->p_Map->m_NPCs.end(); ++NPC)
		{
			if (NPC->second->x == x && NPC->second->y == y)
			{
				Name = p_Game->ENF_File->data[NPC->second->ID].name;
				Name[0] = std::toupper(Name[0]);
			
				Height = p_Game->resource->GetImageInfo(21,( p_Game->ENF_File->data[NPC->second->ID].graphic - 1)*40 + 1, true).Height;
				this->m_CursorType = CursorType::Object;
				break;
			}
		}

		for (std::map<int, Map_Player*>::iterator player = this->p_Map->m_Players.begin(); player != this->p_Map->m_Players.end(); ++player)
		{
			if (player->second->x == x && player->second->y == y)
			{
				Name = player->second->name;
				Name[0] = std::toupper(Name[0]);
				Name += "  " + player->second->guildtag;
				Height = 65;
				if (player->second->Stance == Map_Player::PlayerStance::ChairSitting || player->second->Stance == Map_Player::PlayerStance::GroundSitting)
				{
					Height = 45;
				}
				this->m_CursorType = CursorType::Object;
				break;
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
				if (p_Game->MousePressed)
				{
					SItem::SendPickup(p_Game->world->connection->ClientStream,m_item->first, p_Game);
				}
				break;
			}
		}
		//p_Map->ThreadLock.unlock();
		if (!p_Game->RAWMousePressed)
		{
			if (p_Game->Map_UserInterface->map_inventory->childMPindex >= 0)
			{
				int x = this->x;
				int y = this->y;
				if(abs((p_Game->map->m_Players[World::WorldCharacterID]->x - x)) < 2 && abs((p_Game->map->m_Players[World::WorldCharacterID]->y - y)) < 2)
				{ 
					int amount = 0;
					for (int i = 0; i < p_Game->Map_UserInterface->map_inventory->inventory.size(); i++)
					{
						if (p_Game->Map_UserInterface->map_inventory->inventory[i].id == p_Game->Map_UserInterface->map_inventory->childMPindex)
						{
							amount = p_Game->Map_UserInterface->map_inventory->inventory[i].amount;
						}
					}
					if (amount == 1)
					{
						SItem::SendDrop(p_Game->world->connection->ClientStream, p_Game->Map_UserInterface->map_inventory->childMPindex, 1, x, y, p_Game);
						p_Game->Map_UserInterface->map_inventory->childMPindex = -1;
					}
					else if (amount > 1)
					{
						p_Game->Map_UserInterface->map_inventory->DisplayDropDialogye(true, amount, p_Game->Map_UserInterface->map_inventory->childMPindex, x, y);
						p_Game->Map_UserInterface->map_inventory->childMPindex = -1;
					}
				}
			}
		}
		SrcRect.bottom = 32;
		SrcRect.left = 0 + (64 * this->m_CursorType);
		SrcRect.right = 64 + (64 * this->m_CursorType);
		SrcRect.top = 0;
		D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, NULL, NULL);
		int rx = (x - this->p_Map->xpos);
		int ry = (y - this->p_Map->ypos);
		int mx = (rx * 32) - (ry * 32)+ 280;
		int my = (ry * 16) + (rx * 16)+ 170;


		D3DXVECTOR3 * Pos = new D3DXVECTOR3(mx, my , depth);
		D3DXVECTOR3 * Center = new D3DXVECTOR3(1, 1, 0);

		m_sprite->SetTransform(&mat);
		m_sprite->Draw(p_Game->resource->CreateTexture(2, 24, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
		delete Pos;
		delete Center;
		if (Name != "")
		{
			RECT rct;

			if (p_Game->map->m_Players[World::WorldCharacterID]->direction == 0 || p_Game->map->m_Players[World::WorldCharacterID]->direction == 3)
			{
				rct.left = mx - 16 - (p_Game->map->m_Players[World::WorldCharacterID]->xoffset);
				rct.right = rct.left + 100;
				rct.top = my - Height - (p_Game->map->m_Players[World::WorldCharacterID]->yoffset);
				rct.bottom = rct.top + 20;
			}
			else
			{
				rct.left = mx - 16 + (p_Game->map->m_Players[World::WorldCharacterID]->xoffset);
				rct.right = rct.left + 100;
				rct.top = my - Height - (p_Game->map->m_Players[World::WorldCharacterID]->yoffset);
				rct.bottom = rct.top + 20;
			}

			std::basic_string<wchar_t> Game_istring;
			Game_istring.clear();
			std::wstring newstr = std::to_wstring(depth).c_str();
			Game_istring += newstr.substr(0, 4);

			p_Game->MessageFont->DrawTextA(m_sprite, Name.c_str(), -1, &rct, DT_CENTER, D3DCOLOR_ARGB(255, 255, 255, 255));

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
void UI_Cursor::Update()
{
	int MouseX = p_Game->MouseX + this->p_Map->xoff;
	int MouseY = p_Game->MouseY + this->p_Map->yoff;

	if (!p_Game->Map_UserInterface->MouseHeld)
	{
		p_Game->Map_UserInterface->map_inventory->childMPindex = -1;
	}
	hideme = false;
	if (p_Game->MouseY > 308 || p_Game->MouseY < 12)
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

		default:
		{
			this->m_CursorType = CursorType::Invisible;
			break;
		}
		}
		if (tmeta.sign.first != "" && p_Game->MousePressed)
		{
			World::ThrowMessage(tmeta.sign.first, tmeta.sign.second);
			p_Game->MousePressed = false;
		}
		if (tmeta.spec > (EMF_Tile_Spec)0 && tmeta.spec < (EMF_Tile_Spec)17)
		{
			this->m_CursorType = CursorType::Object;
		}
		if (tmeta.spec > (EMF_Tile_Spec)19 && tmeta.spec < (EMF_Tile_Spec)31)
		{
			this->m_CursorType = CursorType::Object;
		}
		this->p_Map->ThreadLock.unlock();
	}


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

}
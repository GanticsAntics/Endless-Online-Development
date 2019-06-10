#include "stdafx.h"
#include "UI_Cursor.h"
#include "Game.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* floor */

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
	if(hideme)
	{
		return;
	}
	//this->p_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	D3DXMATRIX mat;
	RECT SrcRect;

	p_Game->DrawTextW(cur_istring.c_str(), 10, 32, D3DCOLOR_ARGB(200, 255, 255, 255));

	if (this->m_CursorType != CursorType::Invisible)
	{
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

		/*RECT rct;
		rct.left = x;
		rct.right = x + 100;
		rct.top = y;
		rct.bottom = y + 100;

		std::basic_string<wchar_t> Game_istring;
		Game_istring.clear();
		std::wstring newstr = std::to_wstring(depth).c_str();
		Game_istring += newstr.substr(0, 4);

		p_Game->MessageFont->DrawText(m_sprite, Game_istring.c_str(), -1, &rct, 0, D3DCOLOR_ARGB(255, 255, 255, 255));*/

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


	/*	std::string test = "";
		cur_istring.clear();
		char xstr[12];
		test += "MouseX = " + std::to_string(xr) + "{" + std::to_string(floor(xr/64)) + "}" + ": Mouse Y = " + std::to_string(yr) + "{" + std::to_string(floor(yr / 32)) + "}";
		World::DebugPrint(test.c_str());*/

	//# See the final result
	return std::pair<int, int>(x2, y2);
}
void UI_Cursor::Update()
{
	int MouseX = p_Game->MouseX + this->p_Map->xoff;
	int MouseY = p_Game->MouseY + this->p_Map->yoff;
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
	}
	for (std::map<int, Map_NPC*>::iterator NPC = this->p_Map->m_NPCs.begin(); NPC != this->p_Map->m_NPCs.end(); ++NPC)
	{
		if (NPC->second->x == x && NPC->second->y == y)
		{
			this->m_CursorType = CursorType::Object;
			break;
		}
	}

	for (std::map<int, Map_Player*>::iterator player = this->p_Map->m_Players.begin(); player != this->p_Map->m_Players.end(); ++player)
	{
		if (player->second->x == x && player->second->y == y)
		{
			this->m_CursorType = CursorType::Object;
			break;
		}
	}

	cur_istring.clear();
	wchar_t xstr[12];
	cur_istring += L"MouseX = ";
	_itow_s(x, xstr, 12, 10);
	cur_istring += xstr;
	wchar_t ystr[12];
	cur_istring += L": Mouse Y = ";
	_itow_s(y, ystr, 12, 10);
	cur_istring += ystr;
}
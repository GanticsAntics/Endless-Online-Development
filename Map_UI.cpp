#include "stdafx.h"
#include "Map_UI.h"
#include "Game.h"
#include "include/CBitmapEx/BitmapEx.h"
#include "Send/STalk.h"
Map_UI::Map_UI()
{
	D3DXVECTOR2 Pos;
	Pos.x = 380;
	Pos.y = 313;

	D3DXVECTOR2 Size;
	Size.x = 140;
	Size.y = 30;
}
Game* UI_Game;
CBitmapEx UI_Mask;
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}
void Map_UI::UI_SendMessage()
{
	if (this->ChatTextbox->text != L"")
	{
		std::string message = ws2s(this->ChatTextbox->text);
		STalk::SendTalk(UI_Game->world->connection->ClientStream, message, UI_Game);
		this->ChatTextbox->TextBounds = RECT();
		this->ChatTextbox->text.clear();
		std::string playername = UI_Game->map->m_Players[World::WorldCharacterID]->name;
		playername[0] = std::toupper(playername[0]);
		TextTools::AppendChat(0, 380, playername, message, UI_Game->MessageFont);
		UI_Game->Map_UserInterface->map_talk->UI_TextScrollbar->BottomLineIndex();
	}
}
LPDIRECT3DTEXTURE9 TX_UI_Mask = NULL;
void Map_UI::Initialize(World* _world, IDirect3DDevice9Ptr m_Device, LPVOID* m_game)
{
	D3DXIMAGE_INFO info = D3DXIMAGE_INFO();
	this->m_world = _world;
	this->m_Device = m_Device;
	D3DXCreateSprite(this->m_Device, &this->Sprite);
	UI_Game = (Game*)m_game;
	this->map_news = new Map_UI_News(this, m_game);
	this->map_inventory = new Map_UI_Inventory(this, m_game);
	this->map_characterstats = new Map_UI_CharacterStats(this, m_game);
	this->map_gamehelp = new Map_UI_GameHelp(this, m_game);
	this->map_gamesettings = new Map_UI_GameSettings(this, m_game);
	this->map_macro = new Map_UI_KeyboardMacros(this, m_game);
	this->map_mapUI = new Map_UI_Map(this, m_game);
	this->map_party = new Map_UI_Party(this, m_game);
	this->map_passiveskills = new Map_UI_PassiveSkills(this, m_game);
	this->map_skills = new Map_UI_Skills(this, m_game);
	this->map_talk = new Map_UI_Talk(this, m_game);
	this->map_whoisonline = new Map_UI_WhoIsOnline(this, m_game);
	D3DXVECTOR2 Pos;
	Pos.x = 107;
	Pos.y = 309;

	D3DXVECTOR2 Size;
	Size.x = 340;
	Size.y = 30;
	Textbox m_ChatTextbox =  Textbox(Pos, Size, D3DCOLOR_ARGB(255, 0, 0, 0), UI_Game->MessageFont, Game::GameStage::PInGame, 0);
	m_ChatTextbox.blinkhidden = false;
	m_ChatTextbox.MaxLen = 200;
	m_ChatTextbox.nonAcceptedKeyEntered = true;
	m_ChatTextbox.acceptspace = true;
	m_ChatTextbox.acceptsReturn = true;
	m_ChatTextbox.SetKeyMask(Textbox::KeyType::None);
	this->ChatTextbox = UI_Game->world->RegisterTextBox(m_ChatTextbox);

	UI_Mask.Create(640, 480);
	UI_Mask.Clear(_RGB(100,0,0));
	UI_Mask.MakeTransparent(_RGB(100, 0, 0));
	for (int i = 0; i < UI_Mask.GetWidth(); i++)
	{
		for (int ii = 308; ii < UI_Mask.GetHeight(); ii++)
		{
			UI_Mask.SetPixel(i, ii, _RGB(1, 0, 0));
		}
	}
	for (int i = 0; i < 11; i++)
	{
		for (int ii = 0; ii < UI_Mask.GetHeight(); ii++)
		{
			UI_Mask.SetPixel(i, ii, _RGB(1, 0, 0));
			UI_Mask.SetPixel(i + 629, ii, _RGB(1, 0, 0));
		}
	}
	for (int i = 0; i < UI_Mask.GetWidth(); i++)
	{
		for (int ii = 0; ii < 9; ii++)
		{
			UI_Mask.SetPixel(i, ii, _RGB(1, 0, 0));
		}
	}
	for (int i = 49; i < 99; i++)
	{
		for (int ii = 0; ii < 11; ii++)
		{
			UI_Mask.SetPixel(i, ii, _RGB(1, 0, 0));
			UI_Mask.SetPixel(i + 494, ii, _RGB(1, 0, 0));
		}
	}
	DWORD dwBufferSize = UI_Mask.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	LPBYTE buffer;
	buffer = (LPBYTE)malloc(dwBufferSize);
	UI_Mask.Save(buffer);

	HRESULT Hr = D3DXCreateTextureFromFileInMemoryEx(m_Device, buffer, dwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DCOLOR_ARGB(1, 0, 0, 0), &info, NULL, &TX_UI_Mask);
	
	free(buffer);
	__deallocate(bitmapEx);
}

void Map_UI::Update()
{
	this->MouseX = UI_Game->MouseX;
	this->MouseY = UI_Game->MouseY;
	this->FPS = UI_Game->FPS;
	this->MousePressed = UI_Game->MousePressed;
	this->MouseHeld = UI_Game->RAWMousePressed;
	this->map_news->Update();
	this->map_inventory->Update();
	this->map_characterstats->Update();
	this->map_gamehelp->Update();
	this->map_gamesettings->Update();
	this->map_macro->Update();
	this->map_mapUI->Update();
	this->map_party->Update();
	this->map_passiveskills->Update();
	this->map_skills->Update();
	this->map_talk->Update();
	this->map_whoisonline->Update();
	UI_Game->world->SetFocusedTextbox(this->ChatTextbox);
}

void Map_UI::Render()
{
	this->Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	UI_Game->Draw(this->Sprite, TX_UI_Mask, 1, 1, D3DCOLOR_ARGB(255, 255, 255, 255));
	UI_Game->Draw(this->Sprite, UI_Game->resource->CreateTexture(2, 1, true).Texture, 1, 1, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	/*UI_Game->Draw(this->Sprite, UI_Game->resource->CreateTexture(2, 22, false).Texture, 9, 54, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	UI_Game->Draw(this->Sprite, UI_Game->resource->CreateTexture(2, 23, true).Texture, 99, 9, 0, D3DCOLOR_ARGB(255, 255, 255, 255));*/
	UI_Game->Draw(this->Sprite, UI_Game->resource->CreateTexture(2, 21, true).Texture, 1, 1, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	UI_Game->Draw(this->Sprite, UI_Game->resource->CreateTexture(2, 20, true).Texture, 18, 310, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	this->map_news->Render();
	this->map_inventory->Render();
	this->map_characterstats->Render();
	this->map_gamehelp->Render();
	this->map_gamesettings->Render();
	this->map_macro->Render();
	this->map_mapUI->Render();
	this->map_party->Render();
	this->map_passiveskills->Render();
	this->map_skills->Render();
	this->map_talk->Render();
	this->map_whoisonline->Render();
	ChatTextbox->Render(this->Sprite);
	this->Sprite->End();

}
Map_UI::~Map_UI()
{
}

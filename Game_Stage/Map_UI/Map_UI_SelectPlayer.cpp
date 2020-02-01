#include "..\..\stdafx.h"
#include "Map_UI_SelectPlayer.h"
#include "Map_UI.h"
#include "Map_UI_ChatBubbleHandler.h"
#include "..\Game.h"
#include "..\..\Packet_Handler\Send\SPaperdoll.h"

vector<pair<int, int>> menudataypos;
Map_UI* Ptr_SelectPlayer_MapUI;
Game* Ptr_SelectPlayer_Game;
Map_UI_SelectPlayer::Map_UI_SelectPlayer(void* m_UIElement, void* m_Game)
{
	Ptr_SelectPlayer_MapUI = (Map_UI*)m_UIElement;
	Ptr_SelectPlayer_Game = (Game*)m_Game;

	menudataypos.push_back(pair<int, int>(10, 14));
	menudataypos.push_back(pair<int, int>(24, 14));
	menudataypos.push_back(pair<int, int>(38, 14));
	menudataypos.push_back(pair<int, int>(52, 14));
	menudataypos.push_back(pair<int, int>(66, 14));
	menudataypos.push_back(pair<int, int>(80, 17));
	menudataypos.push_back(pair<int, int>(98, 14));
	menudataypos.push_back(pair<int, int>(112, 14));
}


void Map_UI_SelectPlayer::Update()
{

	depth = 0;

	int tempplayerid = -1;

	if (playerid != -1)
	{
		int width = 96;
		int height = 136;
		RECT SrcRect;
		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + height;
		SrcRect.left = 0;
		SrcRect.right = SrcRect.left + width;
		int tilexp = ((Ptr_SelectPlayer_Game->map->m_Players[playerid]->x * 32) - (Ptr_SelectPlayer_Game->map->m_Players[playerid]->y * 32)) - Ptr_SelectPlayer_Game->map->xoff;
		int tileyp = ((Ptr_SelectPlayer_Game->map->m_Players[playerid]->x * 16) + (Ptr_SelectPlayer_Game->map->m_Players[playerid]->y * 16)) - Ptr_SelectPlayer_Game->map->yoff;
		D3DXVECTOR3* Pos = new D3DXVECTOR3(tilexp + 47, tileyp - 65, 1.0f);

		if ((Ptr_SelectPlayer_Game->MouseX > Pos->x&& Ptr_SelectPlayer_Game->MouseX < Pos->x + width) && (Ptr_SelectPlayer_Game->MouseY > Pos->y && Ptr_SelectPlayer_Game->MouseY < Pos->y + height))
		{
			int mouselocy = Ptr_SelectPlayer_Game->MouseY - Pos->y;
			this->CurrentIndex = SelectIndex::None;
			for (int i = 0; i < menudataypos.size(); i++)
			{
				if (mouselocy > menudataypos[i].first && mouselocy < menudataypos[i].first + menudataypos[i].second)
				{
					this->CurrentIndex = (SelectIndex)(i + 1);
					if (Ptr_SelectPlayer_Game->MousePressed)
					{
						switch (this->CurrentIndex)
						{
						case(SelectIndex::Paperdoll):
							{
								SPaperdoll::SendPaperdollRequest(Ptr_SelectPlayer_Game->world->connection->ClientStream, playerid, Ptr_SelectPlayer_Game);
								break;
							}
							default: break;
						}
					}

				}
			}
			this->MouseoverMenu = true;
		}
		else
		{
			this->CurrentIndex = SelectIndex::None;
			this->MouseoverMenu = false;
		}
		if (Ptr_SelectPlayer_Game->MousePressed)
		{
			this->MouseoverMenu = false;
			SelectMenuActive = false;
			playerid = -1;
		}
		delete Pos;
	}
	if (Ptr_SelectPlayer_Game->MouseRightPressed)
	{
		if (Ptr_SelectPlayer_Game->MapCursor.cursordat._CType == Map_UI_Cursor::CursorType::Player)
		{
			tempplayerid = Ptr_SelectPlayer_Game->MapCursor.cursordat.index;
		}


		if (tempplayerid != -1)
		{
			playerid = tempplayerid;
			SelectMenuActive = true;
		}
		else
		{
			SelectMenuActive = false;
			playerid = -1;
		}
	}
	else
	{
		if (Ptr_SelectPlayer_Game->MapCursor.m_CursorType != Map_UI_Cursor::CursorType::Invisible && Ptr_SelectPlayer_Game->MapCursor.cursordat._CType == Map_UI_Cursor::CursorType::Player)
		{
			Ptr_SelectPlayer_MapUI->DrawHelpMessage("Action", "Menu belongs to player " + Ptr_SelectPlayer_Game->map->m_Players[Ptr_SelectPlayer_Game->MapCursor.cursordat.index]->name);
		}
	}


}

void Map_UI_SelectPlayer::Render()
{
	if (playerid != -1)
	{	
		RECT SrcRect;
		int width = 96;
		int height = 137;
		int tilexp = ((Ptr_SelectPlayer_Game->map->m_Players[playerid]->x * 32) - (Ptr_SelectPlayer_Game->map->m_Players[playerid]->y * 32)) - Ptr_SelectPlayer_Game->map->xoff;
		int tileyp = ((Ptr_SelectPlayer_Game->map->m_Players[playerid]->x * 16) + (Ptr_SelectPlayer_Game->map->m_Players[playerid]->y * 16)) - Ptr_SelectPlayer_Game->map->yoff;

		D3DXVECTOR3* Pos = new D3DXVECTOR3(tilexp + 47, tileyp - 65, 1.0f);
		D3DXVECTOR3* Center = new D3DXVECTOR3(1, 1, 0);
		D3DCOLOR col = D3DCOLOR_ARGB(160, 255, 255, 255);

		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + height;
		SrcRect.left = 192;
		SrcRect.right = SrcRect.left + width;
		Ptr_SelectPlayer_Game->Map_UserInterface->Sprite->Draw(Ptr_SelectPlayer_Game->Map_UserInterface->map_ChatBubbleHandler->ChatBoxBG, &SrcRect, NULL, Pos, col);
		
		col = D3DCOLOR_ARGB(255 , 255, 255, 255);
		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + height;
		SrcRect.left = 0;
		SrcRect.right = SrcRect.left + width;
		Ptr_SelectPlayer_Game->Map_UserInterface->Sprite->Draw(Ptr_SelectPlayer_Game->ResourceManager->CreateTexture(2, 41, true).Texture.get(), &SrcRect, NULL, Pos, col);
	
		col = D3DCOLOR_ARGB(255, 255, 255, 255);

		switch (this->CurrentIndex)
		{
			case(0):
			{
				SrcRect.top = 10;
				SrcRect.bottom = SrcRect.top;
				SrcRect.left = 96;
				SrcRect.right = SrcRect.left;
				Pos->y += 10;
				break;
			}
			case(1):
			{
				SrcRect.top = 10;
				SrcRect.bottom = SrcRect.top + 14;
				SrcRect.left = 96;
				SrcRect.right = SrcRect.left + width;
				Pos->y += SrcRect.top;
				break;
			}
			case(2):
			{
				SrcRect.top = 23;
				SrcRect.bottom = SrcRect.top + 14;
				SrcRect.left = 96;
				SrcRect.right = SrcRect.left + width;
				Pos->y += SrcRect.top;
				break;
			}
			case(3):
			{
				SrcRect.top = 38;
				SrcRect.bottom = SrcRect.top + 14;
				SrcRect.left = 96;
				SrcRect.right = SrcRect.left + width;
				Pos->y += SrcRect.top;
				break;
			}
			case(4):
			{
				SrcRect.top = 52;
				SrcRect.bottom = SrcRect.top + 14;
				SrcRect.left = 96;
				SrcRect.right = SrcRect.left + width;
				Pos->y += SrcRect.top;
				break;
			}
			case(5):
			{
				SrcRect.top = 66;
				SrcRect.bottom = SrcRect.top + 14;
				SrcRect.left = 96;
				SrcRect.right = SrcRect.left + width;
				Pos->y += SrcRect.top;
				break;
			}
			case(6):
			{
				SrcRect.top = 80;
				SrcRect.bottom = SrcRect.top + 17;
				SrcRect.left = 96;
				SrcRect.right = SrcRect.left + width;
				Pos->y += SrcRect.top;
				break;
			}
			case(7):
			{
				SrcRect.top = 97;
				SrcRect.bottom = SrcRect.top + 14;
				SrcRect.left = 96;
				SrcRect.right = SrcRect.left + width;
				Pos->y += SrcRect.top;
				break;
			}
			case(8):
			{
				SrcRect.top = 112;
				SrcRect.bottom = SrcRect.top + 14;
				SrcRect.left = 96;
				SrcRect.right = SrcRect.left + width;
				Pos->y += SrcRect.top;
				break;
			}
		}
		Ptr_SelectPlayer_Game->Map_UserInterface->Sprite->Draw(Ptr_SelectPlayer_Game->ResourceManager->CreateTexture(2, 41, true).Texture.get(), &SrcRect, NULL, Pos, col);

		delete Pos;
		delete Center;
	}


}
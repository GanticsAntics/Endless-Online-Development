#include "..\..\stdafx.h"
#include "Map_UI_SelectPlayer.h"
#include "Map_UI.h"
#include "Map_UI_ChatBubbleHandler.h"
#include "..\game.h"
#include "..\..\Packet_Handler\Send\SPaperdoll.h"

vector<pair<int, int>> menudataypos;

Map_UI_SelectPlayer::Map_UI_SelectPlayer(Map_UI* m_UIElement, Game* p_Game)
{
	this->m_MapUI = m_UIElement;
	this->m_game = p_Game;

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
		int tilexp = ((this->m_game->map->m_Players[playerid]->x * 32) - (this->m_game->map->m_Players[playerid]->y * 32)) - this->m_game->map->xoff;
		int tileyp = ((this->m_game->map->m_Players[playerid]->x * 16) + (this->m_game->map->m_Players[playerid]->y * 16)) - this->m_game->map->yoff;
		sf::Vector3f* Pos = new sf::Vector3f(tilexp + 47, tileyp - 65, 1.0f);

		if ((this->m_game->MouseX > Pos->x&& this->m_game->MouseX < Pos->x + width) && (this->m_game->MouseY > Pos->y && this->m_game->MouseY < Pos->y + height))
		{
			int mouselocy = this->m_game->MouseY - Pos->y;
			this->CurrentIndex = SelectIndex::None;
			for (int i = 0; i < menudataypos.size(); i++)
			{
				if (mouselocy > menudataypos[i].first && mouselocy < menudataypos[i].first + menudataypos[i].second)
				{
					this->CurrentIndex = (SelectIndex)(i + 1);
					if (this->m_game->MousePressed)
					{
						switch (this->CurrentIndex)
						{
						case(SelectIndex::Paperdoll):
							{
								SPaperdoll::SendPaperdollRequest(this->m_game->world->connection->ClientStream, playerid, this->m_game);
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
		if (this->m_game->MousePressed)
		{
			this->MouseoverMenu = false;
			SelectMenuActive = false;
			playerid = -1;
		}
		delete Pos;
	}
	if (this->m_game->MouseRightPressed)
	{
		if (this->m_game->MapCursor.cursordat._CType == Map_UI_Cursor::CursorType::Player)
		{
			tempplayerid = this->m_game->MapCursor.cursordat.index;
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
		if (this->m_game->MapCursor.m_CursorType != Map_UI_Cursor::CursorType::Invisible && this->m_game->MapCursor.cursordat._CType == Map_UI_Cursor::CursorType::Player)
		{
			this->m_MapUI->DrawHelpMessage("Action", "Menu belongs to player " + this->m_game->map->m_Players[this->m_game->MapCursor.cursordat.index]->name);
		}
	}


}

void Map_UI_SelectPlayer::Render(float depth)
{
	if (playerid != -1)
	{	
		RECT SrcRect;
		int width = 96;
		int height = 137;
		int tilexp = ((this->m_game->map->m_Players[playerid]->x * 32) - (this->m_game->map->m_Players[playerid]->y * 32)) - this->m_game->map->xoff;
		int tileyp = ((this->m_game->map->m_Players[playerid]->x * 16) + (this->m_game->map->m_Players[playerid]->y * 16)) - this->m_game->map->yoff;

		sf::Vector3f* Pos = new sf::Vector3f(tilexp + 47, tileyp - 65, 1.0f);
		sf::Vector3f* Center = new sf::Vector3f(1, 1, 0);
		sf::Color col = sf::Color::Color(186, 122, 89, 133);

		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + height;
		SrcRect.left = 192;
		SrcRect.right = SrcRect.left + width;
		//this->m_game->Map_UserInterface->Sprite->Draw(this->m_game->Map_UserInterface->map_ChatBubbleHandler->ChatBoxBG, &SrcRect, NULL, Pos, col);
		this->m_game->Draw(this->m_game->Map_UserInterface->map_ChatBubbleHandler->ChatBoxBG, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), 0.02f);

		col = sf::Color::Color(255 , 255, 255, 255);
		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + height;
		SrcRect.left = 0;
		SrcRect.right = SrcRect.left + width;
		//this->m_game->Map_UserInterface->Sprite->Draw(this->m_game->ResourceManager->CreateTexture(2, 41, true)._Texture.get(), &SrcRect, NULL, Pos, col);
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 41, true), Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), 0.02f);

		col = sf::Color::Color(255, 255, 255, 255);

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
		//this->m_game->Map_UserInterface->Sprite->Draw(this->m_game->ResourceManager->CreateTexture(2, 41, true)._Texture.get(), &SrcRect, NULL, Pos, col);
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 41, true), Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), 0.02f);

		delete Pos;
		delete Center;
	}


}
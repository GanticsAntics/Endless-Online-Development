#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "Map_UI_ChatBubbleHandler.h"
#include "..\Game.h"

Map_UI* Ptr_ChatBubble_Map;
Game* Ptr_ChatBubble_Game;
Map_UI_ChatBubbleHandler::Map_UI_ChatBubbleHandler(void* m_UIElement, void* m_Game)
{
	Ptr_ChatBubble_Map = (Map_UI*)m_UIElement;
	Ptr_ChatBubble_Game = (Game*)m_Game;
	CBitmapEx BmpTop;
	
	BmpTop.Create(1, 7);
	for(int i = 0; i < 7; i++)
	{
		if (i == 0)
		{
			BmpTop.SetPixel(0, i, _RGB(0, 0, 0));
		}
		else
		{
			BmpTop.SetPixel(0, i, _RGB(255, 255, 255));
		}
	}

	DWORD cadwBufferSize = BmpTop.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	LPBYTE cabuffer;

	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);
	D3DXIMAGE_INFO cainfo = D3DXIMAGE_INFO();
	HRESULT caHr = D3DXCreateTextureFromFileInMemoryEx(Ptr_ChatBubble_Game->Map_UserInterface->m_Device, cabuffer, cadwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
	D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &cainfo, NULL, &this->ChatBox_Top);



	BmpTop.FlipVertical();
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);
	cainfo = D3DXIMAGE_INFO();
	caHr = D3DXCreateTextureFromFileInMemoryEx(Ptr_ChatBubble_Game->Map_UserInterface->m_Device, cabuffer, cadwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &cainfo, NULL, &this->ChatBox_Bottom);
	
	BmpTop.Create(7, 1);
	for (int i = 0; i < 7; i++)
	{
		if (i == 6)
		{
			BmpTop.SetPixel(i, 0, _RGB(0, 0, 0));
		}
		else
		{
			BmpTop.SetPixel(i, 0, _RGB(255, 255, 255));
		}
	}
	cadwBufferSize = BmpTop.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);
	cainfo = D3DXIMAGE_INFO();
	caHr = D3DXCreateTextureFromFileInMemoryEx(Ptr_ChatBubble_Game->Map_UserInterface->m_Device, cabuffer, cadwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
	D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &cainfo, NULL, &this->ChatBox_Right);

	BmpTop.FlipHorizontal();
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);
	cainfo = D3DXIMAGE_INFO();
	caHr = D3DXCreateTextureFromFileInMemoryEx(Ptr_ChatBubble_Game->Map_UserInterface->m_Device, cabuffer, cadwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
	D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &cainfo, NULL, &this->ChatBox_Left);

	BmpTop.Create(6, 7);
	BmpTop.Clear(_RGB(100, 100, 100));
	for (int i = 0; i < 7; i++)
	{
		if (i == 0)
		{
			BmpTop.SetPixel(i, 7, _RGB(0, 0, 0));
		}
		else
		{
			BmpTop.SetPixel(i, 7,_RGB(255, 255, 255));
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (i == 0)
		{
			BmpTop.SetPixel(i, 5, _RGB(0, 0, 0));
			BmpTop.SetPixel(i, 6, _RGB(0, 0, 0));
		}
		else
		{
			BmpTop.SetPixel(i, 5, _RGB(255, 255, 255));
			BmpTop.SetPixel(i, 6, _RGB(255, 255, 255));
		}
	}
	for (int i = 1; i < 7; i++)
	{
		if (i == 1)
		{
			BmpTop.SetPixel(i, 4, _RGB(0, 0, 0));
		}
		else
		{
			BmpTop.SetPixel(i, 4, _RGB(255, 255, 255));
		}
	}
	for (int i = 2; i < 7; i++)
	{
		if (i == 2)
		{
			BmpTop.SetPixel(i, 3, _RGB(0, 0, 0));
		}
		else
		{
			BmpTop.SetPixel(i, 3, _RGB(255, 255, 255));
		}
	}
	for (int i = 3; i < 7; i++)
	{
		if (i == 3 || i == 4)
		{
			BmpTop.SetPixel(i, 2, _RGB(0, 0, 0));
		}
		else
		{
			BmpTop.SetPixel(i, 2, _RGB(255, 255, 255));
		}
	}
	cadwBufferSize = BmpTop.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);
	cainfo = D3DXIMAGE_INFO();
	caHr = D3DXCreateTextureFromFileInMemoryEx(Ptr_ChatBubble_Game->Map_UserInterface->m_Device, cabuffer, cadwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(255,100,100,100), &cainfo, NULL, &this->ChatBox_TopLeft);


	BmpTop.FlipHorizontal();
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);
	cainfo = D3DXIMAGE_INFO();
	caHr = D3DXCreateTextureFromFileInMemoryEx(Ptr_ChatBubble_Game->Map_UserInterface->m_Device, cabuffer, cadwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(255, 100, 100, 100), &cainfo, NULL, &this->ChatBox_TopRight);

	BmpTop.FlipVertical();
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);
	cainfo = D3DXIMAGE_INFO();
	caHr = D3DXCreateTextureFromFileInMemoryEx(Ptr_ChatBubble_Game->Map_UserInterface->m_Device, cabuffer, cadwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(255, 100, 100, 100), &cainfo, NULL, &this->ChatBox_BottomRight);


	BmpTop.FlipHorizontal();
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);
	cainfo = D3DXIMAGE_INFO();
	caHr = D3DXCreateTextureFromFileInMemoryEx(Ptr_ChatBubble_Game->Map_UserInterface->m_Device, cabuffer, cadwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(255, 100, 100, 100), &cainfo, NULL, &this->ChatBox_BottomLeft);

	BmpTop.Clear(_RGB(255, 255, 255));
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);
	cainfo = D3DXIMAGE_INFO();
	caHr = D3DXCreateTextureFromFileInMemoryEx(Ptr_ChatBubble_Game->Map_UserInterface->m_Device, cabuffer, cadwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(255, 100, 100, 100), &cainfo, NULL, &this->ChatBoxBG);
}

void Map_UI_ChatBubbleHandler::Update()
{
	int counter = 0;
	for each (BubbleContainer container in this->ChatBubbleList)
	{
		time_t currenttime = clock();
		if (currenttime - container._StartTime > 3000 + (container._Message.size() * 50))
		{
			this->ChatBubbleList.erase(this->ChatBubbleList.begin() + counter);
			break;
		}
		counter++;
	}
}

void Map_UI_ChatBubbleHandler::RenderChatBubble(BubbleContainer _Message, int Index)
{
	if (!_Message._IsNPC)
	{
		if (Ptr_ChatBubble_Game->map->m_Players.find(_Message._PlayerID) != Ptr_ChatBubble_Game->map->m_Players.end())
		{
			int sizeX = _Message.Width;
			int sizeY = _Message.Height;
			int rx = (Ptr_ChatBubble_Game->map->m_Players[_Message._PlayerID]->x - Ptr_ChatBubble_Game->map->xpos);
			int ry = (Ptr_ChatBubble_Game->map->m_Players[_Message._PlayerID]->y - Ptr_ChatBubble_Game->map->ypos);
			int x = (rx * 32) - (ry * 32) + 280 + 32 - (sizeX / 2);
			int y = (ry * 16) + (rx * 16) + 170 - 65 - sizeY;

			if (_Message._PlayerID != World::WorldCharacterID)
			{
				if (Ptr_ChatBubble_Game->map->m_Players[_Message._PlayerID]->direction == 1 || Ptr_ChatBubble_Game->map->m_Players[_Message._PlayerID]->direction == 2)
				{
					x = (rx * 32) - (ry * 32) + 280 + 32 - (sizeX / 2) - Ptr_ChatBubble_Game->map->m_Players[_Message._PlayerID]->xoffset;
					y = (ry * 16) + (rx * 16) + 170 - 65 - sizeY + Ptr_ChatBubble_Game->map->m_Players[_Message._PlayerID]->yoffset;
				}
				else
				{
					x = (rx * 32) - (ry * 32) + 280 + 32 - (sizeX / 2) + Ptr_ChatBubble_Game->map->m_Players[_Message._PlayerID]->xoffset;
					y = (ry * 16) + (rx * 16) + 170 - 65 - sizeY + Ptr_ChatBubble_Game->map->m_Players[_Message._PlayerID]->yoffset;
				}
				if (Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->direction == 1 || Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->direction == 2)
				{
					x += Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->xoffset;
					y -= Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->yoffset;
				}
				else
				{
					x -= Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->xoffset;
					y -= Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->yoffset;
				}
			}
			D3DXVECTOR3* Pos = new D3DXVECTOR3(x, y, 0.5 + (0.0001 * Index));
			D3DXVECTOR3 * Center = new D3DXVECTOR3(1, 1, 0);
			RECT SrcRect;
			D3DCOLOR col = _Message.BG_color;

			SrcRect.top = 0;
			SrcRect.bottom = 7;
			SrcRect.left = 0;
			SrcRect.right = 7 + sizeX;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_Top, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 7 + sizeY;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x += 7 + sizeX;
			Pos->y += 8;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_Right, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 7 + sizeY;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x -= 14 + sizeX;;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_Left, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 7;
			SrcRect.left = 0;
			SrcRect.right = 7 + +sizeX;
			Pos->x += 7;
			Pos->y += 6 + sizeY;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_Bottom, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 8;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x = x - 7;
			Pos->y = y;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_TopLeft, &SrcRect, Center, Pos, col);

			Pos->x += 14 + sizeX;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_TopRight, &SrcRect, Center, Pos, col);


			Pos->y += 15 + sizeY;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_BottomRight, &SrcRect, Center, Pos, col);


			Pos->x -= 14 + sizeX;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_BottomLeft, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = sizeY + 7;
			SrcRect.left = 0;
			SrcRect.right = sizeX + 7;
			Pos->x = x;
			Pos->y = y + 7;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBoxBG, &SrcRect, Center, Pos, col);

			SrcRect.top = Pos->y + 2;
			SrcRect.bottom = SrcRect.top + sizeY + 7;
			SrcRect.left = Pos->x + 1;
			SrcRect.right = SrcRect.left + sizeX + 7;

			D3DXMATRIX newmatrix;
			D3DXMATRIX originalMatrix;
			D3DXMatrixTranslation(&newmatrix, NULL, NULL, 0.5 + (0.0001 * Index));
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->GetTransform(&originalMatrix);
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->SetTransform(&newmatrix);
			Ptr_ChatBubble_Game->MessageFont->DrawTextA(Ptr_ChatBubble_Game->Map_UserInterface->Sprite, _Message._Message.c_str(), -1, &SrcRect, DT_LEFT, _Message.TextCol_color);
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->SetTransform(&originalMatrix);
			delete Pos;
			delete Center;
		}
	}
	else
	{
		if (Ptr_ChatBubble_Game->map->m_NPCs.find(_Message._PlayerID) != Ptr_ChatBubble_Game->map->m_NPCs.end())
		{
			int sizeX = _Message.Width;
			int sizeY = _Message.Height;
			int rx = (Ptr_ChatBubble_Game->map->m_NPCs[_Message._PlayerID]->x - Ptr_ChatBubble_Game->map->xpos);
			int ry = (Ptr_ChatBubble_Game->map->m_NPCs[_Message._PlayerID]->y - Ptr_ChatBubble_Game->map->ypos);
			int x = (rx * 32) - (ry * 32) + 280 + 32 - (sizeX / 2);
			int y = (ry * 16) + (rx * 16) + 170 - 70 - sizeY;

				if (Ptr_ChatBubble_Game->map->m_NPCs[_Message._PlayerID]->direction == 1 || Ptr_ChatBubble_Game->map->m_NPCs[_Message._PlayerID]->direction == 2)
				{
					x = (rx * 32) - (ry * 32) + 280 + 32 - (sizeX / 2) - Ptr_ChatBubble_Game->map->m_NPCs[_Message._PlayerID]->xoffset;
					y = (ry * 16) + (rx * 16) + 170 - 65 - sizeY + Ptr_ChatBubble_Game->map->m_NPCs[_Message._PlayerID]->yoffset;
				}
				else
				{
					x = (rx * 32) - (ry * 32) + 280 + 32 - (sizeX / 2) + Ptr_ChatBubble_Game->map->m_NPCs[_Message._PlayerID]->xoffset;
					y = (ry * 16) + (rx * 16) + 170 - 65 - sizeY + Ptr_ChatBubble_Game->map->m_NPCs[_Message._PlayerID]->yoffset;
				}
				if (Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->direction == 1 || Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->direction == 2)
				{
					x += Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->xoffset;
					y -= Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->yoffset;
				}
				else
				{
					x -= Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->xoffset;
					y -= Ptr_ChatBubble_Game->map->m_Players[World::WorldCharacterID]->yoffset;
				}
			
			D3DXVECTOR3* Pos = new D3DXVECTOR3(x, y, 0.5 + (0.0001 * Index));
			D3DXVECTOR3 * Center = new D3DXVECTOR3(1, 1, 0);
			RECT SrcRect;
			D3DCOLOR col = _Message.BG_color;

			SrcRect.top = 0;
			SrcRect.bottom = 7;
			SrcRect.left = 0;
			SrcRect.right = 7 + sizeX;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_Top, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 7 + sizeY;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x += 7 + sizeX;
			Pos->y += 8;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_Right, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 7 + sizeY;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x -= 14 + sizeX;;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_Left, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 7;
			SrcRect.left = 0;
			SrcRect.right = 7 + +sizeX;
			Pos->x += 7;
			Pos->y += 6 + sizeY;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_Bottom, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 8;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x = x - 7;
			Pos->y = y;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_TopLeft, &SrcRect, Center, Pos, col);

			Pos->x += 14 + sizeX;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_TopRight, &SrcRect, Center, Pos, col);


			Pos->y += 15 + sizeY;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_BottomRight, &SrcRect, Center, Pos, col);


			Pos->x -= 14 + sizeX;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBox_BottomLeft, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = sizeY + 7;
			SrcRect.left = 0;
			SrcRect.right = sizeX + 7;
			Pos->x = x;
			Pos->y = y + 7;
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->Draw(this->ChatBoxBG, &SrcRect, Center, Pos, col);

			SrcRect.top = Pos->y + 2;
			SrcRect.bottom = SrcRect.top + sizeY + 7;
			SrcRect.left = Pos->x + 1;
			SrcRect.right = SrcRect.left + sizeX + 7;

			D3DXMATRIX newmatrix;
			D3DXMATRIX originalMatrix;
			D3DXMatrixTranslation(&newmatrix, NULL, NULL, 0.5 + (0.0001 * Index));
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->GetTransform(&originalMatrix);
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->SetTransform(&newmatrix);
			Ptr_ChatBubble_Game->MessageFont->DrawTextA(Ptr_ChatBubble_Game->Map_UserInterface->Sprite, _Message._Message.c_str(), -1, &SrcRect, DT_LEFT, _Message.TextCol_color);
			Ptr_ChatBubble_Game->Map_UserInterface->Sprite->SetTransform(&originalMatrix);
			delete Pos;
			delete Center;
		}
	}
}
void Map_UI_ChatBubbleHandler::Render()
{
	int counter = 0;
	for each (BubbleContainer container in this->ChatBubbleList)
	{
		this->RenderChatBubble(container, this->ChatBubbleList.size() - counter);
		counter++;
	}
}

void Map_UI_ChatBubbleHandler::AddMapMessage(std::string Message, int PlayerID, bool IsNPC , D3DCOLOR BG_color, D3DCOLOR TextCol_color)
{
	int counter = 0;
	for each (BubbleContainer container in this->ChatBubbleList)
	{
		if (container._PlayerID == PlayerID)
		{
			this->ChatBubbleList.erase(this->ChatBubbleList.begin() + counter);
			AddMapMessage(Message, PlayerID, IsNPC, BG_color, TextCol_color);
			return;
		}
		counter++;
	}

	std::string _Message = TextTools::SnipMessageTextToWidth(Message, 110, Ptr_ChatBubble_Game->MessageFont);
	RECT rcRect = { 0,0,0,0 };

	Ptr_ChatBubble_Game->MessageFont->DrawTextA(NULL, _Message.c_str(), _Message.size(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	BubbleContainer newcontainer;
	newcontainer._IsNPC = IsNPC;
	newcontainer.Height = rcRect.bottom;
	newcontainer.Width = rcRect.right;
	newcontainer._Message = _Message;
	newcontainer._PlayerID = PlayerID;
	newcontainer._StartTime = clock();
	newcontainer.BG_color = BG_color;
	newcontainer.TextCol_color = TextCol_color;
	this->ChatBubbleList.push_back(newcontainer);
}

Map_UI_ChatBubbleHandler::~Map_UI_ChatBubbleHandler()
{

}


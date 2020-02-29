#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "Map_UI_ChatBubbleHandler.h"

Map_UI_ChatBubbleHandler::Map_UI_ChatBubbleHandler(Map_UI* m_UIElement, Game* p_Game)
{
	this->m_MapUI = m_UIElement;
	this->m_game = p_Game;
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

	sf::Image resimage;
	resimage.loadFromMemory(cabuffer, cadwBufferSize);
	resimage.createMaskFromColor(sf::Color(100, 100, 100));
	this->ChatBox_Top = new Resource_Manager::TextureData();
	this->ChatBox_Top->_Sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	this->ChatBox_Top->_Texture = std::shared_ptr<sf::Texture>(new sf::Texture());
	this->ChatBox_Top->_Texture->loadFromImage(resimage);
	this->ChatBox_Top->_Texture->setRepeated(true);
	this->ChatBox_Top->_TextureID = 0;
	this->ChatBox_Top->_height = BmpTop.GetHeight();
	this->ChatBox_Top->_width = BmpTop.GetWidth();
	this->ChatBox_Top->_Sprite->setTexture(*this->ChatBox_Top->_Texture);
	free(cabuffer);

	BmpTop.Create(7, 1);
	for (int i = 0; i < 7; i++)
	{
		if (i == 0)
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

	resimage.loadFromMemory(cabuffer, cadwBufferSize);
	resimage.createMaskFromColor(sf::Color(100, 100, 100));
	this->ChatBox_Left = new Resource_Manager::TextureData();
	this->ChatBox_Left->_Sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	this->ChatBox_Left->_Texture = std::shared_ptr<sf::Texture>(new sf::Texture());
	this->ChatBox_Left->_Texture->loadFromImage(resimage);
	this->ChatBox_Left->_Texture->setRepeated(true);
	this->ChatBox_Left->_TextureID = 0;
	this->ChatBox_Left->_height = BmpTop.GetHeight();
	this->ChatBox_Left->_width = BmpTop.GetWidth();
	this->ChatBox_Left->_Sprite->setTexture(*this->ChatBox_Left->_Texture);
	free(cabuffer);

	
	BmpTop.Create(6, 7);
	BmpTop.Clear(_RGB(100, 100, 100));

	for (int i = 0; i < 7; i++)
	{
		if (i == 0)
		{
			BmpTop.SetPixel(i, 5, _RGB(0, 0, 0));
			BmpTop.SetPixel(i, 6, _RGB(0, 0, 0));
			BmpTop.SetPixel(i, 7, _RGB(0, 0, 0));
		}
		else
		{
			BmpTop.SetPixel(i, 5, _RGB(255, 255, 255));
			BmpTop.SetPixel(i, 6, _RGB(255, 255, 255));
			BmpTop.SetPixel(i, 7, _RGB(255, 255, 255));
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
	BmpTop.SetPixel(5, 1, _RGB(0, 0, 0));
	BmpTop.SetPixel(6, 1, _RGB(0, 0, 0));

	cadwBufferSize = BmpTop.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);

	resimage.loadFromMemory(cabuffer, cadwBufferSize);
	resimage.createMaskFromColor(sf::Color(100, 100, 100));
	this->ChatBox_TopLeft = new Resource_Manager::TextureData();
	this->ChatBox_TopLeft->_Sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	this->ChatBox_TopLeft->_Texture = std::shared_ptr<sf::Texture>(new sf::Texture());
	this->ChatBox_TopLeft->_Texture->loadFromImage(resimage);
	this->ChatBox_TopLeft->_TextureID = 0;
	this->ChatBox_TopLeft->_height = BmpTop.GetHeight();
	this->ChatBox_TopLeft->_width = BmpTop.GetWidth();
	this->ChatBox_TopLeft->_Sprite->setTexture(*this->ChatBox_TopLeft->_Texture);
	free(cabuffer);

	BmpTop.FlipVertical();
	cadwBufferSize = BmpTop.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);

	resimage.loadFromMemory(cabuffer, cadwBufferSize);
	resimage.createMaskFromColor(sf::Color(100, 100, 100));
	this->ChatBox_BottomLeft = new Resource_Manager::TextureData();
	this->ChatBox_BottomLeft->_Sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	this->ChatBox_BottomLeft->_Texture = std::shared_ptr<sf::Texture>(new sf::Texture());
	this->ChatBox_BottomLeft->_Texture->loadFromImage(resimage);
	this->ChatBox_BottomLeft->_TextureID = 0;
	this->ChatBox_BottomLeft->_height = BmpTop.GetHeight();
	this->ChatBox_BottomLeft->_width = BmpTop.GetWidth();
	this->ChatBox_BottomLeft->_Sprite->setTexture(*this->ChatBox_BottomLeft->_Texture);
	free(cabuffer);

	BmpTop.Clear(_RGB(255, 255, 255));

	cadwBufferSize = BmpTop.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);

	resimage.loadFromMemory(cabuffer, cadwBufferSize);
	resimage.createMaskFromColor(sf::Color(100, 100, 100));
	this->ChatBoxBG = new Resource_Manager::TextureData();
	this->ChatBoxBG->_Sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	this->ChatBoxBG->_Texture = std::shared_ptr<sf::Texture>(new sf::Texture());
	this->ChatBoxBG->_Texture->loadFromImage(resimage);
	this->ChatBoxBG->_Texture->setRepeated(true);
	this->ChatBoxBG->_TextureID = 0;
	this->ChatBoxBG->_height = BmpTop.GetHeight();
	this->ChatBoxBG->_width = BmpTop.GetWidth();
	this->ChatBoxBG->_Sprite->setTexture(*this->ChatBoxBG->_Texture);
	free(cabuffer);

	BmpTop.Create(7, 10);
	BmpTop.Clear(_RGB(255, 255, 255));
	for (int i = 0; i < 7; i++)
	{
		if (i < 2 || i > 4)
		{
			BmpTop.SetPixel(i, 10, _RGB(100, 100, 100));
			BmpTop.SetPixel(i, 9, _RGB(100, 100, 100));
		}
		else if (i == 2 || i == 4)
		{
			BmpTop.SetPixel(i, 10, _RGB(0, 0, 0));
			BmpTop.SetPixel(i, 9, _RGB(0, 0, 0));
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (i < 1 || i > 5)
		{
			BmpTop.SetPixel(i, 8, _RGB(100, 100, 100));
		}
		else if (i == 1 || i == 5)
		{
			BmpTop.SetPixel(i, 8, _RGB(0, 0, 0));
		}
	}
	BmpTop.SetPixel(0, 7, _RGB(0, 0, 0));
	BmpTop.SetPixel(6, 7, _RGB(0, 0, 0));
	cadwBufferSize = BmpTop.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	cabuffer = (LPBYTE)malloc(cadwBufferSize);
	BmpTop.Save(cabuffer);

	resimage.loadFromMemory(cabuffer, cadwBufferSize);
	resimage.createMaskFromColor(sf::Color(100, 100, 100));
	this->ChatBoxTail = new Resource_Manager::TextureData();
	this->ChatBoxTail->_Sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	this->ChatBoxTail->_Texture = std::shared_ptr<sf::Texture>(new sf::Texture());
	this->ChatBoxTail->_Texture->loadFromImage(resimage);
	this->ChatBoxTail->_TextureID = 0;
	this->ChatBoxTail->_height = BmpTop.GetHeight();
	this->ChatBoxTail->_width = BmpTop.GetWidth();
	this->ChatBoxTail->_Sprite->setTexture(*this->ChatBoxTail->_Texture);

	free(cabuffer);
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
		if (this->m_game->map->m_Players.find(_Message._PlayerID) != this->m_game->map->m_Players.end())
		{
			int sizeX = _Message.Width;
			int sizeY = _Message.Height;
			int rx = (this->m_game->map->m_Players[_Message._PlayerID]->x - this->m_game->map->xpos);
			int ry = (this->m_game->map->m_Players[_Message._PlayerID]->y - this->m_game->map->ypos);
			int x = (rx * 32) - (ry * 32) + 280 + 28 - (sizeX / 2);
			int y = (ry * 16) + (rx * 16) + 170 - 72 - sizeY;

			if (_Message._PlayerID != World::WorldCharacterID)
			{
				x = (rx * 32) - (ry * 32) + 280 + 28 - (sizeX / 2) + this->m_game->map->m_Players[_Message._PlayerID]->xoffset - this->m_game->map->m_Players[World::WorldCharacterID]->xoffset;
				y = (ry * 16) + (rx * 16) + 170 - 72 - sizeY + this->m_game->map->m_Players[_Message._PlayerID]->yoffset - this->m_game->map->m_Players[World::WorldCharacterID]->yoffset;
			}
			sf::Vector3f* Pos = new sf::Vector3f(x, y, 0.5 + (0.0001 * Index));
			sf::Vector3f * Center = new sf::Vector3f(1, 1, 0);
			RECT SrcRect;
			sf::Color col = _Message.BG_color;

			SrcRect.top = 0;
			SrcRect.bottom = 7;
			SrcRect.left = 0;
			SrcRect.right = 7 + sizeX;
			this->m_game->Draw(this->ChatBox_Top, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), 0);

			SrcRect.top = 0;
			SrcRect.bottom = 7 + sizeY;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x += 7 + sizeX;
			Pos->y += 8;
			this->m_game->Draw(this->ChatBox_Left, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(-1, 1), 0);

			SrcRect.top = 0;
			SrcRect.bottom = 7 + sizeY;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x -= 14 + sizeX;;
			this->m_game->Draw(this->ChatBox_Left, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), 0);

			SrcRect.top = 0;
			SrcRect.bottom = 7;
			SrcRect.left = 0;
			SrcRect.right = sizeX / 2;
			Pos->x += 7;
			Pos->y += 6 + sizeY;
			this->m_game->Draw(this->ChatBox_Top, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, -1), 0);
			
			this->m_game->Draw(this->ChatBoxTail, Pos->x + std::ceil(sizeX / 2), Pos->y , col, SrcRect.left, SrcRect.top, 7, 11, sf::Vector2f(1, 1), 0);

			Pos->x += 7 + SrcRect.right;
			SrcRect.right = sizeX - SrcRect.right;
			this->m_game->Draw(this->ChatBox_Top, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, -1), 0);

			SrcRect.top = 0;
			SrcRect.bottom = 8;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x = x - 7;
			Pos->y = y;
			this->m_game->Draw(this->ChatBox_TopLeft, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), 0);

			Pos->x += 14 + sizeX;
			this->m_game->Draw(this->ChatBox_TopLeft, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(-1, 1), 0);

			Pos->y += 15 + sizeY;
			this->m_game->Draw(this->ChatBox_BottomLeft, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(-1, 1), 0);

			Pos->x -= 14 + sizeX;
			this->m_game->Draw(this->ChatBox_BottomLeft, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), 0);

			SrcRect.top = 0;
			SrcRect.bottom = sizeY + 7;
			SrcRect.left = 0;
			SrcRect.right = sizeX + 7;
			Pos->x = x;
			Pos->y = y + 7;
			this->m_game->Draw(this->ChatBoxBG, Pos->x, Pos->y, col, SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), 0);

			SrcRect.top = Pos->y + 2;
			SrcRect.bottom = SrcRect.top + sizeY + 7;
			SrcRect.left = Pos->x + 1;
			SrcRect.right = SrcRect.left + sizeX + 7;

			this->m_game->DrawText(_Message._Message, SrcRect.left, SrcRect.top, _Message.TextCol_color, 9, false, 0);

			delete Pos;
			delete Center;
		}
	}
	else
	{
		if (this->m_game->map->m_NPCs.find(_Message._PlayerID) != this->m_game->map->m_NPCs.end())
		{
			int sizeX = _Message.Width;
			int sizeY = _Message.Height;
			int rx = (this->m_game->map->m_NPCs[_Message._PlayerID]->x - this->m_game->map->xpos);
			int ry = (this->m_game->map->m_NPCs[_Message._PlayerID]->y - this->m_game->map->ypos);
			int x = (rx * 32) - (ry * 32) + 280 + 32 - (sizeX / 2);
			int y = (ry * 16) + (rx * 16) + 170 - 70 - sizeY;

				if (this->m_game->map->m_NPCs[_Message._PlayerID]->direction == 1 || this->m_game->map->m_NPCs[_Message._PlayerID]->direction == 2)
				{
					x = (rx * 32) - (ry * 32) + 280 + 32 - (sizeX / 2) - this->m_game->map->m_NPCs[_Message._PlayerID]->xoffset;
					y = (ry * 16) + (rx * 16) + 170 - 65 - sizeY + this->m_game->map->m_NPCs[_Message._PlayerID]->yoffset;
				}
				else
				{
					x = (rx * 32) - (ry * 32) + 280 + 32 - (sizeX / 2) + this->m_game->map->m_NPCs[_Message._PlayerID]->xoffset;
					y = (ry * 16) + (rx * 16) + 170 - 65 - sizeY + this->m_game->map->m_NPCs[_Message._PlayerID]->yoffset;
				}
				if (this->m_game->map->m_Players[World::WorldCharacterID]->direction == 1 || this->m_game->map->m_Players[World::WorldCharacterID]->direction == 2)
				{
					x += this->m_game->map->m_Players[World::WorldCharacterID]->xoffset;
					y -= this->m_game->map->m_Players[World::WorldCharacterID]->yoffset;
				}
				else
				{
					x -= this->m_game->map->m_Players[World::WorldCharacterID]->xoffset;
					y -= this->m_game->map->m_Players[World::WorldCharacterID]->yoffset;
				}
			
			sf::Vector3f* Pos = new sf::Vector3f(x, y, 0.5 + (0.0001 * Index));
			sf::Vector3f * Center = new sf::Vector3f(1, 1, 0);
			RECT SrcRect;
			sf::Color col = _Message.BG_color;

			SrcRect.top = 0;
			SrcRect.bottom = 7;
			SrcRect.left = 0;
			SrcRect.right = 7 + sizeX;
			//this->m_game->Map_UserInterface->Sprite->Draw(this->ChatBox_Top, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 7 + sizeY;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x += 7 + sizeX;
			Pos->y += 8;
			//this->m_game->Map_UserInterface->Sprite->Draw(this->ChatBox_Right, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 7 + sizeY;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x -= 14 + sizeX;;
			//this->m_game->Map_UserInterface->Sprite->Draw(this->ChatBox_Left, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 7;
			SrcRect.left = 0;
			SrcRect.right = 7 + +sizeX;
			Pos->x += 7;
			Pos->y += 6 + sizeY;
			//this->m_game->Map_UserInterface->Sprite->Draw(this->ChatBox_Bottom, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = 8;
			SrcRect.left = 0;
			SrcRect.right = 7;
			Pos->x = x - 7;
			Pos->y = y;
			//this->m_game->Map_UserInterface->Sprite->Draw(this->ChatBox_TopLeft, &SrcRect, Center, Pos, col);

			Pos->x += 14 + sizeX;
			//this->m_game->Map_UserInterface->Sprite->Draw(this->ChatBox_TopRight, &SrcRect, Center, Pos, col);


			Pos->y += 15 + sizeY;
			//this->m_game->Map_UserInterface->Sprite->Draw(this->ChatBox_BottomRight, &SrcRect, Center, Pos, col);


			Pos->x -= 14 + sizeX;
			//this->m_game->Map_UserInterface->Sprite->Draw(this->ChatBox_BottomLeft, &SrcRect, Center, Pos, col);

			SrcRect.top = 0;
			SrcRect.bottom = sizeY + 7;
			SrcRect.left = 0;
			SrcRect.right = sizeX + 7;
			Pos->x = x;
			Pos->y = y + 7;
			//this->m_game->Map_UserInterface->Sprite->Draw(this->ChatBoxBG, &SrcRect, Center, Pos, col);

			SrcRect.top = Pos->y + 2;
			SrcRect.bottom = SrcRect.top + sizeY + 7;
			SrcRect.left = Pos->x + 1;
			SrcRect.right = SrcRect.left + sizeX + 7;

			//D3DXMATRIX newmatrix;
			//D3DXMATRIX originalMatrix;
			//D3DXMatrixTranslation(&newmatrix, NULL, NULL, 0.5 + (0.0001 * Index));
			//this->m_game->Map_UserInterface->Sprite->GetTransform(&originalMatrix);
			//this->m_game->Map_UserInterface->Sprite->SetTransform(&newmatrix);
			//this->m_game->MessageFont->DrawTextA(this->m_game->Map_UserInterface->Sprite, _Message._Message.c_str(), -1, &SrcRect, DT_LEFT, _Message.TextCol_color);
			//this->m_game->Map_UserInterface->Sprite->SetTransform(&originalMatrix);
			delete Pos;
			delete Center;
		}
	}
}
void Map_UI_ChatBubbleHandler::Render(float depth)
{
	int counter = 0;
	for each (BubbleContainer container in this->ChatBubbleList)
	{
		this->RenderChatBubble(container, this->ChatBubbleList.size() - counter);
		counter++;
	}
}

void Map_UI_ChatBubbleHandler::AddMapMessage(std::string Message, int PlayerID, bool IsNPC , sf::Color BG_color, sf::Color TextCol_color)
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

	std::string _Message = TextTools::SnipMessageTextToWidth(Message, 160,9, this->m_game);
	RECT rcRect = { 0,0,0,0 };
	sf::Vector2f messagesize = this->m_game->GetFontSize(_Message, 9);
	//this->m_game->MessageFont->DrawTextA(NULL, _Message.c_str(), _Message.size(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	BubbleContainer newcontainer;
	newcontainer._IsNPC = IsNPC;
	newcontainer.Height = messagesize.y;
	newcontainer.Width = messagesize.x;
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


#include "..\Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_Talk_MapUI;
Game* Ptr_Talk_Game;

void Map_UI_Talk::ActivateChatButton(int m_Index)
{
	int counter = 0;
	for (int i = 0; i < 2; i++)
	{
		if (counter == m_Index)
		{
			counter++;
			continue;
		}
		UI_WhisperChatButtons[i]->Element_Deactivate();
		counter++;
	}

	for (int i = 0; i < 4; i++)
	{
		if (counter == m_Index)
		{
			counter++;
			continue;
		}
		UI_ChatButtons[i]->Element_Deactivate();
		counter++;
	}
}
Map_UI_Talk::Map_UI_Talk(void* m_UIElement, void* m_Game)
{
	Ptr_Talk_MapUI = (Map_UI*)m_UIElement;
	Ptr_Talk_Game = (Game*)m_Game;

	this->UI_Element_TalkButton = new Button(m_Game, 62, 410, 0, 76, 36, 19, false, Ptr_Talk_Game->resource->CreateTexture(2, 25, false).Texture);
	this->UI_Element_LockText = new  Button(m_Game, 395 + (43 * 4), 433, 440, 16, 19, 16, false, Ptr_Talk_Game->resource->CreateTexture(2, 35, false).Texture);
	this->UI_Element_LockText->SetHighlightOnMouseDown(true);
	this->UI_ChatScrollbars[0] = new UI_Scrollbar(568, 333, 600, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Public], Ptr_Talk_Game->ScrollBarTexture.Texture, m_Game, Ptr_Talk_Game->MessageFont, Ptr_Talk_Game->TextIconTexture.Texture);
	this->UI_ChatScrollbars[1] = new UI_Scrollbar(568, 333, 600, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Whisper1], Ptr_Talk_Game->ScrollBarTexture.Texture, m_Game, Ptr_Talk_Game->MessageFont, Ptr_Talk_Game->TextIconTexture.Texture);
	this->UI_ChatScrollbars[2] = new UI_Scrollbar(568, 333, 600, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Whisper2], Ptr_Talk_Game->ScrollBarTexture.Texture, m_Game, Ptr_Talk_Game->MessageFont, Ptr_Talk_Game->TextIconTexture.Texture);
	this->UI_ChatScrollbars[3] = new UI_Scrollbar(568, 333, 600, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Global], Ptr_Talk_Game->ScrollBarTexture.Texture, m_Game, Ptr_Talk_Game->MessageFont, Ptr_Talk_Game->TextIconTexture.Texture);
	this->UI_ChatScrollbars[4] = new UI_Scrollbar(568, 333, 600, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Guild], Ptr_Talk_Game->ScrollBarTexture.Texture, m_Game, Ptr_Talk_Game->MessageFont, Ptr_Talk_Game->TextIconTexture.Texture);
	this->UI_ChatScrollbars[5] = new UI_Scrollbar(568, 333, 600, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::System], Ptr_Talk_Game->ScrollBarTexture.Texture, m_Game, Ptr_Talk_Game->MessageFont, Ptr_Talk_Game->TextIconTexture.Texture);

	UI_WhisperChatButtons[0] = new Button(m_Game, 123, 433, 0, 16, 132, 16, false, Ptr_Talk_Game->resource->CreateTexture(2, 35, false).Texture);
	UI_WhisperChatButtons[0]->SetHighlightOnMouseDown(true);
	UI_WhisperChatButtons[1] = new Button(m_Game, 256, 433, 0, 16, 132, 16, false, Ptr_Talk_Game->resource->CreateTexture(2, 35, false).Texture);
	UI_WhisperChatButtons[1]->SetHighlightOnMouseDown(true);
	UI_ChatButtons[0] = new Button(m_Game, 389, 433, 264, 16, 43, 16, false, Ptr_Talk_Game->resource->CreateTexture(2, 35, false).Texture);
	UI_ChatButtons[0]->SetHighlightOnMouseDown(true);
	UI_ChatButtons[1] = new Button(m_Game, 390 + (43 * 1), 433, 264, 16, 43, 16, false, Ptr_Talk_Game->resource->CreateTexture(2, 35, false).Texture);
	UI_ChatButtons[1]->SetHighlightOnMouseDown(true);
	UI_ChatButtons[2] = new Button(m_Game, 391 + (43 * 2), 433, 264, 16, 43, 16, false, Ptr_Talk_Game->resource->CreateTexture(2, 35, false).Texture);
	UI_ChatButtons[2]->SetHighlightOnMouseDown(true);
	UI_ChatButtons[3] = new Button(m_Game, 392 + (43 * 3), 433, 264, 16, 43, 16, false, Ptr_Talk_Game->resource->CreateTexture(2, 35, false).Texture);
	UI_ChatButtons[3]->SetHighlightOnMouseDown(true);
}

void Map_UI_Talk::Update()
{
	this->UI_Element_TalkButton->Update(Ptr_Talk_MapUI->MouseX, Ptr_Talk_MapUI->MouseY, Ptr_Talk_MapUI->MousePressed);
	if (this->UI_Element_TalkButton->MouseClickedOnElement())
	{
		Ptr_Talk_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Talk);
	}
	switch (Ptr_Talk_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Talk):
	{
		for (int i = 0; i < 6; i++)
		{
			this->UI_ChatScrollbars[i]->Update(Ptr_Talk_MapUI->MouseX, Ptr_Talk_MapUI->MouseY, Ptr_Talk_MapUI->MousePressed, Ptr_Talk_MapUI->MouseHeld, Ptr_Talk_Game->FPS);
		}
		this->UI_Element_LockText->Update(Ptr_Talk_MapUI->MouseX, Ptr_Talk_MapUI->MouseY, Ptr_Talk_MapUI->MousePressed);
		for (int i = 0; i < 2; i++)
		{
			if (TextTools::ChatGroups[(i + 1)]->size() > 0)
			{
				
				UI_WhisperChatButtons[i]->Update(Ptr_Talk_MapUI->MouseX, Ptr_Talk_MapUI->MouseY, Ptr_Talk_MapUI->MousePressed);
				if (UI_WhisperChatButtons[i]->MouseClickedOnElement())
				{
					ChatIndex = 1 + i;
					this->ActivateChatButton(i);
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			UI_ChatButtons[i]->Update(Ptr_Talk_MapUI->MouseX, Ptr_Talk_MapUI->MouseY, Ptr_Talk_MapUI->MousePressed);
			if (UI_ChatButtons[i]->MouseClickedOnElement())
			{	
				this->ActivateChatButton(2 + i);
				if (i == 0)
				{
					ChatIndex = 0;
				}
				else
				{
					ChatIndex = i + 2;
				}
			}
		}
		break;
	}
	default:
		return;
	}
}

void Map_UI_Talk::Render()
{
	this->UI_Element_TalkButton->Draw(Ptr_Talk_MapUI->Sprite);
	switch (Ptr_Talk_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Talk):
	{
		Ptr_Talk_Game->Draw(Ptr_Talk_MapUI->Sprite, Ptr_Talk_Game->resource->CreateTexture(2, 28, false).Texture, 102, 332, 0.1f, D3DCOLOR_ARGB(255, 255, 255, 255));
		this->UI_ChatScrollbars[this->ChatIndex]->Draw(Ptr_Talk_MapUI->Sprite);

		UI_ChatButtons[0]->Draw(Ptr_Talk_MapUI->Sprite);
		UI_ChatButtons[1]->Draw(Ptr_Talk_MapUI->Sprite);
		UI_ChatButtons[2]->Draw(Ptr_Talk_MapUI->Sprite);
		UI_ChatButtons[3]->Draw(Ptr_Talk_MapUI->Sprite);
		this->UI_Element_LockText->Draw(Ptr_Talk_MapUI->Sprite);

		if (TextTools::ChatGroups[1]->size() > 0)
		{

			UI_WhisperChatButtons[0]->Draw(Ptr_Talk_MapUI->Sprite);
			int x = 145;
			int y = 435;
			RECT rct;
			rct.left = x;
			rct.right = x + 200;
			rct.top = y;
			rct.bottom = y + 50;
			std::string m_message = "PlayerName";
			if (ChatIndex == 1)
			{
				Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
			}
		}

		if (TextTools::ChatGroups[2]->size() > 0)
		{
			UI_WhisperChatButtons[1]->Draw(Ptr_Talk_MapUI->Sprite);
			int x = 145 + 133;
			int y = 435;
			RECT rct;
			rct.left = x;
			rct.right = x + 200;
			rct.top = y;
			rct.bottom = y + 50;
			std::string m_message = "PlayerName";
			if (ChatIndex == 2)
			{
				Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
			}
		}

		int x = 408;
		int y = 435;
		RECT rct;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		std::string m_message = "All";
		if (ChatIndex == 0)
		{
			Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		}
		
		x = 449;
		y = 435;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = "Glbl";

		if (ChatIndex == 3)
		{
			Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		}

		x = 491;
		y = 435;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = "Guild";

		if (ChatIndex == 4)
		{
			Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		}
		x = 535;
		y = 435;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = "Info";

		if (ChatIndex == 5)
		{
			Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			Ptr_Talk_Game->MessageFont->DrawTextA(Ptr_Talk_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		}
		break;
	}
	default:
		return;
	}
}

Map_UI_Talk::~Map_UI_Talk()
{

}

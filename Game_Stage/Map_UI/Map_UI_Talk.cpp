#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\game.h"


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
Map_UI_Talk::Map_UI_Talk(Map_UI* m_UIElement, Game* m_Game)
{
	this->m_MapUI = m_UIElement;
	this->m_game = m_Game;

	this->UI_Element_TalkButton = new Button(this->m_game, 62, 410, 0, 76, 36, 19, false, this->m_game->ResourceManager->GetResource(2, 25, false));
	this->UI_Element_LockText = new  Button(this->m_game, 395 + (43 * 4), 433, 440, 16, 19, 16, false, this->m_game->ResourceManager->GetResource(2, 35, false));
	this->UI_Element_LockText->SetHighlightOnMouseDown(true);
	this->UI_ChatScrollbars[0] = new UI_Scrollbar(568, 333, 400, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Public], this->m_game->ResourceManager->GetResource(2, 29, false), this->m_game, this->m_game->MessageFont, this->m_game->ResourceManager->GetResource(2, 32, true));
	this->UI_ChatScrollbars[1] = new UI_Scrollbar(568, 333, 400, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Whisper1], this->m_game->ResourceManager->GetResource(2, 29, false), this->m_game, this->m_game->MessageFont, this->m_game->ResourceManager->GetResource(2, 32, true));
	this->UI_ChatScrollbars[2] = new UI_Scrollbar(568, 333, 400, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Whisper2], this->m_game->ResourceManager->GetResource(2, 29, false), this->m_game, this->m_game->MessageFont, this->m_game->ResourceManager->GetResource(2, 32, true));
	this->UI_ChatScrollbars[3] = new UI_Scrollbar(568, 333, 400, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Global], this->m_game->ResourceManager->GetResource(2, 29, false), this->m_game, this->m_game->MessageFont, this->m_game->ResourceManager->GetResource(2, 32, true));
	this->UI_ChatScrollbars[4] = new UI_Scrollbar(568, 333, 400, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::Guild], this->m_game->ResourceManager->GetResource(2, 29, false), this->m_game, this->m_game->MessageFont, this->m_game->ResourceManager->GetResource(2, 32, true));
	this->UI_ChatScrollbars[5] = new UI_Scrollbar(568, 333, 400, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::System], this->m_game->ResourceManager->GetResource(2, 29, false), this->m_game, this->m_game->MessageFont, this->m_game->ResourceManager->GetResource(2, 32, true));

	UI_WhisperChatButtons[0] = new Button(this->m_game, 123, 433, 0, 16, 132, 16, false, this->m_game->ResourceManager->GetResource(2, 35, false));
	UI_WhisperChatButtons[0]->SetHighlightOnMouseDown(true);
	UI_WhisperChatButtons[1] = new Button(this->m_game, 256, 433, 0, 16, 132, 16, false, this->m_game->ResourceManager->GetResource(2, 35, false));
	UI_WhisperChatButtons[1]->SetHighlightOnMouseDown(true);
	UI_ChatButtons[0] = new Button(this->m_game, 389, 433, 264, 16, 43, 16, false, this->m_game->ResourceManager->GetResource(2, 35, false));
	UI_ChatButtons[0]->SetHighlightOnMouseDown(true);
	UI_ChatButtons[1] = new Button(this->m_game, 390 + (43 * 1), 433, 264, 16, 43, 16, false, this->m_game->ResourceManager->GetResource(2, 35, false));
	UI_ChatButtons[1]->SetHighlightOnMouseDown(true);
	UI_ChatButtons[2] = new Button(this->m_game, 391 + (43 * 2), 433, 264, 16, 43, 16, false, this->m_game->ResourceManager->GetResource(2, 35, false));
	UI_ChatButtons[2]->SetHighlightOnMouseDown(true);
	UI_ChatButtons[3] = new Button(this->m_game, 392 + (43 * 3), 433, 264, 16, 43, 16, false, this->m_game->ResourceManager->GetResource(2, 35, false));
	UI_ChatButtons[3]->SetHighlightOnMouseDown(true);
}

void Map_UI_Talk::Update()
{
	this->UI_Element_TalkButton->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	if (this->UI_Element_TalkButton->MouseClickedOnElement())
	{
		this->m_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Talk);
	}
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Talk):
	{
		for (int i = 0; i < 6; i++)
		{
			this->UI_ChatScrollbars[i]->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_game->MouseWheelVal, this->m_MapUI->MousePressed, this->m_MapUI->MouseHeld, this->m_game->FPS);
		}
		this->UI_Element_LockText->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
		for (int i = 0; i < 2; i++)
		{
			if (TextTools::ChatGroups[(i + 1)]->size() > 0)
			{
				
				UI_WhisperChatButtons[i]->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
				if (UI_WhisperChatButtons[i]->MouseClickedOnElement())
				{
					ChatIndex = 1 + i;
					this->ActivateChatButton(i);
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			UI_ChatButtons[i]->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
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

void Map_UI_Talk::Render(float depth)
{
	this->UI_Element_TalkButton->Draw(depth);

	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Talk):
	{
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 28, true), 101, 331, sf::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
		this->UI_ChatScrollbars[this->ChatIndex]->Draw(depth);

		UI_ChatButtons[0]->Draw(depth);
		UI_ChatButtons[1]->Draw(depth);
		UI_ChatButtons[2]->Draw(depth);
		UI_ChatButtons[3]->Draw(depth);
		this->UI_Element_LockText->Draw(depth);

		if (TextTools::ChatGroups[1]->size() > 0)
		{

			UI_WhisperChatButtons[0]->Draw(depth);
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
				this->m_game->DrawTextW(m_message, rct.left, rct.top,sf::Color(255, 255, 255, 255), 10, false, depth, 1);
			}
			else
			{
				this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(0, 0, 0, 255), 10, false, depth, 1);
			}
		}

		if (TextTools::ChatGroups[2]->size() > 0)
		{
			UI_WhisperChatButtons[1]->Draw(depth);
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
				this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 10, false, depth, 1);
			}
			else
			{
				this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 10, false, depth, 1);
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
			this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 10, false, depth, 1);
		}
		else
		{
			this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 10, false, depth, 1);
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
			this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 10, false, depth, 1);
		}
		else
		{
			this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 10, false, depth, 1);
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
			this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 10, false, depth, 1);
		}
		else
		{
			this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 10, false, depth, 1);
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
			this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 9, false, depth, 1);
		}
		else
		{
			this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 255), 9, false, depth, 1);
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

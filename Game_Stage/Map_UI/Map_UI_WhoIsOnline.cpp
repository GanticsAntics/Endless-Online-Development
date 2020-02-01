#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\Game.h"
#include "..\..\Packet_Handler\Send\SPlayers.h"

Map_UI* Ptr_WhoIsOnline_MapUI;
Game* Ptr_WhoIsOnline_Game;

time_t WhosisOnlineStartTimer, WhoisOnlineEndTimer;
Map_UI_WhoIsOnline::Map_UI_WhoIsOnline(void* m_UIElement, void* m_Game)
{
	Ptr_WhoIsOnline_MapUI = (Map_UI*)m_UIElement;
	Ptr_WhoIsOnline_Game = (Game*)m_Game;

	this->UI_Element_WhoIsOnlineButton = new Button(m_Game, 590, 350, 0, 114, 36, 19, false, Ptr_WhoIsOnline_Game->ResourceManager->CreateTexture(2, 25, false).Texture);

	this->UI_WhoisOnlineScrollbar = new UI_Scrollbar(568, 351, 600, 117, -445, 0, 82, TextTools::ChatGroups[TextTools::ChatIndex::WhoIsOnline], Ptr_WhoIsOnline_Game->ScrollBarTexture.Texture, m_Game, Ptr_WhoIsOnline_Game->MessageFont, Ptr_WhoIsOnline_Game->TextIconTexture.Texture);
	WhosisOnlineStartTimer = clock();
}

void Map_UI_WhoIsOnline::Update()
{
	this->UI_Element_WhoIsOnlineButton->Update(Ptr_WhoIsOnline_MapUI->MouseX, Ptr_WhoIsOnline_MapUI->MouseY, Ptr_WhoIsOnline_MapUI->MousePressed);
	if (this->UI_Element_WhoIsOnlineButton->MouseClickedOnElement())
	{
		Ptr_WhoIsOnline_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_WhoIsOnline);
		SPlayers::SendPlayerListRequest(Ptr_WhoIsOnline_Game->world->connection->ClientStream, Ptr_WhoIsOnline_Game);
	}
	switch (Ptr_WhoIsOnline_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_WhoIsOnline):
	{
		WhoisOnlineEndTimer = clock();
		this->UI_WhoisOnlineScrollbar->Update(Ptr_WhoIsOnline_MapUI->MouseX, Ptr_WhoIsOnline_MapUI->MouseY, Ptr_WhoIsOnline_Game->MouseWheelVal, Ptr_WhoIsOnline_MapUI->MousePressed, Ptr_WhoIsOnline_MapUI->MouseHeld, Ptr_WhoIsOnline_Game->FPS);
		if (WhoisOnlineEndTimer - WhosisOnlineStartTimer > 1000)
		{
			WhosisOnlineStartTimer = clock();
			TextTools::ChatGroups[TextTools::ChatIndex::WhoIsOnline]->clear();
			for (int i = 0; i < World::OnlinePlayers.size(); i++)
			{
				TextTools::ChatContainer newcontainer;
				//newcontainer.CharacterName = World::OnlinePlayers[i]._Name;
				newcontainer.Chat_Icon = 9 + (World::OnlinePlayers[i]._Icon / 5);
				newcontainer.Message.push_back(World::OnlinePlayers[i]._Name);
				TextTools::ChatGroups[TextTools::ChatIndex::WhoIsOnline]->push_back(newcontainer);
			}
		}
		break;
	}
	default:
		return;
	}
}

void Map_UI_WhoIsOnline::Render()
{
	this->UI_Element_WhoIsOnlineButton->Draw(Ptr_WhoIsOnline_MapUI->Sprite);
	switch (Ptr_WhoIsOnline_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_WhoIsOnline):
	{
		Ptr_WhoIsOnline_Game->Draw(Ptr_WhoIsOnline_MapUI->Sprite, Ptr_WhoIsOnline_Game->ResourceManager->CreateTexture(2, 36, false).Texture, 102, 332, 0.1f, D3DCOLOR_ARGB(255, 255, 255, 255));
		this->UI_WhoisOnlineScrollbar->Draw(Ptr_WhoIsOnline_MapUI->Sprite);
		break;
	}
	default:
		return;
	}
}

Map_UI_WhoIsOnline::~Map_UI_WhoIsOnline()
{

}

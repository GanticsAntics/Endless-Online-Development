#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_GameHelp_MapUI;
Game* Ptr_GameHelp_Game;
Map_UI_GameHelp::Map_UI_GameHelp(void* m_UIElement, void* m_Game)
{
	Ptr_GameHelp_MapUI = (Map_UI*)m_UIElement;
	Ptr_GameHelp_Game = (Game*)m_Game;

	this->UI_Element_GameHelpButton = new Button(m_Game, 590, 430, 0, 190, 36, 19, false, Ptr_GameHelp_Game->ResourceManager->CreateTexture(2, 25, false).Texture);
}

void Map_UI_GameHelp::Update()
{
	this->UI_Element_GameHelpButton->Update(Ptr_GameHelp_MapUI->MouseX, Ptr_GameHelp_MapUI->MouseY, Ptr_GameHelp_MapUI->MousePressed);
	if (this->UI_Element_GameHelpButton->MouseClickedOnElement())
	{
		Ptr_GameHelp_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_GameHelp, 0);
	}
	switch (Ptr_GameHelp_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_GameHelp):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_GameHelp::Render()
{
	this->UI_Element_GameHelpButton->Draw(Ptr_GameHelp_MapUI->Sprite);
	switch (Ptr_GameHelp_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_GameHelp):
	{
		Ptr_GameHelp_Game->Draw(Ptr_GameHelp_MapUI->Sprite, Ptr_GameHelp_Game->ResourceManager->CreateTexture(2, 63, false).Texture, 102, 332, 0.1f, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_GameHelp::~Map_UI_GameHelp()
{

}

#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_MapUI_MapUI;
Game* Ptr_MapUI_Game;
Map_UI_Map::Map_UI_Map(void* m_UIElement, void* m_Game)
{
	Ptr_MapUI_MapUI = (Map_UI*)m_UIElement;
	Ptr_MapUI_Game = (Game*)m_Game;

	this->UI_Element_MapButton = new Button(m_Game, 62, 350, 0, 19, 36, 19, false, Ptr_MapUI_Game->ResourceManager->CreateTexture(2, 25, false).Texture);
}

void Map_UI_Map::Update()
{
	this->UI_Element_MapButton->Update(Ptr_MapUI_MapUI->MouseX, Ptr_MapUI_MapUI->MouseY, Ptr_MapUI_MapUI->MousePressed);
	if (this->UI_Element_MapButton->MouseClickedOnElement())
	{
		//Ptr_MapUI_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Map, 0);
	}
	switch (Ptr_MapUI_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Map):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_Map::Render()
{
	this->UI_Element_MapButton->Draw(Ptr_MapUI_MapUI->Sprite);
	switch (Ptr_MapUI_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Map):
	{
		//Ptr_MapUI_Game->Draw(Ptr_MapUI_MapUI->Sprite, Ptr_MapUI_Game->ResourceManager->CreateTexture(2, 63, false).Texture, 102, 332, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_Map::~Map_UI_Map()
{

}

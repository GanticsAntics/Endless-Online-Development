#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\game.h"

Map_UI_Map::Map_UI_Map(Map_UI* m_UIElement, Game* m_Game)
{
	this->m_MapUI = m_UIElement;
	this->m_game = m_Game;

	this->UI_Element_MapButton = new Button(this->m_game, 62, 350, 0, 19, 36, 19, false, this->m_game->ResourceManager->GetResource(2, 25, false));
}

void Map_UI_Map::Update()
{
	this->UI_Element_MapButton->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	if (this->UI_Element_MapButton->MouseClickedOnElement())
	{
		//this->m_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Map, 0);
	}
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Map):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_Map::Render(float depth)
{
	this->UI_Element_MapButton->Draw();
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Map):
	{
		//this->m_game->Draw(this->m_MapUI->Sprite, this->m_game->ResourceManager->CreateTexture(2, 63, false)._Texture, 102, 332, 0, sf::Color::Color(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_Map::~Map_UI_Map()
{

}

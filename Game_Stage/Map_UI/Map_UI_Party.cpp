#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\game.h"

Map_UI_Party::Map_UI_Party(Map_UI* m_UIElement, Game* m_Game)
{
	this->m_MapUI = (Map_UI*)m_UIElement;
	this->m_game = m_Game;
	
	this->UI_Element_PartyButton = new Button(this->m_game, 590, 370, 0, 133, 36, 19, false, this->m_game->ResourceManager->GetResource(2, 25, false));
}

void Map_UI_Party::Update()
{
	this->UI_Element_PartyButton->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	if (this->UI_Element_PartyButton->MouseClickedOnElement())
	{
		this->m_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Party, 0);
	}
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Party):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_Party::Render(float depth)
{
	this->UI_Element_PartyButton->Draw();
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Party):
	{
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 42, false), 101, 331, sf::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
		break;
	}
	default:
		return;
	}
}

Map_UI_Party::~Map_UI_Party()
{

}

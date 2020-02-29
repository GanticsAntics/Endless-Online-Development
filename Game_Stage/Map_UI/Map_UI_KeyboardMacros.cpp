#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\game.h"

Map_UI_KeyboardMacros::Map_UI_KeyboardMacros(Map_UI* m_UIElement, Game* m_Game)
{
	this->m_MapUI = m_UIElement;
	this->m_game = m_Game;

	this->UI_Element_KeyboardMacrosButton = new Button(this->m_game, 590, 390, 0, 152, 36, 19, false, this->m_game->ResourceManager->GetResource(2, 25, false));
}

void Map_UI_KeyboardMacros::Update()
{
	this->UI_Element_KeyboardMacrosButton->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	if (this->UI_Element_KeyboardMacrosButton->MouseClickedOnElement())
	{
		this->m_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_KeyboardMacros, 0);
	}
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_KeyboardMacros):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_KeyboardMacros::Render(float depth)
{
	this->UI_Element_KeyboardMacrosButton->Draw();
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_KeyboardMacros):
	{
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 63, false), 101, 331, sf::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
		break;
	}
	default:
		return;
	}
}

Map_UI_KeyboardMacros::~Map_UI_KeyboardMacros()
{

}

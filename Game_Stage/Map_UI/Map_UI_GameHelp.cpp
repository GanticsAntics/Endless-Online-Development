#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\game.h"

Map_UI_GameHelp::Map_UI_GameHelp(Map_UI* m_UIElement, Game* m_Game)
{
	this->m_MapUI = m_UIElement;
	this->m_game = m_Game;

	this->UI_Element_GameHelpButton = new Button(this->m_game, 590, 430, 0, 190, 36, 19, false, this->m_game->ResourceManager->GetResource(2, 25, false));
}

void Map_UI_GameHelp::Update()
{
	this->UI_Element_GameHelpButton->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	if (this->UI_Element_GameHelpButton->MouseClickedOnElement())
	{
		this->m_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_GameHelp, 0);
	}
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_GameHelp):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_GameHelp::Render(float depth)
{
	this->UI_Element_GameHelpButton->Draw();
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_GameHelp):
	{

		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 63, false), 101, 331, sf::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
		break;
	}
	default:
		return;
	}
}

Map_UI_GameHelp::~Map_UI_GameHelp()
{

}

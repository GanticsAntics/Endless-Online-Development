#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\game.h"


Map_UI_GameSettings::Map_UI_GameSettings(Map_UI* m_UIElement, Game* p_Game)
{
	this->m_MapUI = m_UIElement;
	this->m_game = p_Game;
	this->UI_Element_GameSettingsButton = new Button(this->m_game, 590, 410, 0, 171, 36, 19, false, this->m_game->ResourceManager->GetResource(2, 25, false));
}

void Map_UI_GameSettings::Update()
{
	this->UI_Element_GameSettingsButton->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	if (this->UI_Element_GameSettingsButton->MouseClickedOnElement())
	{
		this->m_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_GameSettings, 0);
	}
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_GameSettings):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_GameSettings::Render(float depth)
{
	this->UI_Element_GameSettingsButton->Draw();
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_GameSettings):
	{
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 47, false), 101, 331, sf::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
		break;
	}
	default:
		return;
	}
}

Map_UI_GameSettings::~Map_UI_GameSettings()
{

}

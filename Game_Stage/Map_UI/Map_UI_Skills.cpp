#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\..\game.h"


Map_UI_Skills::Map_UI_Skills(Map_UI* m_UIElement, Game* m_Game)
{
	this->m_MapUI = (Map_UI*)m_UIElement;
	this->m_game = m_Game;

	this->UI_Element_SkillsButton = new Button(this->m_game, 62, 370, 0, 38, 36, 19, false, this->m_game->ResourceManager->GetResource(2, 25, false));
}

void Map_UI_Skills::Update()
{
	this->UI_Element_SkillsButton->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	if (this->UI_Element_SkillsButton->MouseClickedOnElement())
	{
		this->m_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Skills, 0);
	}
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Skills):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_Skills::Render(float depth)
{
	this->UI_Element_SkillsButton->Draw();
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Skills):
	{
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 62, false), 101, 331, sf::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
		break;
	}
	default:
		return;
	}
}

Map_UI_Skills::~Map_UI_Skills()
{

}

#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\..\Game.h"
Map_UI* Ptr_PassiveSkills_MapUI;
Game* Ptr_PassiveSkills_Game;
Map_UI_PassiveSkills::Map_UI_PassiveSkills(void* m_UIElement, void* m_Game)
{
	Ptr_PassiveSkills_MapUI = (Map_UI*)m_UIElement;
	Ptr_PassiveSkills_Game = (Game*)m_Game;

	this->UI_Element_PassiveSkillsButton = new Button(m_Game, 62, 390, 0, 57, 36, 19, false, Ptr_PassiveSkills_Game->ResourceManager->CreateTexture(2, 25, false).Texture);
}

void Map_UI_PassiveSkills::Update()
{
	this->UI_Element_PassiveSkillsButton->Update(Ptr_PassiveSkills_MapUI->MouseX, Ptr_PassiveSkills_MapUI->MouseY, Ptr_PassiveSkills_MapUI->MousePressed);
	if (this->UI_Element_PassiveSkillsButton->MouseClickedOnElement())
	{
		Ptr_PassiveSkills_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_PassiveSkills, 0);
	}
	switch (Ptr_PassiveSkills_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_PassiveSkills):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_PassiveSkills::Render()
{
	this->UI_Element_PassiveSkillsButton->Draw(Ptr_PassiveSkills_MapUI->Sprite);
	switch (Ptr_PassiveSkills_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_PassiveSkills):
	{
		Ptr_PassiveSkills_Game->Draw(Ptr_PassiveSkills_MapUI->Sprite, Ptr_PassiveSkills_Game->ResourceManager->CreateTexture(2, 62, false).Texture, 102, 332, 0.1f, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_PassiveSkills::~Map_UI_PassiveSkills()
{

}

#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_Settings_MapUI;
Game* Ptr_Settings_Game;
Map_UI_GameSettings::Map_UI_GameSettings(void* m_UIElement, void* m_Game)
{
	Ptr_Settings_MapUI = (Map_UI*)m_UIElement;
	Ptr_Settings_Game = (Game*)m_Game;
	this->UI_Element_GameSettingsButton = new Button(m_Game, 590, 410, 0, 171, 36, 19, false, Ptr_Settings_Game->ResourceManager->CreateTexture(2, 25, false).Texture);
}

void Map_UI_GameSettings::Update()
{
	this->UI_Element_GameSettingsButton->Update(Ptr_Settings_MapUI->MouseX, Ptr_Settings_MapUI->MouseY, Ptr_Settings_MapUI->MousePressed);
	if (this->UI_Element_GameSettingsButton->MouseClickedOnElement())
	{
		Ptr_Settings_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_GameSettings, 0);
	}
	switch (Ptr_Settings_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_GameSettings):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_GameSettings::Render()
{
	this->UI_Element_GameSettingsButton->Draw(Ptr_Settings_MapUI->Sprite);
	switch (Ptr_Settings_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_GameSettings):
	{
		Ptr_Settings_Game->Draw(Ptr_Settings_MapUI->Sprite, Ptr_Settings_Game->ResourceManager->CreateTexture(2, 47, false).Texture, 102, 332, 0.1f, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_GameSettings::~Map_UI_GameSettings()
{

}

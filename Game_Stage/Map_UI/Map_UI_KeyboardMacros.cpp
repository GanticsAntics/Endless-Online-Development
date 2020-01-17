#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_Macro_MapUI;
Game* Ptr_Macro_Game;
Map_UI_KeyboardMacros::Map_UI_KeyboardMacros(void* m_UIElement, void* m_Game)
{
	Ptr_Macro_MapUI = (Map_UI*)m_UIElement;
	Ptr_Macro_Game = (Game*)m_Game;

	this->UI_Element_KeyboardMacrosButton = new Button(m_Game, 590, 390, 0, 152, 36, 19, false, Ptr_Macro_Game->ResourceManager->CreateTexture(2, 25, false).Texture);
}

void Map_UI_KeyboardMacros::Update()
{
	this->UI_Element_KeyboardMacrosButton->Update(Ptr_Macro_MapUI->MouseX, Ptr_Macro_MapUI->MouseY, Ptr_Macro_MapUI->MousePressed);
	if (this->UI_Element_KeyboardMacrosButton->MouseClickedOnElement())
	{
		Ptr_Macro_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_KeyboardMacros, 0);
	}
	switch (Ptr_Macro_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_KeyboardMacros):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_KeyboardMacros::Render()
{
	this->UI_Element_KeyboardMacrosButton->Draw(Ptr_Macro_MapUI->Sprite);
	switch (Ptr_Macro_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_KeyboardMacros):
	{
		//Ptr_Macro_Game->Draw(Ptr_Macro_MapUI->Sprite, Ptr_Macro_Game->ResourceManager->CreateTexture(2, 63, false).Texture, 102, 332, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_KeyboardMacros::~Map_UI_KeyboardMacros()
{

}

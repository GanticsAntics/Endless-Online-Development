#include "..\Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_CharStats_MapUI;
Game* Ptr_CharStats_Game;
Map_UI_CharacterStats::Map_UI_CharacterStats(void* m_UIElement, void* m_Game)
{
	Ptr_CharStats_MapUI = (Map_UI*)m_UIElement;
	Ptr_CharStats_Game = (Game*)m_Game;

		this->UI_Element_CharacterStatsButton = new Button(m_Game, 62, 430, 0, 95, 36, 19, false, Ptr_CharStats_Game->resource->CreateTexture(2, 25, false).Texture);
}

void Map_UI_CharacterStats::Update()
{
	this->UI_Element_CharacterStatsButton->Update(Ptr_CharStats_MapUI->MouseX, Ptr_CharStats_MapUI->MouseY, Ptr_CharStats_MapUI->MousePressed);
	if (this->UI_Element_CharacterStatsButton->MouseClickedOnElement())
	{
		Ptr_CharStats_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_CharacterStats, 0);
	}
	switch (Ptr_CharStats_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_CharacterStats):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_CharacterStats::Render()
{
	this->UI_Element_CharacterStatsButton->Draw(Ptr_CharStats_MapUI->Sprite);
	switch (Ptr_CharStats_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_CharacterStats):
	{
		Ptr_CharStats_Game->Draw(Ptr_CharStats_MapUI->Sprite, Ptr_CharStats_Game->resource->CreateTexture(2, 34, false).Texture, 102, 332, 0.1f, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_CharacterStats::~Map_UI_CharacterStats()
{

}

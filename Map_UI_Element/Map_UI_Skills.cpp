#include "..\Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_Skills_MapUI;
Game* Ptr_Skills_Game;
Map_UI_Skills::Map_UI_Skills(void* m_UIElement, void* m_Game)
{
	Ptr_Skills_MapUI = (Map_UI*)m_UIElement;
	Ptr_Skills_Game = (Game*)m_Game;

	this->UI_Element_SkillsButton = new Button(m_Game, 62, 370, 0, 38, 36, 19, false, Ptr_Skills_Game->resource->CreateTexture(2, 25, false).Texture);
}

void Map_UI_Skills::Update()
{
	this->UI_Element_SkillsButton->Update(Ptr_Skills_MapUI->MouseX, Ptr_Skills_MapUI->MouseY, Ptr_Skills_MapUI->MousePressed);
	if (this->UI_Element_SkillsButton->MouseClickedOnElement())
	{
		Ptr_Skills_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Skills, 0);
	}
	switch (Ptr_Skills_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Skills):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_Skills::Render()
{
	this->UI_Element_SkillsButton->Draw(Ptr_Skills_MapUI->Sprite);
	switch (Ptr_Skills_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Skills):
	{
		Ptr_Skills_Game->Draw(Ptr_Skills_MapUI->Sprite, Ptr_Skills_Game->resource->CreateTexture(2, 62, false).Texture, 102, 332, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_Skills::~Map_UI_Skills()
{

}

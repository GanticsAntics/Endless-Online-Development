#include "..\Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_Party_MapUI;
Game* Ptr_Party_Game;
Map_UI_Party::Map_UI_Party(void* m_UIElement, void* m_Game)
{
	Ptr_Party_MapUI = (Map_UI*)m_UIElement;
	Ptr_Party_Game = (Game*)m_Game;

	this->UI_Element_PartyButton = new Button(m_Game, 590, 370, 0, 133, 36, 19, false, Ptr_Party_Game->resource->CreateTexture(2, 25, false).Texture);
}

void Map_UI_Party::Update()
{
	this->UI_Element_PartyButton->Update(Ptr_Party_MapUI->MouseX, Ptr_Party_MapUI->MouseY, Ptr_Party_MapUI->MousePressed);
	if (this->UI_Element_PartyButton->MouseClickedOnElement())
	{
		Ptr_Party_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Party, 0);
	}
	switch (Ptr_Party_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Party):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_Party::Render()
{
	this->UI_Element_PartyButton->Draw(Ptr_Party_MapUI->Sprite);
	switch (Ptr_Party_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Party):
	{
		Ptr_Party_Game->Draw(Ptr_Party_MapUI->Sprite, Ptr_Party_Game->resource->CreateTexture(2, 42, false).Texture, 102, 332, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_Party::~Map_UI_Party()
{

}

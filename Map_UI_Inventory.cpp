#include "Map_UI_Inventory.h"
#include "Map_UI.h"
#include "Game.h"
Map_UI* Ptr_Inv_MapUI;
Game* Ptr_Inv_Game;
Map_UI_Inventory::Map_UI_Inventory(void* m_UIElement, void* m_Game)
{
	Ptr_Inv_MapUI = (Map_UI *) m_UIElement;
	Ptr_Inv_Game = (Game*)m_Game;

	this->UI_Element_InventoryButton = new Button(m_Game, 62, 330, 0, 0, 36, 19, false, Ptr_Inv_Game->resource->CreateTexture(2, 25, false).Texture);
}

void Map_UI_Inventory::Update()
{
	this->UI_Element_InventoryButton->Update(Ptr_Inv_MapUI->MouseX, Ptr_Inv_MapUI->MouseY, Ptr_Inv_MapUI->MousePressed);
	if (this->UI_Element_InventoryButton->MouseClickedOnElement())
	{
		Ptr_Inv_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Inventory, 0);
	}
	switch (Ptr_Inv_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Inventory):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_Inventory::Render()
{
	this->UI_Element_InventoryButton->Draw(Ptr_Inv_MapUI->Sprite);
	switch (Ptr_Inv_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Inventory):
	{
		Ptr_Inv_Game->Draw(Ptr_Inv_MapUI->Sprite, Ptr_Inv_Game->resource->CreateTexture(2, 44, false).Texture, 102, 332, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_Inventory::~Map_UI_Inventory()
{

}

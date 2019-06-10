#pragma once
#include "Utilities/Button.h"
class Map_UI_Inventory
{
public:
	Button* UI_Element_InventoryButton;

	//Map_UI_Inventory();
	Map_UI_Inventory(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_Inventory();
};


#pragma once
#include "..\Utilities/Button.h"
class Map_UI_Map
{
public:
	Button* UI_Element_MapButton;

	//Map_UI_Inventory();
	Map_UI_Map(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_Map();
};


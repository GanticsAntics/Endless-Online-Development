#pragma once
#include "..\Utilities/Button.h"
class Map_UI_KeyboardMacros
{
public:

	Button* UI_Element_KeyboardMacrosButton;

	//Map_UI_Inventory();
	Map_UI_KeyboardMacros(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_KeyboardMacros();
};


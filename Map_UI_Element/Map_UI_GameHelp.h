#pragma once
#include "..\Utilities/Button.h"
class Map_UI_GameHelp
{
public:
	Button* UI_Element_GameHelpButton;
	//Map_UI_Inventory();
	Map_UI_GameHelp(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_GameHelp();
};


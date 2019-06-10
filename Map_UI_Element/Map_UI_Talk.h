#pragma once
#include "..\Utilities/Button.h"
#include "..\Utilities/UI_ScrollBar.h"
class Map_UI_Talk
{
public:
	Button* UI_Element_TalkButton;
	UI_Scrollbar* UI_TextScrollbar;
	//Map_UI_Inventory();
	Map_UI_Talk(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_Talk();
};


#pragma once
#include "..\Utilities/Button.h"
#include "..\Utilities/UI_ScrollBar.h"
class Map_UI_News
{

public:
	//Map_UI_Inventory();
	UI_Scrollbar* UI_TextScrollbar;
	Map_UI_News(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_News();
};


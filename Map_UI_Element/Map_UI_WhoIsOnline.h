#pragma once
#include "..\Utilities/Button.h"
#include "..\Utilities\UI_ScrollBar.h"
class Map_UI_WhoIsOnline
{
public:
	Button* UI_Element_WhoIsOnlineButton;
	UI_Scrollbar* UI_WhoisOnlineScrollbar;
	//Map_UI_Inventory();
	Map_UI_WhoIsOnline(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_WhoIsOnline();
};


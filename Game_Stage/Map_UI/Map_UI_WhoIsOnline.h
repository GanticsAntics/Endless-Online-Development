#pragma once
#include "..\Utilities/Button.h"
#include "..\Utilities\UI_ScrollBar.h"
class Map_UI_WhoIsOnline
{
private:
	Map_UI* m_MapUI;
	Game* m_game;
public:
	time_t WhosisOnlineStartTimer, WhoisOnlineEndTimer;
	Button* UI_Element_WhoIsOnlineButton;
	UI_Scrollbar* UI_WhoisOnlineScrollbar;
	//Map_UI_Inventory();
	Map_UI_WhoIsOnline(Map_UI* m_MapUI, Game* m_Game);
	void Update();
	void Render(float depth);
	~Map_UI_WhoIsOnline();
};


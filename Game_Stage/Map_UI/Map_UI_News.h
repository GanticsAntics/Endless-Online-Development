#pragma once
#include "..\Utilities/Button.h"
#include "..\Utilities/UI_ScrollBar.h"
class Map_UI_News
{
private:
	Map_UI* m_MapUI;
	Game* m_game;
public:
	//Map_UI_Inventory();
	UI_Scrollbar* UI_TextScrollbar;
	Map_UI_News(Map_UI* m_MapUI, Game* m_Game);
	void Update();
	void Render(float depth);
	~Map_UI_News();
};


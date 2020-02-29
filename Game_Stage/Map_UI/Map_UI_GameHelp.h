#pragma once
#include "..\Utilities/Button.h"
class Map_UI_GameHelp
{
private:
	Map_UI* m_MapUI;
	Game* m_game;
public:
	Button* UI_Element_GameHelpButton;
	//Map_UI_Inventory();
	Map_UI_GameHelp(Map_UI* m_MapUI, Game* m_Game);
	void Update();
	void Render(float depth);
	~Map_UI_GameHelp();
};


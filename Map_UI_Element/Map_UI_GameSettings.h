#pragma once
#include "..\Utilities/Button.h"
class Map_UI_GameSettings
{
public:
	Button* UI_Element_GameSettingsButton;

	//Map_UI_Inventory();
	Map_UI_GameSettings(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_GameSettings();
};


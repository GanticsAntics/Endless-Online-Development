#pragma once
#include "..\Utilities/Button.h"
class Map_UI_Skills
{
public:
	Button* UI_Element_SkillsButton;

	//Map_UI_Inventory();
	Map_UI_Skills(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_Skills();
};


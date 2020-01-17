#pragma once
#include "..\Utilities/Button.h"
class Map_UI_PassiveSkills
{
public:
	Button* UI_Element_PassiveSkillsButton;

	//Map_UI_Inventory();
	Map_UI_PassiveSkills(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_PassiveSkills();
};


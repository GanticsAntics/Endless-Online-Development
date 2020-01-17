#pragma once
class Map_UI_CharacterStats
{
public:
	Button* UI_Element_CharacterStatsButton;

	//Map_UI_Inventory();
	Map_UI_CharacterStats(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_CharacterStats();
};


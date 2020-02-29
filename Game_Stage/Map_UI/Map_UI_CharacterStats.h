#pragma once
class Map_UI;
class Map_UI_CharacterStats
{
private:
	Map_UI* m_MapUI;
	Game* m_game;
public:
	Button* UI_Element_CharacterStatsButton;

	//Map_UI_Inventory();
	Map_UI_CharacterStats(Map_UI* m_MapUI, Game* m_Game);
	void Update();
	void Render(float depth);
	~Map_UI_CharacterStats();
};


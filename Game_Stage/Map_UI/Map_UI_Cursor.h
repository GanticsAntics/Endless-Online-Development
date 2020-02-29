#pragma once
#include "..\Map.h"
class Map_UI_Cursor : public UI_Element
{
private:
	Game* m_game;
	Map* p_Map;
	sf::RenderWindow*p_Device;
	sf::Sprite* p_Sprite;
public:
	int x = 0;
	int y = 0;

	int Height = 60;
	bool Cursor_Show = true;
	enum CursorType ///Note: Unsure if this enumerator can differentiate from other indexes
	{
		None = 0,
		Object,
		Special,
		Invisible,
		Player,
		NPC,
		Vault,
		Chest,
		Shop,
		Board,
		Bank
	};
	struct CursorDat
	{
		CursorType _CType;
		int x, y;
		int index;
	};
	CursorDat cursordat;
	std::basic_string<wchar_t> cur_istring;
	std::basic_string<char> scur_istring;
	CursorType m_CursorType;
	Map_UI_Cursor();
	Map_UI_Cursor(Game* m_Game, Map* m_Map, sf::RenderWindow*m_Device);
	~Map_UI_Cursor();
	void Update();
	void Render(sf::Sprite* m_sprite, float depth);
};


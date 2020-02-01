#pragma once

class Map_UI_SelectPlayer
{
public:
	enum SelectIndex
	{
		None = 0,
		Paperdoll = 1,
		Book = 2,
		Join = 3,
		Invite = 4,
		Trade = 5,
		Whisper = 6,
		Freind = 7,
		Ignore = 8
	};
	SelectIndex CurrentIndex = SelectIndex::None;
	bool SelectMenuActive = false;
	bool MouseoverMenu = false;
	int depth = 0;
	int playerid = -1;
	Map_UI_SelectPlayer(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
};


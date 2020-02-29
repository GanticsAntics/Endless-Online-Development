#pragma once
#include "..\Utilities/Button.h"
#include "..\Utilities/UI_ScrollBar.h"
class Map_UI_Talk
{
	void ActivateChatButton(int m_index);
private:
	Map_UI* m_MapUI;
	Game* m_game;
public:
	int ChatIndex = 0;
	Button* UI_Element_TalkButton;
	Button* UI_Element_LockText;

	UI_Scrollbar* UI_ChatScrollbars[6];
	Button* UI_WhisperChatButtons[2];
	Button* UI_ChatButtons[4];
	Map_UI_Talk(Map_UI* m_MapUI, Game* m_Game);
	void Update();
	void Render(float depth);
	~Map_UI_Talk();
};


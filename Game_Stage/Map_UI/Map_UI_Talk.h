#pragma once
#include "..\Utilities/Button.h"
#include "..\Utilities/UI_ScrollBar.h"
class Map_UI_Talk
{
	void ActivateChatButton(int m_index);
public:
	int ChatIndex = 0;
	Button* UI_Element_TalkButton;
	Button* UI_Element_LockText;

	UI_Scrollbar* UI_ChatScrollbars[6];
	Button* UI_WhisperChatButtons[2];
	Button* UI_ChatButtons[4];
	Map_UI_Talk(void* m_MapUI, void* m_Game);
	void Update();
	void Render();
	~Map_UI_Talk();
};


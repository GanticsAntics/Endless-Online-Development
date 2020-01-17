#pragma once
#include "..\Utilities/Button.h"
class Map_UI_ChatBubbleHandler
{
	struct BubbleContainer
	{
		bool _IsNPC = false;
		int Width;
		int Height;
		int _PlayerID;
		std::string _Message;
		time_t _StartTime;
		D3DCOLOR BG_color;
		D3DCOLOR TextCol_color;
	};

	void RenderChatBubble(BubbleContainer _Message, int index);
public:
	LPDIRECT3DTEXTURE9 ChatBox_TopLeft;
	LPDIRECT3DTEXTURE9 ChatBox_TopRight;
	LPDIRECT3DTEXTURE9 ChatBox_BottomLeft;
	LPDIRECT3DTEXTURE9 ChatBox_BottomRight;
	LPDIRECT3DTEXTURE9 ChatBox_Right;
	LPDIRECT3DTEXTURE9 ChatBox_Left;
	LPDIRECT3DTEXTURE9 ChatBox_Bottom;
	LPDIRECT3DTEXTURE9 ChatBox_Top;
	LPDIRECT3DTEXTURE9 ChatBoxBG;
	//Map_UI_Inventory();

	std::vector<BubbleContainer> ChatBubbleList;
	Map_UI_ChatBubbleHandler(void* m_MapUI, void* m_Game);
	void AddMapMessage(std::string Message, int PlayerID, bool IsNPC = false, D3DCOLOR BG_color = D3DCOLOR_ARGB(200,255,255,255), D3DCOLOR TextCol_color = D3DCOLOR_ARGB(200, 0, 0, 0));
	void Update();
	void Render();
	~Map_UI_ChatBubbleHandler();
};


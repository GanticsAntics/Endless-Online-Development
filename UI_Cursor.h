#pragma once
#include "Map.h"
#include "UI_Element.h"
class UI_Cursor : public UI_Element
{
private:
	Map* p_Map;
	IDirect3DDevice9Ptr p_Device;
	ID3DXSprite* p_Sprite;
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
	};
	std::basic_string<wchar_t> cur_istring;
	std::basic_string<char> scur_istring;
	CursorType m_CursorType;
	UI_Cursor();
	UI_Cursor(VOID* m_Game, Map* m_Map, IDirect3DDevice9Ptr m_Device);
	~UI_Cursor();
	void Update();
	void Render(ID3DXSprite* m_sprite, float depth);
};


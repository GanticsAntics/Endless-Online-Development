#include "..\stdafx.h"
#ifndef Textbox_h
#define Textbox_h
class Textbox
{
public:
	enum KeyType
    {
        None = 0,
        Letter = 1,
        Digit = 2,
        LetterOrDigit = Letter | Digit,
        Punctuation = 4,
        Separator = 8,
        Control = 16
    };
		RECT TextBounds;
		byte Phase;
		byte SubPhase;
		ID3DXSprite* Sprite;
		int WorldID;
        KeyType keyMask;
        bool nonAcceptedKeyEntered;
		int MaxLen;
		bool focused;
		bool blinkhidden;
        bool acceptsReturn;
		bool acceptspace = false;
		wchar_t hashkey;
        int textBoxInnerWidth;
		D3DXCOLOR color;
		std::basic_string<wchar_t> text;
		D3DXVECTOR2 position, size;
		Textbox(D3DXVECTOR2 m_position, D3DXVECTOR2 m_size, int fontSize, D3DXCOLOR labelColor, IDirect3DDevice9* m_Dev, byte _Phase, byte _Subphase);
		Textbox(D3DXVECTOR2 m_position, D3DXVECTOR2 m_size, D3DXCOLOR labelColor, ID3DXFont* m_font, byte _Phase, byte _Subphase);
		ID3DXFont* Font;
		KeyType GetKeyType(char c);
		void OnKeyDown(WPARAM args);
		void OnKeyPress(WPARAM args);
		void Render(ID3DXSprite* m_Sprite);
		void Reset();
		void SetKeyMask(KeyType newKeyMask);
		bool CheckCollision(int X, int Y);
		void Release();

};
#endif //Textbox_h
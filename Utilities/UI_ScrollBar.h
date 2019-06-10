#include "..\stdafx.h"
#ifndef UI_Scrollbar_h
#define UI_Scrollbar_h
#include <d3d9types.h>
#include "Button.h"
#include "..\TextTools.h"

class UI_Scrollbar 
{
	Button* UI_Scrollbar_Button_Top;
	Button* UI_Scrollbar_Button_Bottom;
	boost::shared_ptr<IDirect3DTexture9> p_ScrollbarTexture;
	std::vector<TextTools::ChatContainer>* p_container;
	ID3DXFont* ScrollbarReferenceFont;
	std::string FullText = "";
	std::vector<std::string> SubText;
	short ElementWidth = 0;
	short ElementHeight = 0;
	int x = 0;
	int y = 0;
	int TextX = 0;
	int TextY = 0;
	bool TextOrElement = false;

	float m_BarHeight = 0;
	float Barpos = 0;
	float BarHeight = 0;
	bool Selected = false;
	float Lineindex = 0;
	int ScrollBarFPSCounter = 0;
public:
	D3DCOLOR TextCol = D3DCOLOR_ARGB(255, 0, 0, 0);
	UI_Scrollbar(int m_x, int m_y, int m_ElementWidth, int m_ElementHeight, int m_BarHeight, boost::shared_ptr<IDirect3DTexture9> m_ScrollbarTexture, void* m_Game);
	UI_Scrollbar(int m_x, int m_y, short m_textWidth, short m_textHeight, int m_XtextlocationRelativeToX, int m_YtextlocationRelativeToY, int m_BarHeight, std::string m_text, boost::shared_ptr<IDirect3DTexture9> m_ScrollbarTexture, void* m_Game, ID3DXFont* m_ScrollbarReferenceFont);
	UI_Scrollbar(int m_x, int m_y, short m_textWidth, short m_textHeight, int m_XtextlocationRelativeToX, int m_YtextlocationRelativeToY, int m_BarHeight, std::vector<TextTools::ChatContainer>* m_container, boost::shared_ptr<IDirect3DTexture9> m_ScrollbarTexture, void* m_Game, ID3DXFont* m_ScrollbarReferenceFont);
	float BarPercent = 0;
	
	//std::string GetCroppedString() { return this->SubText; }
	void SetInputString(std::string m_InputString) { this->FullText = m_InputString; this->SubText.clear(); }
	void SetPosition(int m_x, int m_y) { this->x = m_x; this->y = m_y; }
	void Update(int MouseX, int MouseY, bool MousePressed, bool MouseHeld, int FPS);
	void BottomLineIndex()
	{
		if (p_container == NULL)
		{
			this->Lineindex = this->SubText.size() - 6;
			if (this->Lineindex < 0)
			{
				this->Lineindex = 0;
			}
			this->BarPercent = (float)(this->Lineindex) / (float)(this->SubText.size());
			this->Barpos = (float)(this->BarPercent) * (float)(this->BarHeight - 32);
		}
		else
		{
			int counter = 0;
			for (int i = 0; i < p_container->size(); i++)
			{
				counter += p_container->at(i).MessageLength;
			}
			this->Lineindex = counter - 5;

			if (this->Lineindex < 0)
			{
				this->Lineindex = 0;
			}
			this->BarPercent = (float)(this->Lineindex) / (float)(counter);
			this->Barpos = ((float)(this->BarPercent) * (float)(this->BarHeight - 32));
		}
	}
	void Draw(ID3DXSprite* _Sprite);

};
#endif // Button_h
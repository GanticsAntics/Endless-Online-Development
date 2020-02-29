#include "..\stdafx.h"
#ifndef UI_Scrollbar_h
#define UI_Scrollbar_h
#include <d3d9types.h>
#include "Button.h"
#include "TextTools.h"

class UI_Scrollbar 
{
	Button* UI_Scrollbar_Button_Top;
	Button* UI_Scrollbar_Button_Bottom;
	Resource_Manager::TextureData* p_ScrollbarTexture;
	Resource_Manager::TextureData* p_IconTexture;
	std::vector<TextTools::ChatContainer>* p_container;
	sf::Font* ScrollbarReferenceFont;
	std::string FullText = "";
	std::vector<std::string> SubText;
	short ElementWidth = 0;
	short ElementHeight = 0;
	Game* m_game;

	int TextX = 0;
	int TextY = 0;
	bool TextOrElement = false;
	bool IsVertical = true;
	float m_BarHeight = 0;
	float Barpos = 0;
	float BarHeight = 0;
	bool Selected = false;
	float Lineindex = 0;
	int ScrollBarFPSCounter = 0;
	bool Buttonsenabled = true;
	int MaxIndex = 0;
	int Numberoflines = 6;
	int x = 0;
	int y = 0;
public:	

	sf::Color TextCol = sf::Color::White;// (255, 0, 0, 0);
	UI_Scrollbar(int m_x, int m_y, int m_ElementWidth, int m_ElementHeight, int m_BarHeight, Resource_Manager::TextureData* m_ScrollbarTexture, Game* m_Game, Resource_Manager::TextureData* p_IconTexture);
	UI_Scrollbar(int m_x, int m_y, short m_textWidth, short m_textHeight, int m_XtextlocationRelativeToX, int m_YtextlocationRelativeToY, int m_BarHeight, std::string m_text, Resource_Manager::TextureData* m_ScrollbarTexture, Game* m_Game, sf::Font* m_ScrollbarReferenceFont, Resource_Manager::TextureData* p_IconTexture);
	UI_Scrollbar(int m_x, int m_y, short m_textWidth, short m_textHeight, int m_XtextlocationRelativeToX, int m_YtextlocationRelativeToY, int m_BarHeight, std::vector<TextTools::ChatContainer>* m_container, Resource_Manager::TextureData* m_ScrollbarTexture, Game* m_Game, sf::Font* m_ScrollbarReferenceFont, Resource_Manager::TextureData* p_IconTexture);
	float BarPercent = 0;
	//std::string GetCroppedString() { return this->SubText; }
	void SetButtonsEnabled(bool value = true) { this->Buttonsenabled = value; }
	void SetVertical(bool value = true) { this->IsVertical = value; }
	void SetInputString(std::string m_InputString) { this->FullText = m_InputString; this->SubText.clear(); }
	void SetNumberOfLines(int NumberofLines) { this->Numberoflines = NumberofLines; }
	int GetBarHeight() { return this->BarHeight; }
	int GetButtonWidth() { return this->ElementHeight; }
	std::pair<int, int> GetPosition() { return std::pair<int, int>(x, y); }
	void SetPosition(int m_x, int m_y)
	{
		this->x = m_x; 
		this->y = m_y;
		if (this->IsVertical)
		{
			this->UI_Scrollbar_Button_Top->SetPosition(std::pair<int, int>(this->x, this->y));
			this->UI_Scrollbar_Button_Bottom->SetPosition(std::pair<int, int>(this->x, this->y  + this->BarHeight));
		}
		else
		{
			this->UI_Scrollbar_Button_Top->SetPosition(std::pair<int, int>(this->x, this->y));
			this->UI_Scrollbar_Button_Bottom->SetPosition(std::pair<int, int>(this->x + this->ElementHeight + this->BarHeight, this->y));
		}
	}
	void Update(int MouseX, int MouseY, int MouseWheelValue, bool MousePressed, bool MouseHeld, int FPS);
	void BottomLineIndex()
	{
		if (p_container == NULL)
		{
			this->Lineindex = this->SubText.size() - (this->Numberoflines - 1);
			if (this->Lineindex < 0)
			{
				this->Lineindex = 0;
			}

			if (this->SubText.size() - (this->Numberoflines - 1) == 0)
			{
				this->BarPercent = 0;
			}
			else
			{
				this->BarPercent = (float)(this->Lineindex) / (float)(this->SubText.size() - (this->Numberoflines - 1));
			}
			this->Barpos = (float)(this->BarPercent) * (float)(this->BarHeight - 32);
		}
		else
		{
			int counter = 0;
			for (int i = 0; i < p_container->size(); i++)
			{
				counter += p_container->at(i).MessageLength;
			}
			this->Lineindex = counter - (this->Numberoflines - 1);

			if (this->Lineindex < 0)
			{
				this->Lineindex = 0;
			}
			if ((float)(counter - (this->Numberoflines - 1)) == 0)
			{
				this->BarPercent = 0;
			}
			else
			{
				this->BarPercent = (float)(this->Lineindex) / (float)(counter - (this->Numberoflines - 1));
			}

			this->Barpos = ((float)(this->BarPercent) * (float)(this->BarHeight - 32));
		}
	}
	void SetMaxIndex(int _Index) { this->MaxIndex = _Index; }
	int GetMaxIndex() { return this->MaxIndex; }
	int GetIndex() { return this->Lineindex; }
	void SetIndex(int _Index) {
	this->Lineindex = _Index; 
	this->BarPercent = (float)(this->Lineindex) / (float)(this->MaxIndex);
	this->Barpos = ((float)(this->BarPercent) * (float)(this->BarHeight - 32));
	}
	void Draw(float depth);

};
#endif // Button_h
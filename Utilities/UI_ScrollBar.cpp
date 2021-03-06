#include "..\stdafx.h"
#include "UI_ScrollBar.h"
#include "..\game.h"


UI_Scrollbar::UI_Scrollbar(int m_x, int m_y, int m_ElementWidth, int m_ElementHeighht, int m_BarHeight, Resource_Manager::TextureData* m_ScrollbarTexture, Game* p_Game, Resource_Manager::TextureData* m_IconTexture)
{
	this->m_game = p_Game;
	this->p_container = NULL;
	this->TextOrElement = false;
	this->x = m_x;
	this->y = m_y;
	this->ElementWidth = m_ElementWidth;
	this->ElementHeight = m_ElementHeighht;
	this->BarHeight = m_BarHeight;
	this->p_ScrollbarTexture = m_ScrollbarTexture;
	this->p_IconTexture = m_IconTexture;
	this->UI_Scrollbar_Button_Top = new Button(this->m_game, this->x, this->y, 0, 45, 16, 15, true, m_ScrollbarTexture);
	this->UI_Scrollbar_Button_Bottom = new Button(this->m_game, this->x, this->y + this->BarHeight, 0, 15, 16, 15, true, m_ScrollbarTexture);
};

UI_Scrollbar::UI_Scrollbar(int m_x, int m_y, short m_textWidth, short m_textHeight, int m_XtextlocationRelativeToX, int m_YtextlocationRelativeToY, int m_BarHeight, std::string m_text, Resource_Manager::TextureData* m_ScrollbarTexture, Game* p_Game,sf::Font*  m_ScrollbarReferenceFont, Resource_Manager::TextureData* m_IconTexture)
{
	this->m_game = p_Game;
	this->p_container = NULL;
	this->TextOrElement = true;
	this->x = m_x;
	this->y = m_y;
	this->ElementWidth = m_textWidth;
	this->ElementHeight = m_textHeight;
	this->BarHeight = m_BarHeight;
	this->FullText = m_text;
	this->p_ScrollbarTexture = m_ScrollbarTexture;
	this->ScrollbarReferenceFont = m_ScrollbarReferenceFont;
	this->TextX = m_XtextlocationRelativeToX;
	this->TextY = m_YtextlocationRelativeToY;
	this->p_IconTexture = m_IconTexture;
	this->TextCol = sf::Color::Black;
	this->UI_Scrollbar_Button_Top = new Button(this->m_game, this->x, this->y, 0, 45, 16, 15, true, m_ScrollbarTexture);
	this->UI_Scrollbar_Button_Bottom = new Button(this->m_game, this->x, this->y + this->BarHeight, 0, 15, 16, 15, true, m_ScrollbarTexture);
};


UI_Scrollbar::UI_Scrollbar(int m_x, int m_y, short m_textWidth, short m_textHeight, int m_XtextlocationRelativeToX, int m_YtextlocationRelativeToY, int m_BarHeight, std::vector<TextTools::ChatContainer>* m_container, Resource_Manager::TextureData* m_ScrollbarTexture, Game* p_Game,sf::Font*  m_ScrollbarReferenceFont, Resource_Manager::TextureData* m_IconTexture)
{
	this->m_game = p_Game;
	this->p_container = m_container;
	this->TextOrElement = true;
	this->x = m_x;
	this->y = m_y;
	this->ElementWidth = m_textWidth;
	this->ElementHeight = m_textHeight;
	this->BarHeight = m_BarHeight;
	this->FullText = "";
	this->p_ScrollbarTexture = m_ScrollbarTexture;
	this->ScrollbarReferenceFont = m_ScrollbarReferenceFont;
	this->TextX = m_XtextlocationRelativeToX;
	this->TextY = m_YtextlocationRelativeToY;
	this->p_IconTexture = m_IconTexture;
	this->TextCol = sf::Color::Black;
	this->UI_Scrollbar_Button_Top = new Button(this->m_game, this->x, this->y, 0, 45, 16, 15, true, m_ScrollbarTexture);
	this->UI_Scrollbar_Button_Bottom = new Button(this->m_game, this->x, this->y + this->BarHeight, 0, 15, 16, 15, true, m_ScrollbarTexture);
};
int Fontsize = 10;
void UI_Scrollbar::Update(int MouseX, int MouseY, int MouseWheelValue, bool MousePressed, bool MouseHeld, int FPS)
{
	if (this->Buttonsenabled)
	{
		this->UI_Scrollbar_Button_Bottom->Update(MouseX, MouseY, MousePressed);
		this->UI_Scrollbar_Button_Top->Update(MouseX, MouseY, MousePressed);
	}
	if (!MouseHeld)
	{
		this->Selected = false;
	}
	if (this->Selected)
	{
		if (this->IsVertical)
		{
			this->Barpos = MouseY - this->y - 24;
			if (this->Barpos < 0)
			{
				this->Barpos = 0;
			}
			if (this->Barpos > this->BarHeight - 32)
			{
				this->Barpos = this->BarHeight - 32;
			}
		}
		else
		{
			this->Barpos = MouseX - this->x - 24;
			if (this->Barpos < 0)
			{
				this->Barpos = 0;
			}
			if (this->Barpos > this->BarHeight - 32)
			{
				this->Barpos = this->BarHeight - 32;
			}
		}
	}
	if (this->IsVertical)
	{
		if (MouseX > this->x && MouseX < this->x + 16)
		{
			if (MouseY > this->y + 24 && MouseY < this->y + this->BarHeight - 8)
			{
				if (MouseHeld)
				{
					this->Selected = true;
				}
			}
		}
	}
	else
	{
		if (MouseX > this->x && MouseX < this->x + this->BarHeight )
		{
			if (MouseY > this->y && MouseY < this->y + 16)
			{
				if (MouseHeld)
				{
					this->Selected = true;
				}
			}
		}
	}
	this->BarPercent = (float)(this->Barpos) / (float)(this->BarHeight - 32);
	if (this->TextOrElement)
	{
		this->MaxIndex = this->SubText.size();
	}
	ScrollBarFPSCounter++;
	if (ScrollBarFPSCounter > FPS / 4 )
	{
		{
			this->SubText = TextTools::SnipTextToWidth(this->FullText, this->ElementWidth, Fontsize, this->m_game);
			this->ScrollBarFPSCounter = 0;

		}
	}
	if (this->p_container == NULL)
	{
		this->Lineindex = (this->MaxIndex - (this->Numberoflines - 1)) * (float)(this->BarPercent);
		if (this->Lineindex < 0)
		{
			this->Lineindex = 0;
		}
	}
	else
	{
		int counter = 0;
		for (int i = 0; i < p_container->size(); i++)
		{
			counter += p_container->at(i).MessageLength;
		}
		this->Lineindex = ((float)counter - (this->Numberoflines - 1)) * (float)(this->BarPercent );
		if (this->Lineindex < 0)
		{
			this->Lineindex = 0;
		}
	}
	bool mousepressed = false;

	if(this->UI_Scrollbar_Button_Bottom->MouseClickedOnElement())
	{
		this->Lineindex++;
		mousepressed = true;
	}
	if (this->UI_Scrollbar_Button_Top->MouseClickedOnElement())
	{
		this->Lineindex--;
		mousepressed = true;
	}
	if (MouseWheelValue < 0)
	{
		this->Lineindex -= 1;
		this->BarPercent = (float)(this->Lineindex) / (float)(this->MaxIndex);
		this->Barpos = ((float)(this->BarPercent) * (float)(this->BarHeight - 32));
		mousepressed = true;
	}
	else if (MouseWheelValue > 0)
	{
		this->Lineindex += 1;
		this->BarPercent = (float)(this->Lineindex) / (float)(this->MaxIndex);
		this->Barpos = ((float)(this->BarPercent) * (float)(this->BarHeight - 32));
		mousepressed = true;
	}

	if (mousepressed)
	{
		if (this->p_container == NULL)
		{
			if (this->Lineindex > this->MaxIndex - (this->Numberoflines - 1))
			{
				this->Lineindex = this->MaxIndex - (this->Numberoflines - 1);
			}
			if (this->Lineindex < 0)
			{
				this->Lineindex = 0;
			}
			this->BarPercent = (float)(this->Lineindex) / (float)(this->MaxIndex -(this->Numberoflines - 1));
			this->Barpos = (float)(this->BarPercent) * (float)(this->BarHeight - 32);
		}
		else
		{

			int counter = 0;
			for (int i = 0; i < p_container->size() ; i++)
			{
				counter += p_container->at(i).MessageLength ;
			}
			if (this->Lineindex > counter - (this->Numberoflines - 1))
			{
				this->Lineindex = counter - (this->Numberoflines - 1);
			}
			if (this->Lineindex < 0)
			{
				this->Lineindex = 0;
			}
			

			this->BarPercent = (float)(this->Lineindex) / (float)(counter - (this->Numberoflines - 1));
			this->Barpos = ((float)(this->BarPercent) * (float)(this->BarHeight - 32));
		}
	}
};

void UI_Scrollbar::Draw(float depth)
{
	if (this->Buttonsenabled)
	{
		this->UI_Scrollbar_Button_Bottom->Draw(depth);
		this->UI_Scrollbar_Button_Top->Draw(depth);
	}
	RECT SrcRect;
	SrcRect.left = 0;
	SrcRect.top = 0;
	SrcRect.bottom = 15;
	SrcRect.right = 16;
	sf::Vector3f* Pos = new sf::Vector3f(x - 1, y + 16 + this->Barpos, 0);
	sf::Vector3f* Center = new sf::Vector3f(0, 0, 0);
	if (!this->IsVertical)
	{
		Pos->x = x + 16 + this->Barpos;
		Pos->y = y;
	}


	this->m_game->Draw(this->p_ScrollbarTexture, Pos->x, Pos->y, sf::Color(255, 255, 255, 255), SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), depth);
	if (this->TextOrElement)
	{
		if (this->p_container != NULL)
		{
			int index = 0;
			int indexID = 0;
			int subindex = this->Lineindex - index;
			for (int i = 0; i < p_container->size(); i++)
			{
				if (index + p_container->at(i).MessageLength <= (int)this->Lineindex)
				{
					index += p_container->at(i).MessageLength;
					subindex =  this->Lineindex - index;
					indexID = i;
				}
			}

			int count = 0;
			for (int i = indexID; i < indexID + 6; i++)
			{
				if (i >= this->p_container->size())
				{
					break;
				}

				RECT IconSrcRect;
				IconSrcRect.left = 0;
				IconSrcRect.top = this->p_container->at(i).Chat_Icon*13;
				IconSrcRect.bottom = IconSrcRect.top+13;
				IconSrcRect.right = 12;
				sf::Vector3f* IconPos = new sf::Vector3f(this->x + this->TextX - 18, this->y + this->TextY + count*16, 0);
				sf::Vector3f* IconCentre = new sf::Vector3f(0, 0, 0);
				this->m_game->Draw(this->p_IconTexture, IconPos->x, IconPos->y, sf::Color(255, 255, 255, 255), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), depth);
				delete IconPos;
				delete IconCentre;
				RECT rct;
				rct.left = this->x + this->TextX;
				rct.right = this->x + this->TextX + this->ElementWidth;
				rct.top = this->y + this->TextY + (count * 16);
				rct.bottom = this->y + this->TextY + this->ElementHeight + (count * 16);

				std::string message = this->p_container->at(i).CharacterName + "  ";

				sf::Vector2f strsize = this->m_game->GetFontSize(message, Fontsize);
				//this->ScrollbarReferenceFont->DrawTextA(NULL, message.c_str(), message.size(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
				this->m_game->DrawTextW(message, rct.left, rct.top, this->p_container->at(i).message_col, Fontsize, false, depth);
				//this->ScrollbarReferenceFont->DrawTextA(_Sprite, message.c_str(), -1, &rct, NULL, this->p_container->at(i).message_col);

				for (int ii = subindex; ii < this->p_container->at(i).Message.size(); ii++)
				{
					rct.left = this->x + this->TextX + 7 + strsize.x;
					rct.right = this->x + this->TextX + this->ElementWidth + 7 + strsize.x;
					rct.top = this->y + this->TextY + (count * 16);
					rct.bottom = this->y + this->TextY + this->ElementHeight + (count * 16);
					
					message = this->p_container->at(i).Message[ii];
					this->m_game->DrawTextW(message, rct.left, rct.top, this->p_container->at(i).message_col, Fontsize, false, depth);
					//this->ScrollbarReferenceFont->DrawTextA(_Sprite, message.c_str(), -1, &rct, NULL, this->p_container->at(i).message_col);

					if (ii + 1 == this->p_container->at(i).Message.size())
					{
						subindex = 0;
					}
					if (count >=  5)
					{
						delete Pos;
						delete Center;
						return;
					}
					count++;
				}
			}

		}
		else
		{
			int count = 0;
			int index = floor(this->Lineindex);
			for (int i = index; i < index + 6; i++)
			{
				RECT rct;
				rct.left = this->x + this->TextX;
				rct.right = this->x + this->TextX + this->ElementWidth + 100;
				rct.top = this->y + this->TextY + (count * 16);
				rct.bottom = this->y + this->TextY + this->ElementHeight + (count * 16);
				if (i >= this->SubText.size())
				{
					break;
				}
				this->m_game->DrawTextW(this->SubText[i], rct.left, rct.top, this->TextCol, Fontsize, false, depth);
				//this->ScrollbarReferenceFont->DrawTextA(_Sprite, this->SubText[i].c_str(), -1, &rct, DT_EXPANDTABS, this->TextCol);
				count++;
			}
		}

	}
			delete Pos;
		delete Center;
};


#include "UI_InformationBox.h"
#include "..\stdafx.h"
#include "..\Game.h"
#include <map>

#define UI_Info_BlockWidth 205

UI_InformationBox::UI_InformationBox(Game* p_game)
{
	this->m_game = p_game;
	this->Initialize(this->m_game);
	InfoBxBGTexture = this->m_game->ResourceManager->CreateTexture(2, 52, false).Texture;

	this->SetPosition(std::pair<int, int>(100, 100));
	this->SetSize(std::pair<int, int>(284, 290));
	this->m_game->ResourceManager->CreateTexture(1, 15, false).Texture;
	this->Bt_Okay = new Button(this->m_game, 0, 0, 0, 116, 91, 28, false,  this->m_game->GLoginButtonTexture);
	this->Bt_Add = new Button(this->m_game, 0, 0, 0, 174, 91, 28, false, this->m_game->GLoginButtonTexture);
	this->Bt_Back = new Button(this->m_game, 0, 0, 0, 145, 91, 28, false, this->m_game->GLoginButtonTexture);
	this->Bt_Cancel = new Button(this->m_game, 0, 0, 0, 29, 91, 28, false, this->m_game->GLoginButtonTexture);
	this->Bt_Next = new Button(this->m_game, 0, 0, 0, 203, 91, 28, false, this->m_game->GLoginButtonTexture);
	this->Bt_History = new Button(this->m_game, 0, 0, 0, 232, 91, 28, false, this->m_game->GLoginButtonTexture);
	this->Bt_Progress = new Button(this->m_game, 0, 0, 0, 261, 91, 28, false, this->m_game->GLoginButtonTexture);
	
	this->UI_InfoScrollbar = new UI_Scrollbar(100 + 251,100 + 43, UI_Info_BlockWidth, this->_ElementHeight, 184,this->m_game->ScrollBarTexture.Texture, this->m_game, this->m_game->TextIconTexture.Texture);
	this->UI_InfoScrollbar->SetVertical(true);
	this->UI_InfoScrollbar->SetNumberOfLines(this->MaxIndex);
	
	this->InterfaceButtons.push_back(this->Bt_Cancel);
	this->InterfaceButtons.push_back(this->Bt_Next);
	//this->InterfaceButtons.push_back(this->Bt_Cancel);	
	//this->InterfaceButtons.push_back(this->Bt_Back);
	//this->InterfaceButtons.push_back(this->Bt_Cancel);
	
}

UI_InformationBox::~UI_InformationBox()
{
}
void UI_InformationBox::AlignInterface()
{
	CurrentIndex = this->UI_InfoScrollbar->GetIndex();
	this->UI_InfoScrollbar->SetPosition(this->GetPosition().first + 251, this->GetPosition().second + 43);
	this->UI_InfoScrollbar->SetNumberOfLines(this->MaxIndex);
	int buttoncounter = 0;
	int numberofbuttons = this->InterfaceButtons.size();
	int ClipBoundary = this->GetSize().first/2;
	int btn_left = 0, btn_right = 0;
	int btncentre = 0;
	bool swapdir = false;
	for each (Button * btn in this->InterfaceButtons)
	{
		if (numberofbuttons % 2 != 0)
		{
			btncentre = 1;
		}
		if (numberofbuttons % 2 != 0 && buttoncounter == std::floor((float)(numberofbuttons) / 2.0f))
		{
			int xpos = ClipBoundary - ((btn->GetSize().first / 2)) - (numberofbuttons - 1);
			btn->SetPosition(pair<int, int>(this->GetPosition().first + xpos, this->GetPosition().second + 250));
		}
		else if (!swapdir)
		{
			btn_right++;
			int xpos = ClipBoundary + ((btn->GetSize().first / 2) * (btn_right)) - (btn->GetSize().first / 2) + ((btn->GetSize().first / 2) * btncentre) - (numberofbuttons - 1);
			btn->SetPosition(pair<int, int>(this->GetPosition().first + xpos, this->GetPosition().second + 250));
			swapdir = true;
		}
		else
		{
			btn_left++;
			int xpos = ClipBoundary - ((btn->GetSize().first / 2) * (btn_left)) - (btn->GetSize().first / 2) - ((btn->GetSize().first / 2) * btncentre) - (numberofbuttons - 1);
		    btn->SetPosition(pair<int, int>(this->GetPosition().first + xpos, this->GetPosition().second + 250));
			swapdir = false;
		}	
		buttoncounter++;
	}
}
void UI_InformationBox::Update()
{
	if (this->GetIsActive())
	{
		this->UpdateElement();
		AlignInterface();
		this->UI_InfoScrollbar->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed, this->m_game->RAWMousePressed, this->m_game->FPS);
		bool ButtonPressed = false;
		for each (Button * btn in this->InterfaceButtons)
		{
			btn->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
			if (btn->MouseOverElement())
			{
				if (this->m_game->MousePressed && !this->isdragging)
				{
					ButtonPressed = true;
					if (btn == this->Bt_Cancel)
					{
						this->CloseBox();
					}
				}

			}
		}
		if (this->m_game->MouseX > this->GetPosition().first + 251 && this->m_game->MouseX < this->GetPosition().first + 270 && this->m_game->MouseY >  this->GetPosition().second + 42 && this->m_game->MouseY < this->GetPosition().second + 244 && m_game->MousePressed)
		{
			ButtonPressed = true;
		}
		if (this->MouseOverElement() && m_game->MousePressed && !ButtonPressed)
		{
			this->isdragselected = true;
		}
		if (this->isdragselected == true)
		{
			if (this->m_game->RAWMousePressed)
			{
				if (!this->isdragging)
				{
					DragX = this->m_game->MouseX - this->GetPosition().first;
					DragY = this->m_game->MouseY - this->GetPosition().second;
					this->isdragging = true;
				}
				this->SetPosition(std::pair<int,int>(this->m_game->MouseX - DragX, this->m_game->MouseY - DragY));
			}
			else
			{
				this->isdragging = false;
				this->isdragselected = false;
			}
		}
	}
}

void UI_InformationBox::Draw(ID3DXSprite* _Sprite)
{	
	if (this->GetIsActive())
	{
		this->m_game->Draw(_Sprite, this->InfoBxBGTexture, this->GetPosition().first, this->GetPosition().second, D3DCOLOR_ARGB(255, 255, 255, 255));
		RECT rct;
		rct.left = this->GetPosition().first + 20;
		rct.right = rct.left + UI_Info_BlockWidth;
		rct.top = this->GetPosition().second + 14;
		rct.bottom = rct.top + this->_ElementHeight+5;
		
		
		this->m_game->MessageFont->DrawTextA(_Sprite, this->m_Title.c_str(), -1, &rct, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 240, 240, 199));
		for each (Button * btn in this->InterfaceButtons)
		{
			btn->Draw(_Sprite);
		}
		this->UI_InfoScrollbar->Draw(_Sprite);

		//int totalmaxindex = ((this->CurrentIndex + this->MaxIndex) < (this->ContainerData[0].size()) ? (this->CurrentIndex + this->MaxIndex) : this->ContainerData[0].size());
		for (int i = this->CurrentIndex; i < ((this->CurrentIndex + this->_ElementHeight) < (this->ContainerData[0].size()) ? (this->CurrentIndex+this->_ElementHeight) : this->ContainerData[0].size()); i++)
		{
			rct.left = this->GetPosition().first + 20;
			rct.right = this->GetPosition().first + 40 + UI_Info_BlockWidth;
			rct.top = this->GetPosition().second + 45 + ((i - this->CurrentIndex) * 16);
			rct.bottom = this->GetPosition().second + 45 + this->_ElementHeight + ((i - this->CurrentIndex) * 16);

			this->m_game->MessageFont->DrawTextA(_Sprite, this->ContainerData[0][(i)].Message.c_str(), -1, &rct, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 240, 240, 199));
			
		}
	}
}

void UI_InformationBox::CreateMessage(std::string Title, std::string Message, bool ShowCancel)
{
	this->SetTitle(Title);
	this->m_game->world->UIBox_Hidden = false;
	this->SetIsActive(true);
}

void UI_InformationBox::CloseBox()
{
	this->m_game->world->UIBox_Hidden = true;
	this->SetIsActive(false);
}

void UI_InformationBox::AddMessage(std::string Message)
{
	///The role of this function is to take an input string and splice it into lines (specified by the width inside the parent class) and add it to the container that holds both text and buttons.
	ContainerPhase _ContainerData;

	std::string splicetext = TextTools::SnipMessageTextToWidth(Message, UI_Info_BlockWidth, this->m_game->MessageFont);
	size_t n = std::count(splicetext.begin(), splicetext.end(), '\n');
	int bufpos = 0;
	int buflen = 0;
	for (int i = 0; i < n; i++)
	{
		int offset1 = splicetext.find('\n', bufpos);
		std::string tempstr = splicetext.substr(bufpos, offset1 - (bufpos));
		_MessageContainer newcont;
		newcont.Message = tempstr;
		newcont.Message_Type = MessageType::Text;
		_ContainerData.push_back(newcont);
		bufpos = offset1 + 1;
	}
	this->ContainerData[0] = _ContainerData;
	
	this->MaxIndex = this->ContainerData[0].size();
	
	this->UI_InfoScrollbar->SetMaxIndex((this->MaxIndex*2) - this->_ElementHeight);
}
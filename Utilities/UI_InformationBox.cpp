#include "UI_InformationBox.h"
#include "..\stdafx.h"
#include "..\Game.h"
#include "..\Packet_Handler\Send\SShop.h"
#include <map>

#define UI_Info_BlockWidth 205

UI_InformationBox::UI_InformationBox(Game* p_game)
{
	this->m_game = p_game;
	this->Initialize(this->m_game);
	this->SetIsActive(false);
	InfoBxBGTexture = this->m_game->ResourceManager->CreateTexture(2, 52, false).Texture;
	InfoIcons = this->m_game->ResourceManager->CreateTexture(2, 27, false).Texture;
	this->SetPosition(std::pair<int, int>(70, 20));
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
	this->UI_InfoScrollbar->SetMaxIndex(this->MaxIndex);
	this->UI_InfoScrollbar->SetNumberOfLines(1);
	this->InterfaceButtons.push_back(this->Bt_Cancel);
	//this->InterfaceButtons.push_back(this->Bt_Next);
	//this->InterfaceButtons.push_back(this->Bt_Cancel);	
	//this->InterfaceButtons.push_back(this->Bt_Back);
	//this->InterfaceButtons.push_back(this->Bt_Cancel);
	D3DXVECTOR2 Pos;
	Pos.x = 207;
	Pos.y = 309;

	D3DXVECTOR2 Size;
	Size.x = 460;
	Size.y = 30;
	Textbox _DropTextbox = Textbox(Pos, Size, D3DCOLOR_ARGB(200, 255, 255, 255), this->m_game->MessageFont, Game::GameStage::PInGame, 99);
	_DropTextbox.blinkhidden = false;
	_DropTextbox.MaxLen = 5;
	_DropTextbox.nonAcceptedKeyEntered = false;
	_DropTextbox.acceptspace = true;
	_DropTextbox.acceptsReturn = true;
	_DropTextbox.SetKeyMask(Textbox::KeyType::Digit);
	this->TB_ScrollBox = this->m_game->world->RegisterTextBox(_DropTextbox);

	this->ScrollBoxScrollBar = new UI_Scrollbar(10, 10, 200, 10, 137, this->m_game->ScrollBarTexture.Texture, this->m_game, this->m_game->TextIconTexture.Texture);
	this->ScrollBoxScrollBar->SetPosition(130, 100);
	this->ScrollBoxScrollBar->SetVertical(false);
	this->ScrollBoxScrollBar->SetButtonsEnabled(false);
	//this->ScrollBoxScrollBar->SetMaxIndex(99999);
	this->ScrollBoxScrollBar->SetNumberOfLines(1);

	this->UI_ScrollBoxElement_Okay = new Button(*this->m_game->BT_Message_OK);
	this->UI_ScrollBoxElement_Okay->SetPosition(std::pair<int, int>(421, 273));

	this->UI_ScrollBoxElement_Cancel = new Button(*this->m_game->BT_CharDeleteCancel);
	this->UI_ScrollBoxElement_Cancel->SetPosition(std::pair<int, int>(421, 273));

}

UI_InformationBox::~UI_InformationBox()
{
}
void UI_InformationBox::AlignInterface()
{
	CurrentIndex = this->UI_InfoScrollbar->GetIndex();
	this->UI_InfoScrollbar->SetPosition(this->GetPosition().first + 251, this->GetPosition().second + 43);
	//this->UI_InfoScrollbar->SetNumberOfLines(this->MaxIndex);
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
	if (AwaitingResponse)
	{
		if (this->m_game->MsgID == 1)
		{
			switch (this->_ScrollType)
			{
				case(ScrollBoxType::_SBT_BuyItem):
				{
					SShop::SendShopPurchase(this->m_game->world->connection->ClientStream, this->ScrollBoxID, this->ScrollBoxAmount, this->m_game);
					break;
				}
				case(ScrollBoxType::_SBT_SellItem):
				{
					SShop::SendShopSell(this->m_game->world->connection->ClientStream, this->ScrollBoxID, this->ScrollBoxAmount, this->m_game);
					break;
				}
				case(ScrollBoxType::_SBT_CraftItem):
				{
					CraftItemEntry newcraft;
					newcraft.Item_ID = 0;
					for (int i = 0; i < this->ContainerData[this->PhaseID].size(); i++)
					{
						ItemEntry newcrafting;
						newcrafting.Item_ID = this->ContainerData[this->PhaseID][i].Parameters[0];
						newcrafting.Item_Amount = this->ContainerData[this->PhaseID][i].Parameters[1];
						newcraft.Item_Requirements.push_back(newcrafting);
					}
					if (this->CheckCraftIngredients(newcraft))
					{
						SShop::SendShopCraft(this->m_game->world->connection->ClientStream, this->ScrollBoxID, this->m_game);
					}
					break;
				}
			}
			this->ScrollBoxID = -1;
			this->ScrollBoxAmount = 0;
			this->AwaitingResponse = false;
			this->m_game->MsgID = 0;
			this->isdragging = false;
			this->isdragselected = false;
			this->DragX = 0;
			this->DragY = 0;
		}
	}
	if (!World::MBHidden)
	{
		return;
	}
	
	if (this->GetIsActive())
	{
		this->UpdateElement();
		AlignInterface();
		if (!this->ScrollBoxVisible)
		{
			this->UI_InfoScrollbar->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MouseWheelVal, this->m_game->MousePressed, this->m_game->RAWMousePressed, this->m_game->FPS);
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
						else if (btn == this->Bt_Back)
						{
							if (this->PreviousPhraseIDs.size() > 0)
							{
								this->PhaseType = MessageType::_Text;
								this->ChangePhase(this->PreviousPhraseIDs[this->PreviousPhraseIDs.size()-1], true);
								return;
							}
						}
					}

				}
			}
			if (this->m_game->MouseX > this->GetPosition().first + 251 && this->m_game->MouseX < this->GetPosition().first + 270 && this->m_game->MouseY >  this->GetPosition().second + 42 && this->m_game->MouseY < this->GetPosition().second + 244 && m_game->MousePressed)
			{
				ButtonPressed = true;
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
					int ypos = this->m_game->MouseY - DragY;
					if (ypos > 22 && this->m_game->Stage == Game::GameStage::PInGame)
					{
						ypos = 22;
					}
					this->SetPosition(std::pair<int, int>(this->m_game->MouseX - DragX, ypos));
				}
				else
				{
					this->isdragging = false;
					this->isdragselected = false;
				}
			}

			int buildsize = 0;
			int m_startindex = ReturnLineIndexInPhase(this->PhaseID, this->CurrentIndex);
			RECT rct;
			if (m_startindex == -1) { return; }

			_MessageContainer HighlightedMessage;
			HighlightedMessage.Message = "Empty";
			for (int i = 0; i < _ElementHeight; i++)
			{
				D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 15, this->GetPosition().second + 45 + ((buildsize) * 16), 1);
				D3DXVECTOR3* Center = new D3DXVECTOR3(1, 1, 0);
				rct.left = 0;
				rct.right = UI_Info_BlockWidth + 30;
				rct.top = 0;
				rct.bottom = 16 * this->ContainerData[this->PhaseID][m_startindex + i].sizeofentry;
				if (buildsize == 11 && this->ContainerData[this->PhaseID][m_startindex + i].sizeofentry > 1) { rct.bottom = 24; }
				if (this->m_game->MouseX > Pos->x + rct.left && this->m_game->MouseX < Pos->x + rct.right)
				{
					if (this->m_game->MouseY > Pos->y + rct.top && this->m_game->MouseY < Pos->y + rct.bottom)
					{
						HighlightedMessage = this->ContainerData[this->PhaseID][m_startindex + i];
						if (m_game->MousePressed)
						{
							this->PhaseType = MessageType::_Text;
							switch (HighlightedMessage.Message_Type)
							{
							case(MessageType::_BuyItemEntry):
							{
								if (this->m_game->MousePressed)
								{
									this->ShowScrollBox(ScrollBoxType::_SBT_BuyItem, HighlightedMessage.Parameters[0], HighlightedMessage.Parameters[1], HighlightedMessage.Parameters[2]);
									this->m_game->MousePressed = false;
									////TODO: ADD Buy logic here.

								}	break;
							}
							case(MessageType::_SellItemEntry):
							{
								if (this->m_game->MousePressed)
								{
									this->ShowScrollBox(ScrollBoxType::_SBT_SellItem, HighlightedMessage.Parameters[0], HighlightedMessage.Parameters[1], this->m_game->Map_UserInterface->map_inventory->ContainsItem(HighlightedMessage.Parameters[0]));
									this->m_game->MousePressed = false;
								}	break;
							}
							case(MessageType::_CraftItemEntry):
							{
								if (this->m_game->MousePressed)
								{
									this->PhaseType = MessageType::_IngredientEntry;
									this->_ScrollType = ScrollBoxType::_SBT_CraftItem;
									this->ScrollBoxID = HighlightedMessage.Parameters[0];
									this->Bt_Okay->Deactivate();
								}
								break;
							}
							default:
							{
								break;
							}
							}
							if (this->ContainerData[this->PhaseID][m_startindex + i]._Hyperlinks.size() > 0)
							{							
								this->ChangePhase(this->ContainerData[this->PhaseID][m_startindex + i]._Hyperlinks[0]._Goto);
								delete Pos;
								delete Center;
								break;
							}
						}
					}
				}
				if (this->MouseOverElement() && m_game->MousePressed && !ButtonPressed && HighlightedMessage.Message == "Empty")
				{
					this->isdragselected = true;
				}
				delete Pos;
				delete Center;
				buildsize += this->ContainerData[this->PhaseID][m_startindex + i].sizeofentry;
				if (buildsize >= this->_ElementHeight || (i + m_startindex) >= this->ContainerData[this->PhaseID].size() - 1)
				{
					break;
				}
			}			
		}
	}
	if (ScrollBoxVisible)
	{
		this->UpdateScrollBox();
	}
	else
	{
		this->m_game->SubStage = 0;
	}

	if (this->Bt_Okay->MouseOverElement() && this->Bt_Okay->MouseClickedOnElement())
	{
		//if (this->ScrollBoxScrollBar->GetIndex() != 0)
		{
			switch (this->_ScrollType)
			{
			case(ScrollBoxType::_SBT_CraftItem):
			{
				this->ScrollBoxAmount = 1;
				std::string msg = "Would you like to craft " + std::to_string(ScrollBoxAmount) + " " + World::EIF_File->Get(this->ScrollBoxID).name + "?";
				World::ThrowMessage("Craft item(s)", msg, true);
				this->AwaitingResponse = true;
				break;
			}
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

		int buildsize = 0;
		int m_startindex = ReturnLineIndexInPhase(this->PhaseID, this->CurrentIndex);
		if (m_startindex == -1) { return; }
		for (int i = 0; i < _ElementHeight; i++)
		{
			D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 15, this->GetPosition().second + 45 + ((buildsize) * 16), 1);
			D3DXVECTOR3* Center = new D3DXVECTOR3(1, 1, 0);
			rct.left = 0;
			rct.right = UI_Info_BlockWidth + 30;
			rct.top = 0;
			rct.bottom = 16 * this->ContainerData[this->PhaseID][m_startindex + i].sizeofentry;
			bool mouseover = false;
			if (buildsize == 11 && this->ContainerData[this->PhaseID][m_startindex + i].sizeofentry > 1 ) { rct.bottom = 24; }
			if (this->m_game->MouseX > Pos->x + rct.left && this->m_game->MouseX < Pos->x + rct.right)
			{
				if (this->m_game->MouseY > Pos->y + rct.top && this->m_game->MouseY < Pos->y + rct.bottom)
				{
					_Sprite->Draw(this->m_game->Map_UserInterface->map_ChatBubbleHandler->ChatBoxBG, &rct, Center, Pos, D3DCOLOR_ARGB(30, 255, 255, 255));
				}
			}
			delete Pos;
			delete Center;
			this->DrawContainerEntry(_Sprite, this->ContainerData[this->PhaseID][m_startindex + i], buildsize);			
			buildsize += this->ContainerData[this->PhaseID][m_startindex + i].sizeofentry;
			if(buildsize >= this->_ElementHeight || (i + m_startindex) >= this->ContainerData[this->PhaseID].size()-1)
			{
				break;
			}


		}
	}
	if (ScrollBoxVisible)
	{
		this->RenderScrollBox(_Sprite);
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

	std::string splicetext = TextTools::SnipMessageTextToWidth(Message, UI_Info_BlockWidth, this->m_game->MessageFont);
	size_t n = std::count(splicetext.begin(), splicetext.end(), '\n')+1;
	int bufpos = 0;
	int buflen = 0;
	for (int i = 0; i < n; i++)
	{
		int offset1 = splicetext.find('\n', bufpos);
		std::string tempstr = splicetext.substr(bufpos, offset1 - (bufpos));
		_MessageContainer newcont;
		newcont.Message = tempstr;
		newcont.Message_Type = MessageType::_Text;
		this->ContainerData[0].push_back(newcont);
		bufpos = offset1 + 1;
	}
	
	this->MaxIndex = ReturnLineIndexInPhase(0, this->ContainerData[0].size());
	this->UI_InfoScrollbar->SetNumberOfLines(1);
	this->UI_InfoScrollbar->SetMaxIndex((this->MaxIndex + 1));
}

void UI_InformationBox::AddShopBuyItem(int ShopBuyIndex, int Item_ID, int Item_Amount, int Item_MaxAmount, int PhaseIndex)
{
	if (this->ContainerData[ShopBuyIndex].size() == 0 && PhaseIndex != -1)
	{
		_MessageContainer newcont;
		newcont.Message_Type = MessageType::_BuyItem;
		newcont.sizeofentry = 3;
		_Hyperlink _gotolink;
		_gotolink._Goto = ShopBuyIndex;
		newcont._Hyperlinks.push_back(_gotolink);
		this->ContainerData[PhaseIndex].push_back(newcont);
		this->ShopBuyActive = true;
	}
	//if (Item_ID > 0)
	{
		_MessageContainer ItemContainer;
		ItemContainer.Message_Type = MessageType::_BuyItemEntry;
		ItemContainer.sizeofentry = 3;
		ItemContainer.Parameters.push_back(Item_ID);
		ItemContainer.Parameters.push_back(Item_Amount);
		ItemContainer.Parameters.push_back(Item_MaxAmount);

		this->ContainerData[ShopBuyIndex].push_back(ItemContainer);
	}
	this->UI_InfoScrollbar->SetNumberOfLines(1);
	this->MaxIndex = ReturnLineIndexInPhase(PhaseIndex, this->ContainerData[PhaseIndex].size());
	this->UI_InfoScrollbar->SetIndex(0);
	this->UI_InfoScrollbar->SetMaxIndex((this->ContainerData[PhaseIndex].size() + 1));

}
void UI_InformationBox::AddStorageItem(int ItemID, int ItemAmount, int PhaseIndex)
{
	_MessageContainer ItemContainer;
	ItemContainer.Message_Type = MessageType::_StorageItemEntry;
	ItemContainer.sizeofentry = 3;
	ItemContainer.Parameters.push_back(ItemID);
	ItemContainer.Parameters.push_back(ItemAmount);
	this->ContainerData[PhaseIndex].push_back(ItemContainer);
	this->UI_InfoScrollbar->SetNumberOfLines(1);
	this->MaxIndex = ReturnLineIndexInPhase(PhaseIndex, this->ContainerData[PhaseIndex].size());
	this->UI_InfoScrollbar->SetMaxIndex((this->ContainerData[PhaseIndex].size() + 1));
}
void UI_InformationBox::AddShopSellItem(int ShopSellIndex, int Item_ID, int Item_Amount, int PhaseIndex)
{
	if (this->ContainerData[ShopSellIndex].size() == 0 && PhaseIndex != -1)
	{
		_MessageContainer newcont;
		newcont.Message_Type = MessageType::_SellItem;
		newcont.sizeofentry = 3;
		_Hyperlink _gotolink;
		_gotolink._Goto = ShopSellIndex;
		newcont._Hyperlinks.push_back(_gotolink);
		this->ContainerData[PhaseIndex].push_back(newcont);
	}
	//if (Item_ID > 0)
	{
		_MessageContainer ItemContainer;
		ItemContainer.Message_Type = MessageType::_SellItemEntry;
		ItemContainer.sizeofentry = 3;
		ItemContainer.Parameters.push_back(Item_ID);
		ItemContainer.Parameters.push_back(Item_Amount);
		this->ContainerData[ShopSellIndex].push_back(ItemContainer);
	}

	this->UI_InfoScrollbar->SetNumberOfLines(1);
	this->UI_InfoScrollbar->SetIndex(0);
	this->MaxIndex = ReturnLineIndexInPhase(PhaseIndex, this->ContainerData[PhaseIndex].size());
	this->UI_InfoScrollbar->SetMaxIndex((this->ContainerData[PhaseIndex].size() + 1));

}

void UI_InformationBox::AddShopCraftItem(int ShopCraftIndex, CraftItemEntry Item_Entry, int PhaseIndex)
{
	if (this->ContainerData[ShopCraftIndex].size() == 0 && PhaseIndex != -1)
	{
		_MessageContainer newcont;
		newcont.Message_Type = MessageType::_CraftItem;
		newcont.sizeofentry = 3;
		_Hyperlink _gotolink;
		_gotolink._Goto = ShopCraftIndex;
		newcont._Hyperlinks.push_back(_gotolink);
		this->ContainerData[PhaseIndex].push_back(newcont);
	}

	_MessageContainer ItemContainer;
	ItemContainer.Message_Type = MessageType::_CraftItemEntry;
	ItemContainer.sizeofentry = 3;
	ItemContainer.Parameters.push_back(Item_Entry.Item_ID);
	_Hyperlink _gotolink;
	_gotolink._Goto = this->ContainerData.size();
	ItemContainer._Hyperlinks.push_back(_gotolink);

	for (int i = 0; i < Item_Entry.Item_Requirements.size(); i++)
	{
		_MessageContainer newitem;
		newitem.Message_Type = MessageType::_IngredientEntry;
		newitem.sizeofentry = 3;
		newitem.Parameters.push_back(Item_Entry.Item_Requirements[i].Item_ID);
		newitem.Parameters.push_back(Item_Entry.Item_Requirements[i].Item_Amount);
		this->ContainerData[_gotolink._Goto].push_back(newitem);
	}
	for (int i = 0; i < Item_Entry.Item_Requirements.size(); i++)
	{
		ItemContainer.Parameters.push_back(Item_Entry.Item_Requirements[i].Item_ID);
		ItemContainer.Parameters.push_back(Item_Entry.Item_Requirements[i].Item_Amount);
	}
	this->ContainerData[ShopCraftIndex].push_back(ItemContainer);
	this->UI_InfoScrollbar->SetNumberOfLines(1);
	this->MaxIndex = ReturnLineIndexInPhase(PhaseIndex, this->ContainerData[PhaseIndex].size());
	this->UI_InfoScrollbar->SetMaxIndex((this->MaxIndex + 1) - this->_ElementHeight);

}

int UI_InformationBox::ReturnLineIndexInPhase(int PhaseIndex, int Lineindex)
{
	int entrycount = 0;
	if (Lineindex < this->ContainerData[PhaseIndex].size())
	{
		return Lineindex;
	}
	return  this->ContainerData[PhaseIndex].size() -1;
}

void UI_InformationBox::DrawContainerEntry(ID3DXSprite* _Sprite, _MessageContainer _entry, int EntryIndex)
{
	RECT SrcRect;
	switch (_entry.Message_Type)
	{
	case(MessageType::_Text):
	{
		SrcRect.left = this->GetPosition().first + 20;
		SrcRect.right = this->GetPosition().first + 40 + UI_Info_BlockWidth;
		SrcRect.top = this->GetPosition().second + 45 + ((EntryIndex) * 16);
		SrcRect.bottom = this->GetPosition().second + 46 + this->_ElementHeight + ((EntryIndex) * 16);

		this->m_game->MessageFont->DrawTextA(_Sprite, _entry.Message.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 240, 240, 199));

		break;
	}
	case(MessageType::_BuyItem):
	{
		RECT SrcRect;
		SrcRect.left = 0;
		SrcRect.top = 291;
		SrcRect.bottom = SrcRect.top + 31;
		SrcRect.right = SrcRect.left + 31; 
		if (EntryIndex == 11) { SrcRect.bottom -= 16; }
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 20, this->GetPosition().second + 52+ ((EntryIndex) * 16), 0.05);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->Draw(this->InfoIcons.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
		delete Pos;
		delete Center;

		SrcRect.left = this->GetPosition().first + 75;
		SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
		SrcRect.top = this->GetPosition().second + 54 + ((EntryIndex) * 16);
		SrcRect.bottom = SrcRect.top + this->_ElementHeight*2;
		if (EntryIndex == 11) { SrcRect.bottom -= 11; }
		std::string sizeofshop = "Buy Item(s)\n" + std::to_string(this->ContainerData[_entry._Hyperlinks[0]._Goto].size()) + " items in store.";
		this->m_game->MessageFont->DrawTextA(_Sprite,sizeofshop.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 222, 222, 222));

		break;
	}
	case(MessageType::_SellItem):
	{
		RECT SrcRect;
		SrcRect.left = 31;
		SrcRect.top = 291;
		SrcRect.bottom = SrcRect.top + 31;
		SrcRect.right = SrcRect.left + 31;
		if (EntryIndex == 11) { SrcRect.bottom -= 16; }
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 20, this->GetPosition().second + 52 + ((EntryIndex) * 16), 0.05);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->Draw(this->InfoIcons.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
		delete Pos;
		delete Center;

		SrcRect.left = this->GetPosition().first + 75;
		SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
		SrcRect.top = this->GetPosition().second + 54 + ((EntryIndex) * 16);
		SrcRect.bottom = SrcRect.top + this->_ElementHeight * 2;
		if (EntryIndex == 11) { SrcRect.bottom -= 11; }
		std::string sizeofshop = "Sell Item(s)\n" + std::to_string(this->ContainerData[_entry._Hyperlinks[0]._Goto].size()) + " items accepted.";
		this->m_game->MessageFont->DrawTextA(_Sprite, sizeofshop.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 222, 222, 222));


		break;
	}
	case(MessageType::_CraftItem):
	{
		RECT SrcRect;
		SrcRect.left = 124;
		SrcRect.top = 291;
		SrcRect.bottom = SrcRect.top + 31;
		SrcRect.right = SrcRect.left + 31;
		if (EntryIndex == 11) { SrcRect.bottom -= 16; }
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 20, this->GetPosition().second + 52 + ((EntryIndex) * 16), 0.05);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->Draw(this->InfoIcons.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
		delete Pos;
		delete Center;

		SrcRect.left = this->GetPosition().first + 75;
		SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
		SrcRect.top = this->GetPosition().second + 54 + ((EntryIndex) * 16);
		SrcRect.bottom = SrcRect.top + this->_ElementHeight * 2;
		if (EntryIndex == 11) { SrcRect.bottom -= 11; }
		std::string sizeofshop = "Craft Item(s)\n" + std::to_string(this->ContainerData[_entry._Hyperlinks[0]._Goto].size()) + " items accepted.";
		this->m_game->MessageFont->DrawTextA(_Sprite, sizeofshop.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 222, 222, 222));
		

		break; 
	}
	case(MessageType::_BuyItemEntry):
	{
		RECT SrcRect;
		SrcRect.left = 0;
		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + 32;
		SrcRect.right = SrcRect.left + 64;
		if (EntryIndex == 11) { SrcRect.bottom -= 16; }
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 10, this->GetPosition().second + 52 + ((EntryIndex) * 16), 0.05);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->Draw(this->m_game->ResourceManager->CreateTexture(3, 0, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		if (_entry.Parameters.size() > 1)
		{
			int graphic = World::EIF_File->Get(_entry.Parameters[0]).graphic * 2;
			this->m_game->Draw(_Sprite, this->m_game->ResourceManager->CreateTexture(23, (graphic)-1, true).Texture, Pos->x + 32 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Width/2), Pos->y + 16 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Height / 2), 1, D3DCOLOR_ARGB(255, 255, 255, 255));
			delete Pos;
			delete Center;

			SrcRect.left = this->GetPosition().first + 75;
			SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
			SrcRect.top = this->GetPosition().second + 54 + ((EntryIndex) * 16);
			SrcRect.bottom = SrcRect.top + this->_ElementHeight * 3;
			if (EntryIndex == 11) { SrcRect.bottom -= 11; }
			std::string sizeofshop = World::EIF_File->Get(_entry.Parameters[0]).name+"\nprice: " + std::to_string(_entry.Parameters[1]);
			this->m_game->MessageFont->DrawTextA(_Sprite, sizeofshop.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 222, 222, 222));
		}

		else
		{
			delete Pos;
			delete Center;
		}

		break;
	}
	case(MessageType::_SellItemEntry):
	{
		RECT SrcRect;
		SrcRect.left = 0;
		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + 32;
		SrcRect.right = SrcRect.left + 64;
		if (EntryIndex == 11) { SrcRect.bottom -= 16; }
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 10, this->GetPosition().second + 52 + ((EntryIndex) * 16), 0.05);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->Draw(this->m_game->ResourceManager->CreateTexture(3, 0, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		if (_entry.Parameters.size() > 1)
		{
			int graphic = World::EIF_File->Get(_entry.Parameters[0]).graphic * 2;
			this->m_game->Draw(_Sprite, this->m_game->ResourceManager->CreateTexture(23, (graphic)-1, true).Texture, Pos->x + 32 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Width / 2), Pos->y + 16 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Height / 2), 1, D3DCOLOR_ARGB(255, 255, 255, 255));
			delete Pos;
			delete Center;

			SrcRect.left = this->GetPosition().first + 75;
			SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
			SrcRect.top = this->GetPosition().second + 54 + ((EntryIndex) * 16);
			SrcRect.bottom = SrcRect.top + this->_ElementHeight * 3;
			if (EntryIndex == 11) { SrcRect.bottom -= 11; }
			std::string sizeofshop = World::EIF_File->Get(_entry.Parameters[0]).name + "\nprice: " + std::to_string(_entry.Parameters[1]);
			this->m_game->MessageFont->DrawTextA(_Sprite, sizeofshop.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 222, 222, 222));
		}

		else
		{
			delete Pos;
			delete Center;
		}

		break;
	}
	case(MessageType::_CraftItemEntry):
	{
		RECT SrcRect;
		SrcRect.left = 0;
		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + 32;
		SrcRect.right = SrcRect.left + 64;
		if (EntryIndex == 11) { SrcRect.bottom -= 16; }
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 10, this->GetPosition().second + 52 + ((EntryIndex) * 16), 0.05);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->Draw(this->m_game->ResourceManager->CreateTexture(3, 0, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		{
			int  graphic = World::EIF_File->Get(_entry.Parameters[0]).graphic * 2;
			if (_entry.Parameters[0] == 1)
			{
				if (_entry.Parameters[1] == 1)
				{
					graphic = 270;
				}
				else if (_entry.Parameters[1] <= 100)
				{
					graphic = 272;
				}
				else if (_entry.Parameters[1] <= 1000)
				{
					graphic = 274;
				}
				else if (_entry.Parameters[1] <= 100000)
				{
					graphic = 276;
				}
				else //if (m_item->second.amount <= 100000)
				{
					graphic = 278;
				}
			}

			this->m_game->Draw(_Sprite, this->m_game->ResourceManager->CreateTexture(23, (graphic)-1, true).Texture, Pos->x + 32 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Width / 2), Pos->y + 16 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Height / 2), 1, D3DCOLOR_ARGB(255, 255, 255, 255));
			delete Pos;
			delete Center;

			SrcRect.left = this->GetPosition().first + 75;
			SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
			SrcRect.top = this->GetPosition().second + 54 + ((EntryIndex) * 16);
			SrcRect.bottom = SrcRect.top + this->_ElementHeight * 3;
			if (EntryIndex == 11) { SrcRect.bottom -= 11; }
			std::string sizeofshop = World::EIF_File->Get(_entry.Parameters[0]).name + "\ningredients: " + std::to_string((_entry.Parameters.size()-1)/2);
			this->m_game->MessageFont->DrawTextA(_Sprite, sizeofshop.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 222, 222, 222));
		}

		break;
	}
	case(MessageType::_IngredientEntry):
	{
		RECT SrcRect;
		SrcRect.left = 0;
		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + 32;
		SrcRect.right = SrcRect.left + 64;
		if (EntryIndex == 11) { SrcRect.bottom -= 16; }
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 10, this->GetPosition().second + 52 + ((EntryIndex) * 16), 0.05);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->Draw(this->m_game->ResourceManager->CreateTexture(3, 0, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		//if (_entry.Parameters.size() > 1)
		{

			int  graphic = World::EIF_File->Get(_entry.Parameters[0]).graphic * 2;
			if (_entry.Parameters[0] == 1)
			{
				if (_entry.Parameters[1] == 1)
				{
					graphic = 270;
				}
				else if (_entry.Parameters[1] <= 100)
				{
					graphic = 272;
				}
				else if (_entry.Parameters[1] <= 1000)
				{
					graphic = 274;
				}
				else if (_entry.Parameters[1] <= 100000)
				{
					graphic = 276;
				}
				else //if (m_item->second.amount <= 100000)
				{
					graphic = 278;
				}
			}
			this->m_game->Draw(_Sprite, this->m_game->ResourceManager->CreateTexture(23, (graphic)-1, true).Texture, Pos->x + 32 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Width / 2), Pos->y + 16 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Height / 2), 1, D3DCOLOR_ARGB(255, 255, 255, 255));
			delete Pos;
			delete Center;

			SrcRect.left = this->GetPosition().first + 75;
			SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
			SrcRect.top = this->GetPosition().second + 54 + ((EntryIndex) * 16);
			SrcRect.bottom = SrcRect.top + this->_ElementHeight * 3;
			if (EntryIndex == 11) { SrcRect.bottom -= 11; }
			std::string sizeofshop = World::EIF_File->Get(_entry.Parameters[0]).name;// +"\ningredients: " + std::to_string((_entry.Parameters.size() - 1) / 2);
			this->m_game->MessageFont->DrawTextA(_Sprite, sizeofshop.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 222, 222, 222));
			
			
			D3DCOLOR colors[] = { D3DCOLOR_ARGB(180, 222, 222, 222),D3DCOLOR_ARGB(255, 242, 94, 101),  D3DCOLOR_ARGB(255, 242, 94, 101) };
			SrcRect.left = this->GetPosition().first + 75;
			SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
			SrcRect.top += this->_ElementHeight + 2;
			RECT r = SrcRect; // starting point
			int amountowned = this->m_game->Map_UserInterface->map_inventory->ContainsItem(_entry.Parameters[0]);
			std::string strings[] = { std::to_string(amountowned).c_str(), " of ", std::to_string(_entry.Parameters[1]).c_str() };
			std::string craftstr = strings[0] + strings[1] + strings[2];
			//for (int i = 0; i < _countof(strings); ++i)
			{
				this->m_game->MessageFont->DrawTextA(NULL, "ingredients needed: ", -1, &r, DT_CALCRECT, 0);
				this->m_game->MessageFont->DrawTextA(_Sprite, "ingredients needed: ", -1, &r, DT_NOCLIP, colors[0]);
				r.left = r.right;
			}
			SrcRect.left += 100;
			if(amountowned >= _entry.Parameters[1])
			{
				this->m_game->MessageFont->DrawTextA(_Sprite, craftstr.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(222, 132, 241, 95));
			}
			else
			{
				this->m_game->MessageFont->DrawTextA(_Sprite, craftstr.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(222, 242, 94, 101));
			}
		}

		break;
	}
	case(MessageType::_StorageItemEntry):
	{
		RECT SrcRect;
		SrcRect.left = 0;
		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + 32;
		SrcRect.right = SrcRect.left + 64;
		if (EntryIndex == 11) { SrcRect.bottom -= 16; }
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first + 10, this->GetPosition().second + 52 + ((EntryIndex) * 16), 0.05);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->Draw(this->m_game->ResourceManager->CreateTexture(3, 0, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

		if (_entry.Parameters.size() > 1)
		{
			SrcRect;
			SrcRect.left = 0;
			SrcRect.top = 0;
			SrcRect.bottom = SrcRect.top + 32;
			SrcRect.right = SrcRect.left + 64;
			if (EntryIndex == 11) { SrcRect.bottom -= 13; }
			int graphic = World::EIF_File->Get(_entry.Parameters[0]).graphic * 2;
			Pos->x = Pos->x + 32 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Width / 2);
			Pos->y = Pos->y + 16 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Height / 2);
		
			
			_Sprite->Draw(this->m_game->ResourceManager->CreateTexture(23, (graphic)-1, true).Texture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

			//this->m_game->Draw(_Sprite, this->m_game->ResourceManager->CreateTexture(23, (graphic)-1, true).Texture, Pos->x + 32 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Width / 2), Pos->y + 16 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Height / 2), 1, D3DCOLOR_ARGB(255, 255, 255, 255));
			delete Pos;
			delete Center;

			SrcRect.left = this->GetPosition().first + 75;
			SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
			SrcRect.top = this->GetPosition().second + 54 + ((EntryIndex) * 16);
			SrcRect.bottom = SrcRect.top + this->_ElementHeight * 3;
			if (EntryIndex == 11) { SrcRect.bottom -= 22; }
			std::string Addstr = "";
			if(World::EIF_File->Get(_entry.Parameters[0]).type == EIF::Type::Armor)
			{
				if (World::EIF_File->Get(_entry.Parameters[0]).gender == 1)
				{
					Addstr = "(male)";
				}
				else
				{
					Addstr = "(female)";
				}
			}
			std::string sizeofshop = World::EIF_File->Get(_entry.Parameters[0]).name + "\nx " + std::to_string(_entry.Parameters[1]) + " "+ Addstr;
			this->m_game->MessageFont->DrawTextA(_Sprite, sizeofshop.c_str(), -1, &SrcRect, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 222, 222, 222));
		}

		else
		{
			delete Pos;
			delete Center;
		}

		break;
	}
	default:
	{
		break;
	}
	}
}

void UI_InformationBox::ChangePhase(int _PhaseID, bool Backpressed)
{
	if (!Backpressed)
	{
		this->PreviousPhraseIDs.push_back(this->PhaseID);
	}
	else
	{
		this->PreviousPhraseIDs.pop_back();
	}

	this->PhaseID = _PhaseID;
	this->UI_InfoScrollbar->SetIndex(0);
	this->UI_InfoScrollbar->SetNumberOfLines(1);
	this->MaxIndex = ReturnLineIndexInPhase(this->PhaseID, this->ContainerData[this->PhaseID].size());
	this->UI_InfoScrollbar->SetMaxIndex((this->MaxIndex + 12));

	this->InterfaceButtons.clear();
	if (this->PhaseID == 0)
	{
		this->InterfaceButtons.push_back(this->Bt_Cancel);
		this->PreviousPhraseIDs.clear();
	}
	else
	{
		
		if (this->PhaseType == UI_InformationBox::MessageType::_IngredientEntry)
		{
			this->InterfaceButtons.push_back(this->Bt_Back);
			CraftItemEntry newcraft;
			newcraft.Item_ID = 0;
			for (int i = 0; i < this->ContainerData[this->PhaseID].size(); i++)
			{
				ItemEntry newcrafting;
				newcrafting.Item_ID = this->ContainerData[this->PhaseID][i].Parameters[0];
				newcrafting.Item_Amount = this->ContainerData[this->PhaseID][i].Parameters[1];
				newcraft.Item_Requirements.push_back(newcrafting);
			}
			if (this->CheckCraftIngredients(newcraft))
			{
				this->InterfaceButtons.push_back(this->Bt_Okay);
			}

		}
		else
		{		
			this->InterfaceButtons.push_back(this->Bt_Cancel);
			this->InterfaceButtons.push_back(this->Bt_Back);
		}
		
	}
	this->Phasechanged = true;
}

void UI_InformationBox::DrawCraftItemBox(ID3DXSprite* _Sprite, _MessageContainer _entry)
{
	D3DXVECTOR3* Pos = new D3DXVECTOR3(1,1,1);
	D3DXVECTOR3* Center = new D3DXVECTOR3(1, 1, 0);
	RECT rct;
	rct.left = 0;
	rct.right = UI_Info_BlockWidth + 30;
	rct.top = 0;
	rct.bottom = 15 + ((_entry.Parameters.size() - 1) / 2)*45;
	Pos->x = this->m_game->MouseX - (rct.right / 2);
	Pos->y = this->m_game->MouseY - 10;
	_Sprite->Draw(this->m_game->Map_UserInterface->map_ChatBubbleHandler->ChatBoxBG, &rct, Center, Pos, D3DCOLOR_ARGB(166, 0, 0, 0));
	rct.left = Pos->x + 3;
	rct.right = rct.left + UI_Info_BlockWidth + 30;
	rct.top = Pos->y + 3;
	rct.bottom = rct.top + 15 + ((_entry.Parameters.size() - 1) / 2) * 45;
	this->m_game->MessageFont->DrawTextA(_Sprite, "Ingredients Required", -1, &rct, DT_EXPANDTABS, D3DCOLOR_ARGB(255, 222, 222, 222));

	for (int i = 0, j = 1; i < (_entry.Parameters.size() - 1) / 2; i++, j += 2)
	{
		RECT SrcRect;
		SrcRect.left = 0;
		SrcRect.top = 0;
		SrcRect.bottom = SrcRect.top + 32;
		SrcRect.right = SrcRect.left + 64;

		D3DXVECTOR3* _Pos = new D3DXVECTOR3(Pos->x + 10, Pos->y + 25 + (i * 40), 0.05);
		D3DXVECTOR3* _Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->Draw(this->m_game->ResourceManager->CreateTexture(3, 0, true).Texture.get(), &SrcRect, _Center, _Pos, D3DCOLOR_ARGB(255, 255, 255, 255));


		int graphic = World::EIF_File->Get(_entry.Parameters[j]).graphic * 2;
		this->m_game->Draw(_Sprite, this->m_game->ResourceManager->CreateTexture(23, (graphic)-1, true).Texture, _Pos->x + 32 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Width / 2), _Pos->y + 16 - (this->m_game->ResourceManager->GetImageInfo(23, (graphic)-1, true).Height / 2), 1, D3DCOLOR_ARGB(255, 255, 255, 255));


		SrcRect.left = _Pos->x + 75;
		SrcRect.right = SrcRect.left + 20 + UI_Info_BlockWidth;
		SrcRect.top = _Pos->y + 4;
		SrcRect.bottom = SrcRect.top + this->_ElementHeight * 3;
		int amountowned = this->m_game->Map_UserInterface->map_inventory->ContainsItem(_entry.Parameters[j]);
		int amountrequired = _entry.Parameters[j + 1];
		D3DCOLOR drawcol = D3DCOLOR_ARGB(255, 128, 255, 0);
		if (amountowned < amountrequired)
		{
			drawcol = D3DCOLOR_ARGB(255, 237, 28, 36);
		}

		std::string sizeofshop = World::EIF_File->Get(_entry.Parameters[j]).name + "\namount owned: "+ std::to_string(amountowned) +" of " + std::to_string(amountrequired);
		this->m_game->MessageFont->DrawTextA(_Sprite, sizeofshop.c_str(), -1, &SrcRect, DT_EXPANDTABS, drawcol);
		delete _Pos;
		delete _Center;

	}
	delete Pos;
	delete Center;
}

void UI_InformationBox::ShowScrollBox(ScrollBoxType boxtype, int ItemID, int Value, int MaxAmount)
{
	this->_ScrollType = boxtype;
	this->ScrollBoxID = ItemID;
	this->ScrollBoxAmount = MaxAmount;
	this->ScrollValueAmount = Value;

	if (MaxAmount > 1)
	{
		ScrollBoxX = 190;
		ScrollBoxY = 80;
		//this->ScrollBoxX = this->m_game->MouseX - 120;
		//this->ScrollBoxY = this->m_game->MouseY - 120;	
		this->isdragging = false;
		this->isdragselected = false;
		this->ScrollBoxVisible = true;
		this->m_game->world->SetFocusedTextbox(this->TB_ScrollBox);
		this->m_game->SubStage = 99;
		this->ScrollBoxScrollBar->SetMaxIndex(MaxAmount);
		this->ScrollBoxScrollBar->SetIndex(1);
	}
	else
	{
		switch (boxtype)
		{
			case(ScrollBoxType::_SBT_BuyItem):
			{
				this->ScrollBoxAmount = 1;
				std::string msg = "Buy " + std::to_string(ScrollBoxAmount) + " " + World::EIF_File->Get(this->ScrollBoxID).name + " for " + to_string(ScrollBoxAmount * ScrollValueAmount) + " gold?";
				World::ThrowMessage("Buy item(s)", msg, true);
				this->AwaitingResponse = true;
				break;
			}
			case(ScrollBoxType::_SBT_SellItem):
			{			
				this->ScrollBoxAmount = 1;
				std::string msg = "Sell " + std::to_string(ScrollBoxAmount) + " " + World::EIF_File->Get(this->ScrollBoxID).name + " for " + to_string(ScrollBoxAmount * ScrollValueAmount) + " gold?";
				World::ThrowMessage("Sell item(s)", msg, true);
				this->AwaitingResponse = true;
				break;
			}

		}
	}
}

void UI_InformationBox::RenderScrollBox(ID3DXSprite* _Sprite)
{
	RECT BoxRect = { 0,0 ,0,0 };
	BoxRect.left = 38;
	BoxRect.top = 0;
	BoxRect.bottom = BoxRect.top + 170;
	BoxRect.right = BoxRect.left + 265;
	D3DXVECTOR3* Pos = new D3DXVECTOR3(this->ScrollBoxX, this->ScrollBoxY, 0.07);
	D3DXVECTOR3* Centre = new D3DXVECTOR3(0, 0, 0);
	_Sprite->Draw(this->m_game->Map_UserInterface->map_inventory->p_DropJunkTexture.get(), &BoxRect, Centre, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DCOLOR col = D3DCOLOR_ARGB(200, 230, 230, 214);

	EIF_Data m_item = this->m_game->world->EIF_File->Get(this->ScrollBoxID);
	std::string renderstr = "How much ";
	renderstr += m_item.name;
	renderstr += "\nwould you like to ";
	switch (this->_ScrollType)
	{
		case(ScrollBoxType::_SBT_BuyItem):
		{
			BoxRect.left = 39;
			BoxRect.top = 244;
			BoxRect.bottom = BoxRect.top + 20;
			BoxRect.right = BoxRect.left + 244;
			Pos->y = ScrollBoxY + 11;
			Pos->x = ScrollBoxX + 11;
			renderstr += "Buy?";
			_Sprite->Draw(this->m_game->Map_UserInterface->map_inventory->p_DropJunkTexture.get(), &BoxRect, Centre, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

			break;
		}
		case(ScrollBoxType::_SBT_SellItem):
		{
			BoxRect.left = 39;
			BoxRect.top = 244;
			BoxRect.bottom = BoxRect.top + 20;
			BoxRect.right = BoxRect.left + 244;
			Pos->y = ScrollBoxY + 11;
			Pos->x = ScrollBoxX + 11;
			renderstr += "Sell?";
			_Sprite->Draw(this->m_game->Map_UserInterface->map_inventory->p_DropJunkTexture.get(), &BoxRect, Centre, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

			break;
		}
	}

	BoxRect = { 0,0 ,0,0 };
	BoxRect.left = this->ScrollBoxX + 20;
	BoxRect.top = this->ScrollBoxY + 38;
	BoxRect.bottom = BoxRect.top + 100;
	BoxRect.right = BoxRect.left + 250;

	this->m_game->DefaultFont->DrawTextA(_Sprite, renderstr.c_str(), -1, &BoxRect, NULL, col);
	this->UI_ScrollBoxElement_Cancel->Draw(_Sprite);
	this->UI_ScrollBoxElement_Okay->Draw(_Sprite);
	this->TB_ScrollBox->Render(_Sprite);
	this->ScrollBoxScrollBar->Draw(_Sprite);
	delete Pos;
	delete Centre;
}
int sbstartx = 0;
int sbstarty = 0;
void UI_InformationBox::UpdateScrollBox()
{
	if (!World::MBHidden)
	{
		return;
	}
	this->isdragging = false;
	this->isdragselected = false;
	this->UI_ScrollBoxElement_Cancel->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
	this->UI_ScrollBoxElement_Okay->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
	this->ScrollBoxScrollBar->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MouseWheelVal, this->m_game->MousePressed, this->m_game->RAWMousePressed, this->m_game->FPS);
	
	if (this->m_game->MouseX > this->ScrollBoxX&& this->m_game->MouseX < this->ScrollBoxX + 265)
	{
		if (this->m_game->MouseY > this->ScrollBoxY&& this->m_game->MouseY < this->ScrollBoxY + 170)
		{
			int ScrollBarX = this->ScrollBoxScrollBar->GetPosition().first;
			int ScrollBarY = this->ScrollBoxScrollBar->GetPosition().second;
			int Height = this->ScrollBoxScrollBar->GetBarHeight();
		
			if (this->m_game->MouseX > ScrollBarX&& this->m_game->MouseX < ScrollBarX + Height + 16 && this->m_game->MouseY > ScrollBarY&& this->m_game->MouseY < ScrollBarY + 16)
			{

			}
			else if (this->m_game->MousePressed)
			{
				sbstartx = this->ScrollBoxX - this->m_game->MouseX;
				sbstarty = this->ScrollBoxY - this->m_game->MouseY;
			}


		}
	}
	if (this->m_game->RAWMousePressed && sbstartx != 0 && sbstarty != 0)
	{
		this->ScrollBoxX = this->m_game->MouseX + sbstartx;
		this->ScrollBoxY = this->m_game->MouseY + sbstarty;
		if (this->ScrollBoxY > 138)
		{
			this->ScrollBoxY = 138;
		}
	}
	else
	{
		sbstartx = 0;
		sbstarty = 0;
	}
	this->UI_ScrollBoxElement_Cancel->SetPosition(std::pair<int, int>(this->ScrollBoxX + 153, this->ScrollBoxY + 125));
	this->UI_ScrollBoxElement_Okay->SetPosition(std::pair<int, int>(this->ScrollBoxX + 60, this->ScrollBoxY + 125));
	this->ScrollBoxScrollBar->SetPosition(this->ScrollBoxX + 10, this->ScrollBoxY + 96);

	if (this->m_game->RAWMousePressed)
	{
		//m_game->world->DebugPrint(to_string(this->ScrollBoxScrollBar->GetIndex()).c_str());
		this->TB_ScrollBox->text = to_wstring(this->ScrollBoxScrollBar->GetIndex());
		this->TB_ScrollBox->Rendertext = to_wstring(this->ScrollBoxScrollBar->GetIndex());
		this->TB_ScrollBox->UpdateBlinkerOffset();
	}
	else if (this->TB_ScrollBox->text.length() > 0)
	{
		this->ScrollBoxScrollBar->SetIndex(std::stoi(this->TB_ScrollBox->text));
		if (this->ScrollBoxScrollBar->GetIndex() > this->ScrollBoxScrollBar->GetMaxIndex())
		{
			this->ScrollBoxScrollBar->SetIndex(this->ScrollBoxScrollBar->GetMaxIndex());
			this->TB_ScrollBox->text = to_wstring(this->ScrollBoxScrollBar->GetMaxIndex());
			this->TB_ScrollBox->Rendertext = to_wstring(this->ScrollBoxScrollBar->GetMaxIndex());
			this->TB_ScrollBox->UpdateBlinkerOffset();
		}
	}
	else
	{
		//this->ScrollBoxScrollBar->SetIndex(0);
		this->TB_ScrollBox->UpdateBlinkerOffset();
	}

	if (this->UI_ScrollBoxElement_Okay->MouseOverElement() && this->UI_ScrollBoxElement_Okay->MouseClickedOnElement())
	{
		if (this->ScrollBoxScrollBar->GetIndex() != 0)
		{
			switch (this->_ScrollType)
			{
				case(ScrollBoxType::_SBT_BuyItem):
				{
					int amount = this->m_game->Map_UserInterface->map_inventory->ContainsItem(1);
					
					this->ScrollBoxAmount = this->ScrollBoxScrollBar->GetIndex();
					if (amount < this->ScrollBoxScrollBar->GetIndex() * ScrollValueAmount)
					{
						World::ThrowMessage("Warning", "You have not enough gold.");
					}
					else 
					{
						std::string msg = "Buy " + std::to_string(this->ScrollBoxScrollBar->GetIndex()) + " " + World::EIF_File->Get(this->ScrollBoxID).name + " for " + to_string(this->ScrollBoxScrollBar->GetIndex() *ScrollValueAmount) + " gold?";
						World::ThrowMessage("Buy item(s)", msg, true);
						this->AwaitingResponse = true;
					}

					break;
				}
				case(ScrollBoxType::_SBT_SellItem):
				{
					this->ScrollBoxAmount = this->ScrollBoxScrollBar->GetIndex();
					std::string msg = "Sell " + std::to_string(this->ScrollBoxScrollBar->GetIndex()) + " " + World::EIF_File->Get(this->ScrollBoxID).name + " for " + to_string(this->ScrollBoxScrollBar->GetIndex() * ScrollValueAmount) + " gold?";
					World::ThrowMessage("Sell item(s)", msg, true);
					this->AwaitingResponse = true;
					break;
				}
			}
		}
	}
	this->m_game->world->SetFocusedTextbox(this->TB_ScrollBox);

	this->TB_ScrollBox->position.x = this->ScrollBoxX + 160;
	this->TB_ScrollBox->position.y = this->ScrollBoxY + 95;
	if (this->UI_ScrollBoxElement_Okay->MouseOverElement() && this->m_game->MousePressed)
	{
		//this->ScrollBoxID = -1;
		//this->ScrollBoxAmount = 0;
		this->ScrollBoxVisible = false;
	}
	if (this->UI_ScrollBoxElement_Cancel->MouseOverElement() && this->m_game->MousePressed)
	{
		this->ScrollBoxID = -1;
		this->ScrollBoxAmount = 0;
		this->ScrollBoxVisible = false;
		this->TB_ScrollBox->Reset();
		this->m_game->SubStage = 0;
	}
}

bool UI_InformationBox::CheckCraftIngredients(CraftItemEntry _item)
{
	for (int i = 0; i < (_item.Item_Requirements.size()); i++)
	{
		if (this->m_game->Map_UserInterface->map_inventory->ContainsItem(_item.Item_Requirements[i].Item_ID) >= _item.Item_Requirements[i].Item_Amount)
		{
			continue;
		}
		else { return false; }
	}
	return true;
}
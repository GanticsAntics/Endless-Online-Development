#include "..\..\stdafx.h"
#include "Map_UI_Inventory.h"
#include "Map_UI.h"
#include "..\..\Game.h"
#include "..\..\Packet_Handler\Send\SPaperdoll.h"
#include "..\..\Packet_Handler\Send\SItem.h"

Map_UI* Ptr_Inv_MapUI;
Game* Ptr_Inv_Game;
CBitmapEx Black_Bmp;
ID3DXFont* ItemDescFont;
Map_UI_Inventory::Map_UI_Inventory(void* m_UIElement, void* m_Game)
{
	Ptr_Inv_MapUI = (Map_UI *) m_UIElement;
	Ptr_Inv_Game = (Game*)m_Game;
	Black_Bmp = CBitmapEx();
	this->DropJunkScrollBar = new UI_Scrollbar(10, 10, 200, 10, 137, Ptr_Inv_Game->ScrollBarTexture.Texture, Ptr_Inv_Game, Ptr_Inv_Game->TextIconTexture.Texture);
	this->DropJunkScrollBar->SetPosition(130, 100);
	this->DropJunkScrollBar->SetVertical(false);
	this->DropJunkScrollBar->SetButtonsEnabled(false);
	this->DropJunkScrollBar->SetMaxIndex(100);
	D3DXCreateFont(Ptr_Inv_MapUI->m_Device, 12, 0, FW_THIN, 1, FALSE, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"), &ItemDescFont);
	this->p_PPDollTexture = Ptr_Inv_Game->ResourceManager->CreateTexture(2, 49, false).Texture;
	this->p_DropJunkTexture = Ptr_Inv_Game->ResourceManager->CreateTexture(2, 27, false).Texture;
	Black_Bmp.Create(1, 1);
	Black_Bmp.Clear(_RGB(0, 0, 0));
	DWORD dwBufferSize = Black_Bmp.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	LPBYTE buffer;
	buffer = (LPBYTE)malloc(dwBufferSize);
	Black_Bmp.Save(buffer);
	DropMenuY = 120;
	DropMenuX = 180;
	D3DXIMAGE_INFO info = D3DXIMAGE_INFO();
	HRESULT Hr = D3DXCreateTextureFromFileInMemoryEx(Ptr_Inv_MapUI->m_Device, buffer, dwBufferSize, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,NULL, &info, NULL, &this->p_BlackBoxTexture);

	this->UI_Element_PpdollOkay = new Button(*Ptr_Inv_Game->BT_Message_OK);
	this->UI_Element_PpdollOkay->SetPosition(std::pair<int, int>(421, 273));

	this->UI_Element_DropOkay = new Button(*Ptr_Inv_Game->BT_Message_OK);
	this->UI_Element_DropOkay->SetPosition(std::pair<int, int>(421, 273));

	this->UI_Element_DropCancel = new Button(*Ptr_Inv_Game->BT_CharDeleteCancel);
	this->UI_Element_DropCancel->SetPosition(std::pair<int, int>(421, 273));

	this->UI_Element_InventoryButton = new Button(m_Game, 62, 330, 0, 0, 36, 19, false, Ptr_Inv_Game->ResourceManager->CreateTexture(2, 25, false).Texture);
	this->UI_Element_InventoryPPdoll = new Button(m_Game, 486, 340, 38, 385, 88, 19, false, Ptr_Inv_Game->ResourceManager->CreateTexture(2, 27, false).Texture);

	this->UI_Element_InventoryDrop = new Button(m_Game, 491, 399, 0, 15, 38, 37, true, Ptr_Inv_Game->ResourceManager->CreateTexture(2, 27, false).Texture);
	this->UI_Element_InventoryJunk = new Button(m_Game, 531, 399, 0, 89, 38, 37, true, Ptr_Inv_Game->ResourceManager->CreateTexture(2, 27, false).Texture);
	

	D3DXVECTOR2 Pos;
	Pos.x = 107;
	Pos.y = 309;

	D3DXVECTOR2 Size;
	Size.x = 460;
	Size.y = 30;

	Textbox _DropJunkTextbox = Textbox(Pos, Size, D3DCOLOR_ARGB(200, 255, 255, 255), Ptr_Inv_Game->MessageFont, Game::GameStage::PInGame, 0);
	_DropJunkTextbox.blinkhidden = false;
	_DropJunkTextbox.MaxLen = 5;
	_DropJunkTextbox.nonAcceptedKeyEntered = false;
	_DropJunkTextbox.acceptspace = true;
	_DropJunkTextbox.acceptsReturn = true;
	_DropJunkTextbox.SetKeyMask(Textbox::KeyType::Digit);
	this->DropJunkTextbox = Ptr_Inv_Game->world->RegisterTextBox(_DropJunkTextbox);

	int Count = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 14; x++)
		{
			Map_UI_Inventory::InventoryGridCell cell = InventoryGridCell(x, y);
			this->InventoryGrid[Count] = cell;
			Count++;
		}
	}
}
void Map_UI_Inventory::RecalculateInventory()
{
	for (int i = 0; i < 56; i++)
	{
		InventoryGrid[i].ID = -1;
		InventoryGrid[i].MouseOver = false;
		InventoryGrid[i].MousePressed = false;
	}
	for (int i = 0; i < this->inventory.size(); i++)
	{
		this->AddInventoryItem(this->inventory[i]);
	}
	
}
void Map_UI_Inventory::AddInventoryItem(InventoryItem m_item)
{
	bool ItemPlaced = false;
	bool YCollision = false;
	bool Exists = false;
	int Counter = 0;
	for each (InventoryItem Cell in this->inventory)
	{
		EIF_Data m_EIFItem = World::EIF_File->Get(m_item.id);
		if (Cell.id == m_item.id)
		{
			Exists = true;
			break;
		}
		Counter++;
	}
	if (Exists)
	{
		this->inventory[Counter].amount += m_item.amount;
	}
	else
	{
		EIF_Data m_EIFItem = World::EIF_File->Get(m_item.id);
		this->inventory.push_back(m_item);
		if (m_EIFItem.size <= 3)
		{
			int Count = 0;
			for each (InventoryGridCell Cell in this->InventoryGrid)
			{
				if (Cell.ID == -1)
				{
					if (m_EIFItem.size == EIF::Size::Size1x1)
					{
						InventoryGrid[Count].ID = m_EIFItem.id;
						break;
					}
					else
					{
						int y = 0;
						while (y < m_EIFItem.size + 1)
						{
							if (InventoryGrid[Count + (y * 14)].ID == -1)
							{
								if (y == (int)(m_EIFItem.size))
								{
									InventoryGrid[Count].ID = m_EIFItem.id;
									for (int ii = 0; ii < (int)(m_EIFItem.size) + 1; ii++)
									{
										InventoryGrid[Count + (ii * 14)].ID = m_item.id;
									}
									break;
								}
								else
								{
									y++;
								}
							}
							else
							{
								break;
							}
						}
						break;
					}
				}
				Count++;
			}
		}
		else
		{
			int Count = 0;
			EIF_Data m_EIFItem = World::EIF_File->Get(m_item.id);
			for each (InventoryGridCell Cell in this->InventoryGrid)
			{
				if (ItemPlaced)
				{
					break;
				}
				if (Cell.ID == -1 && Cell.X != 13 && Cell.X != 26 && Cell.X != 39)
				{
					int x = 0;
					while (x < 2)
					{
						if (!ItemPlaced || YCollision)
						{
							if (InventoryGrid[Count + x].ID == -1)
							{
								if ((int)(m_EIFItem.size - 4) == 0)
								{
									if (x == 1)
									{
										InventoryGrid[Count + x - 1].ID = m_EIFItem.id;
										InventoryGrid[Count + x].ID = m_EIFItem.id;
										ItemPlaced = true;
									}
									x++;
								}
								else
								{
									int y = 0;
									while (y < (int)(m_EIFItem.size) - 3)
									{
										if (!ItemPlaced)
										{
											if (Count + x + (y * 14) < 56)
											{
												if (InventoryGrid[Count + x + (y * 14)].ID == -1)
												{
													if (y == (int)(m_EIFItem.size) - 4 && x == 1)
													{
														int XX = 0;
														while (XX < 2)
														{
															InventoryGrid[Count + XX].ID = m_item.id;
															for (int iii = 0; iii < (int)(m_EIFItem.size - 3); iii++)
															{
																InventoryGrid[Count + XX + (iii * 14)].ID = m_item.id;
															}
															if (XX == 1)
															{
																ItemPlaced = true;
															}
															XX++;
														}
														break;
													}
												}
												else
												{
													YCollision = true;
													break;
												}
											}
											else
											{
												ItemPlaced = true;
												break;
											}
											y++;
										}
										else
										{
											break;
										}
									}
									x++;
								}
							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
				}
				Count++;
			}
			
		}
	}

}
void Map_UI_Inventory::MoveItem(int _item)
{
	set<int> ItemIDS;
	set<int>::iterator it;
	int Count = 0;
	int MouseX = Ptr_Inv_MapUI->MouseX;
	int MouseY = Ptr_Inv_MapUI->MouseY;
	
	int index = 0;
	InventoryGridCell m_InventoryGrid[56];
	for (int i = 0; i < 56; i++)
	{
		m_InventoryGrid[i] = this->InventoryGrid[i];
	}
	for each (InventoryGridCell Cell in m_InventoryGrid)
	{
		if ((Cell.ID  == -1 || Cell.ID == _item) && Cell.MouseOver)
		{
			EIF_Data m_item = World::EIF_File->Get(_item);
			if ((int)m_item.size <= (3))
			{
				int y = 0;
				while (y < (int)m_item.size + 1)
				{
					if (Count + (y * 14) < 56 && (m_InventoryGrid[Count + y * 14].ID == -1 || (m_InventoryGrid[Count + y * 14].ID == m_item.id)))
					{
						
						m_InventoryGrid[Count + (y * 14)].MouseOver = true;
					}
					else
					{
						return;
					}
					y++;
				}
			}
			else
			{
				int x = 0;
				while (x < 2)
				{
					int y = 0;
					while (y < ((int)m_item.size) - 3)
					{
						if (Count + x + (y * 14) < 56 && Cell.X != 13 && Cell.X != 26 && Cell.X != 39 && (m_InventoryGrid[Count + x + (y * 14)].ID == -1 || m_InventoryGrid[Count + x + (y * 14)].ID == m_item.id))
						{
							m_InventoryGrid[Count + x + (y * 14)].MouseOver = true;
						}
						else
						{
							return;
						}
						y++;
					}
					x++;
				}
			}
			
			if (!Ptr_Inv_MapUI->MouseHeld)
			{
				for (int i = 0; i < 56; i++)
				{
					if (InventoryGrid[i].ID == m_item.id)
					{
						InventoryGrid[i].ID = -1;
						InventoryGrid[i].MouseOver = false;
						InventoryGrid[i].MousePressed = false;
						m_InventoryGrid[i].ID = -1;
						m_InventoryGrid[i].MouseOver = false;
						m_InventoryGrid[i].MousePressed = false;
					}
				}
				if ((int)m_item.size <= (3))
				{
					int y = 0;
					while (y < (int)m_item.size + 1)
					{
						if (Count + (y * 14) < 56 && (m_InventoryGrid[Count + y * 14].ID == -1 || m_InventoryGrid[Count + y * 14].ID == m_item.id))
						{
							m_InventoryGrid[Count + (y * 14)].ID = m_item.id;
						}
						else
						{
							return;
						}
						y++;
					}
				}
				else
				{
					int x = 0;
					while (x < 2)
					{
						int y = 0;
						while (y < ((int)m_item.size) - 3)
						{
							if (Count + x + (y * 14) < 56 && Cell.X != 13 && Cell.X != 26 && Cell.X != 39 && (m_InventoryGrid[Count + x + (y * 14)].ID == -1 || m_InventoryGrid[Count + x + (y * 14)].ID == m_item.id))
							{
								m_InventoryGrid[Count + x + (y * 14)].ID = m_item.id;
							}
							else
							{
								return;
							}
							y++;
						}
						x++;
					}
				}
			}
			for (int i = 0; i < 56; i++)
			{
				InventoryGrid[i] = m_InventoryGrid[i];
			}
			return;
		}
		Count++;
	}
}
time_t clicktimerstart, clicktimerend;
void Map_UI_Inventory::Update()
{
	//this->DropJunkTextbox->
	clicktimerend = clock();
	this->UI_Element_InventoryButton->Update(Ptr_Inv_MapUI->MouseX, Ptr_Inv_MapUI->MouseY, Ptr_Inv_MapUI->MousePressed);
	if (this->UI_Element_InventoryButton->MouseClickedOnElement())
	{
		Ptr_Inv_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Inventory, 0);
	}
	if (this->PaperdollVisible)
	{
		this->UpdatePaperdoll();
		if (this->UI_Element_PpdollOkay->MouseOverElement() && Ptr_Inv_Game->MousePressed)
		{
			this->paperdoll._PlayerID = -1;
			this->PaperdollVisible = false;
		}
	}
	if (this->IsDropMenuActive)
	{
		this->UpdateDropJunk();
		Ptr_Inv_MapUI->isactive = false;
		Ptr_Inv_Game->world->SetFocusedTextbox(this->DropJunkTextbox);
		
		this->DropJunkTextbox->position.x = this->DropMenuX + 160;
		this->DropJunkTextbox->position.y = this->DropMenuY + 95;
		if (this->UI_Element_DropOkay->MouseOverElement() && Ptr_Inv_Game->MousePressed)
		{
			this->DropID = -1;
			this->DropAmount = 0;
			this->IsDropMenuActive = false;
			Ptr_Inv_MapUI->isactive = true;
		}
		if (this->UI_Element_DropCancel->MouseOverElement() && Ptr_Inv_Game->MousePressed)
		{
			this->DropID = -1;
			this->DropAmount = 0;
			this->IsDropMenuActive = false;
			Ptr_Inv_MapUI->isactive = true;
		}
	}
	switch (Ptr_Inv_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Inventory):
	{
		this->UI_Element_InventoryDrop->Update(Ptr_Inv_MapUI->MouseX, Ptr_Inv_MapUI->MouseY, Ptr_Inv_MapUI->MousePressed);
		this->UI_Element_InventoryJunk->Update(Ptr_Inv_MapUI->MouseX, Ptr_Inv_MapUI->MouseY, Ptr_Inv_MapUI->MousePressed);
		this->UI_Element_InventoryPPdoll->Update(Ptr_Inv_MapUI->MouseX, Ptr_Inv_MapUI->MouseY, Ptr_Inv_MapUI->MousePressed);
		int MouseX = Ptr_Inv_MapUI->MouseX;
		int MouseY = Ptr_Inv_MapUI->MouseY;
		int index = 0;
		if (this->UI_Element_InventoryDrop->MouseOverElement())
		{
			if (this->childMPindex >= 0 && !Ptr_Inv_MapUI->MouseHeld)
			{
				int amount = 0;
				for (int i = 0; i < this->inventory.size(); i++)
				{
					if (this->inventory[i].id == this->childMPindex)
					{
						amount = this->inventory[i].amount;
					}
				}
				if (amount == 1)
				{
					SItem::SendDrop(Ptr_Inv_Game->world->connection->ClientStream, Ptr_Inv_Game->Map_UserInterface->map_inventory->childMPindex, 1, Ptr_Inv_Game->map->m_Players[World::WorldCharacterID]->x, Ptr_Inv_Game->map->m_Players[World::WorldCharacterID]->y, Ptr_Inv_Game);
					this->childMPindex = -1;
				}
				else if (amount > 1)
				{
					this->DisplayDropDialogye(true, amount, this->childMPindex, Ptr_Inv_Game->map->m_Players[World::WorldCharacterID]->x, Ptr_Inv_Game->map->m_Players[World::WorldCharacterID]->y);
					this->childMPindex = -1;
				}
			}
		}
		else if (this->UI_Element_InventoryJunk->MouseOverElement())
		{
			if (this->childMPindex >= 0 && !Ptr_Inv_MapUI->MouseHeld)
			{
				int amount = 0;
				for (int i = 0; i < this->inventory.size(); i++)
				{
					if (this->inventory[i].id == this->childMPindex)
					{
						amount = this->inventory[i].amount;
					}
				}
				if (amount == 1)
				{
					//World::ThrowMessage("Warning!", "Do you really want to junk this item?", true);
					SItem::SendJunk(Ptr_Inv_Game->world->connection->ClientStream, Ptr_Inv_Game->Map_UserInterface->map_inventory->childMPindex, 1,  Ptr_Inv_Game);
					this->childMPindex = -1;
				}
				else if (amount > 1)
				{
					this->DisplayDropDialogye(false, amount, this->childMPindex, Ptr_Inv_Game->map->m_Players[World::WorldCharacterID]->x, Ptr_Inv_Game->map->m_Players[World::WorldCharacterID]->y);
					this->childMPindex = -1;
				}
			}
		}
		if (UI_Element_InventoryPPdoll->MouseOverElement() && Ptr_Inv_Game->MousePressed)
		{
			SPaperdoll::SendPaperdollRequest(Ptr_Inv_Game->world->connection->ClientStream, World::WorldCharacterID, Ptr_Inv_Game);
		}
		for each (InventoryGridCell Cell in this->InventoryGrid)
		{
			if (MouseX > 113 + (22 * Cell.X) + (Cell.X * 4) && MouseX < 113 + (22 * Cell.X) + (Cell.X * 4) + 27 && MouseY >(339) + (Cell.Y * 4) + (22 * Cell.Y) && MouseY < (339) + (Cell.Y * 4) + (22 * Cell.Y) + 27)
			{
				this->InventoryGrid[index].MouseOver = true;
				
				//this->InventoryGrid[index].MouseOver = true;
				childMOindex = Cell.ID;
				if (childMPindex == -1 && Ptr_Inv_MapUI->MouseHeld && Cell.ID != -1)
				{
					if (clicktimerend - clicktimerstart < 500)
					{
						int subid = 0;
						EIF_Data m_item = World::EIF_File->Get(Cell.ID);
						int itemloc = 0;
						if(m_item.type >= EIF::Type::Weapon && m_item.type <= EIF::Type::Bracer)
						{
							switch (m_item.type)
							{
							case(EIF::Type::Boots):
							{
								itemloc = 0;
								break;
							}
							case(EIF::Type::Accessory):
							{
								itemloc = 1;
								break;
							}
							case(EIF::Type::Gloves):
							{
								itemloc = 2;
								break;
							}
							case(EIF::Type::Belt):
							{
								itemloc = 3;
								break;
							}
							case(EIF::Type::Armor):
							{
								itemloc = 4;
								break;
							}
							case(EIF::Type::Necklace):
							{
								itemloc = 5;
								break;
							}
							case(EIF::Type::Hat):
							{
								itemloc = 6;
								break;
							}
							case(EIF::Type::Shield):
							{
								itemloc = 7;
								break;
							}
							case(EIF::Type::Weapon):
							{
								itemloc = 8;
								break;
							}
							case(EIF::Type::Ring):
							{
								itemloc = 9;
								break;
							}
							case(EIF::Type::Armlet):
							{
								itemloc = 11;
								break;
							}
							case(EIF::Type::Bracer):
							{
								itemloc = 13;
								break;
							}
							}
							for (int i = 0; i < 15; i++)
							{
								if (i > itemloc) { break; }
								if (this->paperdoll._paperdoll[i] == Cell.ID) { subid++; }
							}
							if (subid <= 1)
							{
								SPaperdoll::SendPaperdollAdd(Ptr_Inv_Game->world->connection->ClientStream, Cell.ID, subid, Ptr_Inv_Game);
							}
						}
					}
					clicktimerstart = clock();
					this->InventoryGrid[index].MousePressed = true;
					childMPindex = Cell.ID;
				}
			}
			else
			{
				this->InventoryGrid[index].MouseOver = false;
			}
			if (childMPindex == Cell.ID && childMPindex != -1)
			{
				this->InventoryGrid[index].MousePressed = true;
			}
			if (!Ptr_Inv_MapUI->MouseHeld)
			{
				this->InventoryGrid[index].MousePressed = false;
			}
			index++;
		}
		if (childMPindex >= 0)
		{
			this->MoveItem(childMPindex);
		}
		break;
	}
	default:
		return;
	}
}

void Map_UI_Inventory::Render()
{
	this->UI_Element_InventoryButton->Draw(Ptr_Inv_MapUI->Sprite);
	switch (Ptr_Inv_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Inventory):
	{
		Ptr_Inv_Game->Draw(Ptr_Inv_MapUI->Sprite, Ptr_Inv_Game->ResourceManager->CreateTexture(2, 44, false).Texture, 102, 332, 0.1f, D3DCOLOR_ARGB(255, 255, 255, 255));
		this->UI_Element_InventoryDrop->Draw(Ptr_Inv_MapUI->Sprite);
		this->UI_Element_InventoryJunk->Draw(Ptr_Inv_MapUI->Sprite);

		int x = 429;
		int y = 370;
		RECT rct;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		std::string m_message = "Weight " + to_string(this->Weight) + "/" + to_string(this->MaxWeight);

		Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_CENTER, D3DCOLOR_ARGB(200, 255, 255, 255));
		this->UI_Element_InventoryPPdoll->Draw(Ptr_Inv_MapUI->Sprite);
		set<int> ItemIDS;
		set<int>::iterator it;
		for each (InventoryGridCell Cell in this->InventoryGrid)
		{
			RECT SrcRect;
			SrcRect.left = 0;
			SrcRect.top = 162;
			SrcRect.bottom = SrcRect.top + 22;
			SrcRect.right = SrcRect.left + 22;
			int x = (114) + (22 * Cell.X) + (Cell.X * 4);
			int y = (340) + (4 * Cell.Y) + (Cell.Y * 22);
			D3DXVECTOR3* Pos = new D3DXVECTOR3(x, y, 0);
			D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
			D3DCOLOR col = D3DCOLOR_ARGB(255, 255, 255, 255);

			if (Cell.MouseOver)
			{
				SrcRect.top = 162 + 22;
				SrcRect.bottom = SrcRect.top + 22;
				col = D3DCOLOR_ARGB(150, 255, 255, 255);
			}
			Ptr_Inv_MapUI->Sprite->Draw(Ptr_Inv_Game->ResourceManager->CreateTexture(2, 27, true).Texture.get(), &SrcRect, Center, Pos, col);
			if (Cell.ID != -1 && Cell.ID != childMPindex)
			{
				for each (InventoryGridCell ChildCell in this->InventoryGrid)
				{
					if (Cell.ID == ChildCell.ID && childMOindex == Cell.ID)
					{
						col = D3DCOLOR_ARGB(255, 255, 255, 255);
						SrcRect.top = 162 + 22;
						SrcRect.bottom = SrcRect.top + 22;

						Ptr_Inv_MapUI->Sprite->Draw(Ptr_Inv_Game->ResourceManager->CreateTexture(2, 27, true).Texture.get(), &SrcRect, Center, Pos, col);
					}
				}
			}
			delete Pos;
			delete Center;
		}
		for each (InventoryGridCell Cell in this->InventoryGrid)
		{
			RECT SrcRect;
			SrcRect.left = 0;
			SrcRect.top = 162;
			SrcRect.bottom = SrcRect.top + 22;
			SrcRect.right = SrcRect.left + 22;
			int x = (114) + (22 * Cell.X) + (Cell.X * 4);
			int y = (340) + (4 * Cell.Y) + (Cell.Y * 22);
			D3DXVECTOR3* Pos = new D3DXVECTOR3(x, y, 0);
			D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
			D3DCOLOR col = D3DCOLOR_ARGB(255, 255, 255, 255);


			it = ItemIDS.find(Cell.ID);
			if (it == ItemIDS.end())
			{
				EIF_Data m_item = World::EIF_File->Get(Cell.ID);
				
				D3DXVECTOR3* itemPos = new D3DXVECTOR3(x, y, 0);
				D3DXVECTOR3* itemCenter = new D3DXVECTOR3(0, 0, 0);
				if (Cell.MousePressed)
				{
					int m_itemHeight = Ptr_Inv_Game->ResourceManager->GetImageInfo(23, m_item.graphic * 2, true).Height;
					int m_itemWidth = Ptr_Inv_Game->ResourceManager->GetImageInfo(23, m_item.graphic * 2, true).Width;

					itemPos->x = Ptr_Inv_Game->MouseX - m_itemWidth / 2;
					itemPos->y = Ptr_Inv_Game->MouseY - m_itemHeight / 2;
					Ptr_Inv_MapUI->Sprite->Draw(Ptr_Inv_Game->ResourceManager->CreateTexture(23, m_item.graphic * 2, true).Texture.get(), NULL, itemCenter, itemPos, D3DCOLOR_ARGB(150, 255, 255, 255));
				}
				else
				{
					Ptr_Inv_MapUI->Sprite->Draw(Ptr_Inv_Game->ResourceManager->CreateTexture(23, m_item.graphic * 2, true).Texture.get(), NULL, itemCenter, itemPos, D3DCOLOR_ARGB(255, 255, 255, 255));
				}
				ItemIDS.insert(Cell.ID);
			}
			delete Pos;
			delete Center;
		}
		for each (InventoryGridCell Cell in this->InventoryGrid)
		{
			if (Cell.MouseOver && Cell.ID != -1)
			{
				int inventoryindex = 0;
				for (int i = 0; i < this->inventory.size(); i++)
				{
					if (Cell.ID == this->inventory[i].id)
					{
						inventoryindex = i;
						break;
					}
				}
				EIF_Data m_item = World::EIF_File->Get(Cell.ID);
				RECT rcRect = { 0,0 ,0,0 };
				std::string message = m_item.name;
				if (m_item.type == EIF::Type::Money)
				{
					message = to_string(this->inventory[inventoryindex].amount) + " " + m_item.name;
				}
				else
				{
					if (this->inventory[inventoryindex].amount > 1)
					{
						message = to_string(this->inventory[inventoryindex].amount) + " x "+ m_item.name;
					}
				}
				Ptr_Inv_MapUI->DrawHelpMessage("Item", message);
				Ptr_Inv_Game->MessageFont->DrawTextA(NULL, message.c_str(), message.size(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
				
				RECT ItemDescriptBox = { 0,0 ,0,0 };
				std::string DecriptionString = "";
				std::string ItemType = "";

				switch (m_item.type)
				{
					case(EIF::Type::Weapon):
					{
						ItemType = "Weapon";
						break;
					}
					case(EIF::Type::Armor):
					{
						ItemType = "Armor";
						break;
					}
					case(EIF::Type::Bracer):
					{
						ItemType = "Bracer";
						break;
					}
					case(EIF::Type::Accessory):
					{
						ItemType = "Accessory";
						break;
					}
					case(EIF::Type::Hat):
					{
						ItemType = "Hat";
						break;
					}
					case(EIF::Type::Armlet):
					{
						ItemType = "Armlet";
						break;
					}
					case(EIF::Type::Belt):
					{
						ItemType = "Belt";
						break;
					}
					case(EIF::Type::Boots):
					{
						ItemType = "Boots";
						break;
					}
					case(EIF::Type::Shield):
					{
						ItemType = "Shield";
						break;
					}
					case(EIF::Type::Gloves):
					{
						ItemType = "Gloves";
						break;
					}
					case(EIF::Type::Necklace):
					{
						ItemType = "Necklace";
						break;
					}
					case(EIF::Type::Ring):
					{
						ItemType = "Ring";
						break;
					}
				}
				if (ItemType != "")
				{
					DecriptionString += "Item Type : " + ItemType + "\n";
					DecriptionString += "Level Req : " + to_string(m_item.levelreq) + "\n";
					DecriptionString += "Attack : " + to_string(m_item.mindam) + " - " + to_string(m_item.maxdam) + "\n";

					DecriptionString += "reqcon	: " + to_string(m_item.conreq) + "	   reqwis	: " + to_string(m_item.wisreq) + "	   reqstr	: " + to_string(m_item.strreq);
					DecriptionString += "    reqcha	: " + to_string(m_item.chareq) + "	  reqint	: " + to_string(m_item.intreq) + "\n";

					DecriptionString += "+ con	: " + to_string(m_item.str) + "	   + wis	: " + to_string(m_item.wis) + "	   + str	: " + to_string(m_item.str);
					DecriptionString += "    + cha	: " + to_string(m_item.con) + "	  + int	: " + to_string(m_item.intl) + "\n";
				}

				ItemDescFont->DrawTextA(NULL, DecriptionString.c_str(), DecriptionString.size(), &ItemDescriptBox, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
				
				int m_itemHeight = Ptr_Inv_Game->ResourceManager->GetImageInfo(23, m_item.graphic * 2, true).Height;
				int m_itemWidth = Ptr_Inv_Game->ResourceManager->GetImageInfo(23, m_item.graphic * 2, true).Width;
				int x = (114) + (22 * Cell.X) + (Cell.X * 4) + 8 + m_itemWidth;

				RECT DrawBox = { 0,0 ,0,0 };
				DrawBox.left =  rcRect.left;
				DrawBox.top =  rcRect.top;
				DrawBox.bottom = rcRect.bottom + ItemDescriptBox.bottom + 4;
				DrawBox.right = rcRect.right + 4;
				if (ItemDescriptBox.right > rcRect.right)
				{
					DrawBox.right = ItemDescriptBox.right + 4;
				}
				if (Cell.X > 7)
				{
					x = (114) + (22 * Cell.X) + (Cell.X * 4) + 8 - ItemDescriptBox.right;
				}
				int y = (340) + (4 * Cell.Y) + (Cell.Y * 22) + 4;
				if (y + DrawBox.bottom + 4 > 480)
				{
					y -= ((y + DrawBox.bottom) - (480)) ;
				}
				//int x = Ptr_Inv_MapUI->MouseX;
				//int y = Ptr_Inv_MapUI->MouseY;
				D3DXVECTOR3* BoxPos = new D3DXVECTOR3(x, y, 0);
				D3DXVECTOR3* BoxCenter = new D3DXVECTOR3(0, 0, 0);
				D3DCOLOR Boxcol = D3DCOLOR_ARGB(150, 255, 255, 255);

				Ptr_Inv_MapUI->Sprite->Draw(this->p_BlackBoxTexture, &DrawBox, BoxCenter, BoxPos, Boxcol);
				
				RECT BoxRect = { 0,0 ,0,0 };
				BoxRect.left = x + 2 + DrawBox.left;
				BoxRect.top = y + 1 + DrawBox.top;
				BoxRect.bottom = y + 1 + DrawBox.bottom;
				BoxRect.right = x + 1 + DrawBox.right;

				Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, message.c_str(), -1, &BoxRect, NULL, D3DCOLOR_XRGB(255, 255, 255));
				BoxRect.left = x + 2 + DrawBox.left;
				BoxRect.top = y + 1 + DrawBox.top + rcRect.bottom;
				BoxRect.bottom = y + 1 + DrawBox.bottom + rcRect.bottom;
				BoxRect.right = x + 1 + DrawBox.right;
				ItemDescFont->DrawTextA(Ptr_Inv_MapUI->Sprite, DecriptionString.c_str(), -1, &BoxRect, NULL, D3DCOLOR_XRGB(255, 255, 200));
				delete BoxPos;
				delete BoxCenter;
				break;
			}
		}
		break;
	}
	default:
		//this->PaperdollVisible = false;
		break;
	}

	if (this->PaperdollVisible)
	{
		this->RenderPaperdoll();
	}
	else if (this->IsDropMenuActive)
	{
		this->RenderDropJunk();
	}
}
///Endshittycommand
struct PPDollInfo
{
	Map_UI_Inventory::EquipLocation location;
	int xoff;
	int yoff;
};
static constexpr PPDollInfo PaperdollInformation[15] = {
{ Map_UI_Inventory::EquipLocation::Boots,     90,218	,  },
{ Map_UI_Inventory::EquipLocation::Accessory,     55,250,  },
{ Map_UI_Inventory::EquipLocation::Gloves,   25,190,  },
{ Map_UI_Inventory::EquipLocation::Belt,   90,187,  },
{ Map_UI_Inventory::EquipLocation::Armor,     90,90,  },
{ Map_UI_Inventory::EquipLocation::Necklace,   155,53,  },
{ Map_UI_Inventory::EquipLocation::Hat,   90,35,  },
{ Map_UI_Inventory::EquipLocation::Shield,   167, 90,  },
{ Map_UI_Inventory::EquipLocation::Weapon,  25,80,  },
{ Map_UI_Inventory::EquipLocation::Ring1,    150,189,  },
{ Map_UI_Inventory::EquipLocation::Ring2,    185,189,  },
{ Map_UI_Inventory::EquipLocation::Armlet1,   150,219,  },
{ Map_UI_Inventory::EquipLocation::Armlet2,  185,219,  },
{ Map_UI_Inventory::EquipLocation::Bracer1, 150,249,  },
{ Map_UI_Inventory::EquipLocation::Bracer2,  185,249,  },
};
void Map_UI_Inventory::RenderPaperdoll()
{
	if (this->paperdoll._PlayerID >= 0)
	{
		RECT BoxRect = { 0,0 ,0,0 };
		BoxRect.left = 0;
		BoxRect.top = Ptr_Inv_Game->map->m_Players[this->paperdoll._PlayerID]->Gender * 290;
		BoxRect.bottom = BoxRect.top + 290;
		BoxRect.right = 380;
		D3DXVECTOR3* Pos = new D3DXVECTOR3(PPdollX, PPdollY, 0.07);
		D3DXVECTOR3* Centre = new D3DXVECTOR3(0, 0, 0);
		Ptr_Inv_MapUI->Sprite->Draw(this->p_PPDollTexture.get(), &BoxRect, Centre, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
		this->UI_Element_PpdollOkay->Draw(Ptr_Inv_MapUI->Sprite);

		for (int i = 0; i < 15; i++)
		{
			Pos = new D3DXVECTOR3(PPdollX + PaperdollInformation[i].xoff, PPdollY + PaperdollInformation[i].yoff, 0.07);
			EIF_Data m_item = World::EIF_File->Get(this->paperdoll._paperdoll[i]);
			Ptr_Inv_MapUI->Sprite->Draw(Ptr_Inv_Game->ResourceManager->CreateTexture(23, m_item.graphic * 2, true).Texture.get(), NULL, Centre, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		D3DCOLOR col = D3DCOLOR_ARGB(200, 255, 255, 255);
		BoxRect = { 0,0 ,0,0 };
		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 22;
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;

		Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, this->paperdoll._name.c_str(), -1, &BoxRect, NULL, col);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 22 + (30 * 1);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;
		this->paperdoll._home = "Wanderer";
		Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, this->paperdoll._home.c_str(), -1, &BoxRect, NULL, col);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 22 + (30 * 2);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;
		this->paperdoll._class = "Warrior";
		Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, this->paperdoll._class.c_str(), -1, &BoxRect, NULL, col);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 22 + (30 * 3);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;

		Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, this->paperdoll._partner.c_str(), -1, &BoxRect, NULL, col);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 22 + (30 * 4);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;

		Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, this->paperdoll._title.c_str(), -1, &BoxRect, NULL, col);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 22 + (30 * 5);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;

		Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, this->paperdoll._job.c_str(), -1, &BoxRect, NULL, col);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 22 + (30 * 6);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;

		Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, this->paperdoll._guild.c_str(), -1, &BoxRect, NULL, col);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 22 + (30 * 7);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;

		Ptr_Inv_Game->MessageFont->DrawTextA(Ptr_Inv_MapUI->Sprite, this->paperdoll._rank.c_str(), -1, &BoxRect, NULL, col);

		delete Pos;
		delete Centre;
	}
}
int startx = 0;
int starty = 0;
void Map_UI_Inventory::UpdatePaperdoll()
{
	this->UI_Element_PpdollOkay->Update(Ptr_Inv_MapUI->MouseX, Ptr_Inv_MapUI->MouseY, Ptr_Inv_MapUI->MousePressed);
	if (Ptr_Inv_MapUI->MouseX > this->PPdollX && Ptr_Inv_MapUI->MouseX < this->PPdollX + 380)
	{
		if (Ptr_Inv_MapUI->MouseY > this->PPdollY && Ptr_Inv_MapUI->MouseY < this->PPdollY + 290)
		{
			PaperdollCheckElements();
			if (Ptr_Inv_MapUI->MousePressed)
			{
				startx = PPdollX - Ptr_Inv_MapUI->MouseX;
				starty = PPdollY - Ptr_Inv_MapUI->MouseY;
			}
		}
	}
	if (Ptr_Inv_MapUI->MouseHeld && startx != 0 && starty != 0)
	{
		this->PPdollX = Ptr_Inv_MapUI->MouseX + startx;
		this->PPdollY = Ptr_Inv_MapUI->MouseY + starty;
		if(this->PPdollY > 20)
		{
			this->PPdollY = 20;
		}
	}
	else
	{
		startx = 0;
		starty = 0;
	}
	this->UI_Element_PpdollOkay->SetPosition(std::pair<int, int>(PPdollX + 276, PPdollY + 253));
}
void Map_UI_Inventory::RenderDropJunk()
{
	RECT BoxRect = { 0,0 ,0,0 };
	BoxRect.left = 38;
	BoxRect.top = 0;
	BoxRect.bottom = BoxRect.top + 170;
	BoxRect.right = BoxRect.left+265;
	D3DXVECTOR3* Pos = new D3DXVECTOR3(DropMenuX, DropMenuY, 0.07);
	D3DXVECTOR3* Centre = new D3DXVECTOR3(0, 0, 0);
	Ptr_Inv_MapUI->Sprite->Draw(this->p_DropJunkTexture.get(), &BoxRect, Centre, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DCOLOR col = D3DCOLOR_ARGB(200, 230, 230, 214);
	
	EIF_Data m_item = Ptr_Inv_Game->world->EIF_File->Get(this->DropID);
	std::string renderstr = "How much ";
	renderstr += m_item.name;
	renderstr +=  "\nwould you like to ";
	
	if (!this->DropOrJunk)
	{
		BoxRect.left = 39;
		BoxRect.top = 174;
		BoxRect.bottom = BoxRect.top + 20;
		BoxRect.right = BoxRect.left + 244;
		Pos->y = DropMenuY + 11;
		Pos->x = DropMenuX + 11;
		renderstr += "junk?";
		Ptr_Inv_MapUI->Sprite->Draw(this->p_DropJunkTexture.get(), &BoxRect, Centre, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		renderstr += "drop?";
	}
	BoxRect = { 0,0 ,0,0 };
	BoxRect.left = this->DropMenuX + 20;
	BoxRect.top = this->DropMenuY + 38;
	BoxRect.bottom = BoxRect.top + 100;
	BoxRect.right = BoxRect.left + 250;

	Ptr_Inv_Game->DefaultFont->DrawTextA(Ptr_Inv_MapUI->Sprite, renderstr.c_str(), -1, &BoxRect, NULL, col);
	this->UI_Element_DropCancel->Draw(Ptr_Inv_MapUI->Sprite);
	this->UI_Element_DropOkay->Draw(Ptr_Inv_MapUI->Sprite);
	this->DropJunkTextbox->Render(Ptr_Inv_MapUI->Sprite);
	this->DropJunkScrollBar->Draw(Ptr_Inv_MapUI->Sprite);
}
void Map_UI_Inventory::UpdateDropJunk()
{
	this->UI_Element_DropCancel->Update(Ptr_Inv_MapUI->MouseX, Ptr_Inv_MapUI->MouseY, Ptr_Inv_MapUI->MousePressed);
	this->UI_Element_DropOkay->Update(Ptr_Inv_MapUI->MouseX, Ptr_Inv_MapUI->MouseY, Ptr_Inv_MapUI->MousePressed);
	this->DropJunkScrollBar->Update(Ptr_Inv_MapUI->MouseX, Ptr_Inv_MapUI->MouseY, Ptr_Inv_MapUI->MousePressed, Ptr_Inv_MapUI->MouseHeld, Ptr_Inv_MapUI->FPS);
	if (Ptr_Inv_MapUI->MouseX > this->DropMenuX && Ptr_Inv_MapUI->MouseX < this->DropMenuX + 265)
	{
		if (Ptr_Inv_MapUI->MouseY > this->DropMenuY && Ptr_Inv_MapUI->MouseY < this->DropMenuY + 170)
		{
			int DropJunkBarX = this->DropJunkScrollBar->GetPosition().first;
			int DropJunkBarY = this->DropJunkScrollBar->GetPosition().second;
			int Height = this->DropJunkScrollBar->GetBarHeight();
			if (Ptr_Inv_MapUI->MouseX > DropJunkBarX && Ptr_Inv_MapUI->MouseX < DropJunkBarX + Height + 16 && Ptr_Inv_MapUI->MouseY > DropJunkBarY && Ptr_Inv_MapUI->MouseY < DropJunkBarY + 16)
			{
				
			}
			else if (Ptr_Inv_MapUI->MousePressed)
			{
				startx = DropMenuX - Ptr_Inv_MapUI->MouseX;
				starty = DropMenuY - Ptr_Inv_MapUI->MouseY;
			}
				
			
		}
	}
	if (Ptr_Inv_MapUI->MouseHeld && startx != 0 && starty != 0)
	{
		this->DropMenuX = Ptr_Inv_MapUI->MouseX + startx;
		this->DropMenuY = Ptr_Inv_MapUI->MouseY + starty;
		if (this->DropMenuY > 138)
		{
			this->DropMenuY = 138;
		}
	}
	else
	{
		startx = 0;
		starty = 0;
	}
	this->UI_Element_DropCancel->SetPosition(std::pair<int, int>(DropMenuX + 153, DropMenuY + 125));
	this->UI_Element_DropOkay->SetPosition(std::pair<int, int>(DropMenuX + 60, DropMenuY + 125));
	this->DropJunkScrollBar->SetPosition(DropMenuX + 10, DropMenuY + 96);
	
	if (Ptr_Inv_Game->RAWMousePressed)
	{
		this->DropJunkTextbox->text = to_wstring(this->DropJunkScrollBar->GetIndex());
		this->DropJunkTextbox->Rendertext = to_wstring(this->DropJunkScrollBar->GetIndex());
		this->DropJunkTextbox->UpdateBlinkerOffset();
	}
	else if (this->DropJunkTextbox->text.length() > 0)
	{
		this->DropJunkScrollBar->SetIndex(std::stoi(this->DropJunkTextbox->text));
		if (this->DropJunkScrollBar->GetIndex() > this->DropJunkScrollBar->GetMaxIndex())
		{
			this->DropJunkScrollBar->SetIndex(this->DropJunkScrollBar->GetMaxIndex());
			this->DropJunkTextbox->text = to_wstring(this->DropJunkScrollBar->GetMaxIndex());
			this->DropJunkTextbox->Rendertext = to_wstring(this->DropJunkScrollBar->GetMaxIndex());
			this->DropJunkTextbox->UpdateBlinkerOffset();
		}
	}
	else
	{
		this->DropJunkScrollBar->SetIndex(0);
		this->DropJunkTextbox->UpdateBlinkerOffset();
	}

	if (this->UI_Element_DropOkay->MouseOverElement() && this->UI_Element_DropOkay->MouseClickedOnElement())
	{
		if (this->DropJunkScrollBar->GetIndex() != 0)
		{
			if (this->DropOrJunk)
			{
				SItem::SendDrop(Ptr_Inv_Game->world->connection->ClientStream, this->DropID, this->DropJunkScrollBar->GetIndex(), this->DropX, this->DropY, Ptr_Inv_Game);
			}
			else
			{
				SItem::SendJunk(Ptr_Inv_Game->world->connection->ClientStream, this->DropID, this->DropJunkScrollBar->GetIndex(), Ptr_Inv_Game);
			}
		}
	}
}
void Map_UI_Inventory::PaperdollCheckElements()
{
	for (int i = 0; i < 15; i++)
	{
		EIF_Data m_item = World::EIF_File->Get(this->paperdoll._paperdoll[i]);
		int Height = Ptr_Inv_Game->ResourceManager->GetImageInfo(23, m_item.graphic * 2, true).Height;
		int Width = Ptr_Inv_Game->ResourceManager->GetImageInfo(23, m_item.graphic * 2, true).Width;

		int xloc = this->PPdollX + PaperdollInformation[i].xoff;
		int yloc = this->PPdollY + PaperdollInformation[i].yoff;
		if (Ptr_Inv_MapUI->MouseX > xloc && Ptr_Inv_MapUI->MouseX < xloc + Width)
		{
			if (Ptr_Inv_MapUI->MouseY > yloc && Ptr_Inv_MapUI->MouseY < yloc + Height)
			{
				Ptr_Inv_MapUI->DrawHelpMessage("Information", m_item.name.c_str());
				if (Ptr_Inv_Game->MouseRightPressed && m_item.id != 0 && paperdoll.Modifiable)
				{
					int subid = 0;
					if(PaperdollInformation[i].location == EquipLocation::Armlet2 || PaperdollInformation[i].location == EquipLocation::Ring2 || PaperdollInformation[i].location == EquipLocation::Bracer2)
					{
						subid++;
					}
					SPaperdoll::SendPaperdollRemove(Ptr_Inv_Game->world->connection->ClientStream, m_item.id, subid, Ptr_Inv_Game);
				}
			}
		}
	}
}
Map_UI_Inventory::~Map_UI_Inventory()
{

}

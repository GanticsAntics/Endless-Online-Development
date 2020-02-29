#include "..\..\stdafx.h"

#include "Map_UI.h"
#include "..\..\Packet_Handler\Send\SPaperdoll.h"
#include "..\..\Packet_Handler\Send\SItem.h"
#include "Map_UI_Inventory.h"

CBitmapEx Black_Bmp;
sf::Font* ItemDescFont;
Map_UI_Inventory::Map_UI_Inventory(Map_UI* m_UIElement, Game* p_Game)
{
	this->m_MapUI = m_UIElement;
	this->m_game = p_Game;
	Black_Bmp = CBitmapEx();
	this->DropJunkScrollBar = new UI_Scrollbar(10, 10, 200, 10, 137, this->m_game->ResourceManager->GetResource(2, 29, false), this->m_game, this->m_game->ResourceManager->GetResource(2, 32, true));
	this->DropJunkScrollBar->SetPosition(130, 100);
	this->DropJunkScrollBar->SetVertical(false);
	this->DropJunkScrollBar->SetButtonsEnabled(false);
	this->DropJunkScrollBar->SetMaxIndex(100);
	//D3DXCreateFont(this->m_MapUI->m_Device, 12, 0, FW_THIN, 1, FALSE, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"), &ItemDescFont);
	this->p_PPDollTexture = this->m_game->ResourceManager->CreateTexture(2, 49, false)._Texture;
	this->p_DropJunkTexture = this->m_game->ResourceManager->CreateTexture(2, 27, false)._Texture;
	Black_Bmp.Create(1, 1);
	Black_Bmp.Clear(_RGB(0, 0, 0));
	DWORD dwBufferSize = Black_Bmp.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	LPBYTE buffer;
	buffer = (LPBYTE)malloc(dwBufferSize);
	Black_Bmp.Save(buffer);
	DropMenuY = 120;
	DropMenuX = 180;

	sf::Image resimage;
	resimage.create(1, 1, sf::Color::Black);
	this->p_BlackBoxTexture = new Resource_Manager::TextureData();
	this->p_BlackBoxTexture->_Sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	this->p_BlackBoxTexture->_Texture = std::shared_ptr<sf::Texture>(new sf::Texture());
	this->p_BlackBoxTexture->_Texture->loadFromImage(resimage);
	this->p_BlackBoxTexture->_Texture->setRepeated(true);
	this->p_BlackBoxTexture->_TextureID = 0;
	this->p_BlackBoxTexture->_height = resimage.getSize().y;
	this->p_BlackBoxTexture->_width = resimage.getSize().x;
	this->p_BlackBoxTexture->_Sprite->setTexture(*this->p_BlackBoxTexture->_Texture);


	this->UI_Element_PpdollOkay = new Button(*this->m_game->BT_Message_OK);
	this->UI_Element_PpdollOkay->SetPosition(std::pair<int, int>(421, 273));

	this->UI_Element_DropOkay = new Button(*this->m_game->BT_Message_OK);
	this->UI_Element_DropOkay->SetPosition(std::pair<int, int>(421, 273));

	this->UI_Element_DropCancel = new Button(*this->m_game->BT_CharDeleteCancel);
	this->UI_Element_DropCancel->SetPosition(std::pair<int, int>(421, 273));

	this->UI_Element_InventoryButton = new Button(this->m_game, 62, 330, 0, 0, 36, 19, false, this->m_game->ResourceManager->GetResource(2, 25, false));
	this->UI_Element_InventoryPPdoll = new Button(this->m_game, 486, 340, 38, 385, 88, 19, false, this->m_game->ResourceManager->GetResource(2, 27, false));

	this->UI_Element_InventoryDrop = new Button(this->m_game, 491, 399, 0, 15, 38, 37, true, this->m_game->ResourceManager->GetResource(2, 27, false));
	this->UI_Element_InventoryJunk = new Button(this->m_game, 531, 399, 0, 89, 38, 37, true, this->m_game->ResourceManager->GetResource(2, 27, false));
	

	sf::Vector2f Pos;
	Pos.x = 107;
	Pos.y = 309;

	sf::Vector2f Size;
	Size.x = 460;
	Size.y = 30;

	Textbox _DropJunkTextbox = Textbox(this->m_game, Pos, Size, sf::Color::Color(255, 255, 255, 200), this->m_game->MessageFont, Game::GameStage::PInGame, 0);
	_DropJunkTextbox.blinkhidden = false;
	_DropJunkTextbox.MaxLen = 5;
	_DropJunkTextbox.nonAcceptedKeyEntered = false;
	_DropJunkTextbox.acceptspace = true;
	_DropJunkTextbox.acceptsReturn = true;
	_DropJunkTextbox.SetKeyMask(Textbox::KeyType::Digit);
	this->DropJunkTextbox = this->m_game->world->RegisterTextBox(_DropJunkTextbox);

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
	int MouseX = this->m_MapUI->MouseX;
	int MouseY = this->m_MapUI->MouseY;
	
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
			
			if (!this->m_MapUI->MouseHeld)
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
	this->UI_Element_InventoryButton->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	if (this->UI_Element_InventoryButton->MouseClickedOnElement())
	{
		this->m_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Inventory, 0);
	}
	if (this->PaperdollVisible)
	{
		this->UpdatePaperdoll();
		if (this->UI_Element_PpdollOkay->MouseOverElement() && this->m_game->MousePressed)
		{
			this->paperdoll._PlayerID = -1;
			this->PaperdollVisible = false;
		}
		this->m_game->MapCursor.m_CursorType = Map_UI_Cursor::CursorType::Invisible;
	}
	if (this->IsDropMenuActive)
	{
		this->UpdateDropJunk();
		this->m_MapUI->isactive = false;
		this->m_game->world->SetFocusedTextbox(this->DropJunkTextbox);
		
		this->DropJunkTextbox->position.x = this->DropMenuX + 160;
		this->DropJunkTextbox->position.y = this->DropMenuY + 93;
		if (this->UI_Element_DropOkay->MouseOverElement() && this->m_game->MousePressed)
		{
			this->DropID = -1;
			this->DropAmount = 0;
			this->IsDropMenuActive = false;
			this->m_MapUI->isactive = true;
		}
		if (this->UI_Element_DropCancel->MouseOverElement() && this->m_game->MousePressed)
		{
			this->DropID = -1;
			this->DropAmount = 0;
			this->IsDropMenuActive = false;
			this->m_MapUI->isactive = true;
		}
	}
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Inventory):
	{
		this->UI_Element_InventoryDrop->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
		this->UI_Element_InventoryJunk->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
		this->UI_Element_InventoryPPdoll->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
		int MouseX = this->m_MapUI->MouseX;
		int MouseY = this->m_MapUI->MouseY;
		int index = 0;
		if (this->UI_Element_InventoryDrop->MouseOverElement())
		{
			if (this->childMPindex >= 0 && !this->m_MapUI->MouseHeld)
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
					SItem::SendDrop(this->m_game->world->connection->ClientStream, this->m_game->Map_UserInterface->map_inventory->childMPindex, 1, this->m_game->map->m_Players[World::WorldCharacterID]->x, this->m_game->map->m_Players[World::WorldCharacterID]->y, this->m_game);
					this->childMPindex = -1;
				}
				else if (amount > 1)
				{
					this->DisplayDropDialogue(true, amount, this->childMPindex, this->m_game->map->m_Players[World::WorldCharacterID]->x, this->m_game->map->m_Players[World::WorldCharacterID]->y);
					this->childMPindex = -1;
				}
			}
		}
		else if (this->UI_Element_InventoryJunk->MouseOverElement())
		{
			if (this->childMPindex >= 0 && !this->m_MapUI->MouseHeld)
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
					SItem::SendJunk(this->m_game->world->connection->ClientStream, this->m_game->Map_UserInterface->map_inventory->childMPindex, 1,  this->m_game);
					this->childMPindex = -1;
				}
				else if (amount > 1)
				{
					this->DisplayDropDialogue(false, amount, this->childMPindex, this->m_game->map->m_Players[World::WorldCharacterID]->x, this->m_game->map->m_Players[World::WorldCharacterID]->y);
					this->childMPindex = -1;
				}
			}
		}
		if (UI_Element_InventoryPPdoll->MouseOverElement() && this->m_game->MousePressed)
		{
			SPaperdoll::SendPaperdollRequest(this->m_game->world->connection->ClientStream, World::WorldCharacterID, this->m_game);
		}
		for each (InventoryGridCell Cell in this->InventoryGrid)
		{
			if (MouseX > 113 + (22 * Cell.X) + (Cell.X * 4) && MouseX < 113 + (22 * Cell.X) + (Cell.X * 4) + 27 && MouseY >(339) + (Cell.Y * 4) + (22 * Cell.Y) && MouseY < (339) + (Cell.Y * 4) + (22 * Cell.Y) + 27)
			{
				this->InventoryGrid[index].MouseOver = true;
				
				//this->InventoryGrid[index].MouseOver = true;
				childMOindex = Cell.ID;
				if (childMPindex == -1 && this->m_MapUI->MouseHeld && Cell.ID != -1)
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
								SPaperdoll::SendPaperdollAdd(this->m_game->world->connection->ClientStream, Cell.ID, subid, this->m_game);
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
			if (!this->m_MapUI->MouseHeld)
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

void Map_UI_Inventory::Render(float depth)
{
	this->UI_Element_InventoryButton->Draw();
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Inventory):
	{
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 44, false), 101, 331, sf::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
		this->UI_Element_InventoryDrop->Draw();
		this->UI_Element_InventoryJunk->Draw();

		int x = 529;
		int y = 370;
		RECT rct;
		rct.left = x;
		rct.right = x + 190;
		rct.top = y;
		rct.bottom = y + 50;
		std::string m_message = "Weight " + to_string(this->Weight) + "/" + to_string(this->MaxWeight);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, sf::Color(255, 255, 255, 200), 12, true, depth,1);
	
		this->UI_Element_InventoryPPdoll->Draw();
		set<int> ItemIDS;
		set<int>::iterator it;
		for each (InventoryGridCell Cell in this->InventoryGrid)
		{
			RECT SrcRect;
			SrcRect.left = 0;
			SrcRect.top = 163;
			SrcRect.bottom = SrcRect.top + 22;
			SrcRect.right = SrcRect.left + 23;
			int x = (114) + (22 * Cell.X) + (Cell.X * 4);
			int y = (340) + (4 * Cell.Y) + (Cell.Y * 22);
			sf::Vector3f* Pos = new sf::Vector3f(x, y, 0);
			sf::Vector3f* Center = new sf::Vector3f(0, 0, 0);
			sf::Color col = sf::Color::Color(255, 255, 255, 255);

			if (Cell.MouseOver)
			{
				SrcRect.top = 163 + 22;
				SrcRect.bottom = SrcRect.top + 22;
				col = sf::Color::Color(150, 255, 255, 255);
			}
			this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 27, false), Pos->x, Pos->y, sf::Color(255, 255, 255, 255), SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), depth);

			//this->m_MapUI->Sprite->Draw(this->m_game->ResourceManager->CreateTexture(2, 27, true)._Texture.get(), &SrcRect, Center, Pos, col);
			if (Cell.ID != -1 && Cell.ID != childMPindex)
			{
				for each (InventoryGridCell ChildCell in this->InventoryGrid)
				{
					if (Cell.ID == ChildCell.ID && childMOindex == Cell.ID)
					{
						col = sf::Color::Color(255, 255, 255, 255);
						SrcRect.top = 163 + 22;
						SrcRect.bottom = SrcRect.top + 22;
						this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 27, false), Pos->x, Pos->y, sf::Color(255, 255, 255, 255), SrcRect.left, SrcRect.top, SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), depth);
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
			sf::Vector3f* Pos = new sf::Vector3f(x, y, 0);
			sf::Vector3f* Center = new sf::Vector3f(0, 0, 0);
			sf::Color col = sf::Color::Color(255, 255, 255, 255);


			it = ItemIDS.find(Cell.ID);
			if (it == ItemIDS.end())
			{
				EIF_Data m_item = World::EIF_File->Get(Cell.ID);
				
				sf::Vector3f* itemPos = new sf::Vector3f(x, y, 0);
				sf::Vector3f* itemCenter = new sf::Vector3f(0, 0, 0);
				if (Cell.MousePressed)
				{
					int m_itemHeight = this->m_game->ResourceManager->GetResource(23, m_item.graphic * 2, true)->_height;
					int m_itemWidth = this->m_game->ResourceManager->GetResource(23, m_item.graphic * 2, true)->_width;

					itemPos->x = this->m_game->MouseX - m_itemWidth / 2;
					itemPos->y = this->m_game->MouseY - m_itemHeight / 2;
					this->m_game->Draw(this->m_game->ResourceManager->GetResource(23, m_item.graphic * 2, true), itemPos->x, itemPos->y, sf::Color(255, 255, 255, 150), 0, 0, -1, -1, sf::Vector2f(1, 1), 0);
				}
				else
				{
					this->m_game->Draw(this->m_game->ResourceManager->GetResource(23, m_item.graphic * 2, true), itemPos->x, itemPos->y, sf::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), 0);
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
				this->m_MapUI->DrawHelpMessage("Item", message);

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
				sf::Vector2f itemdescsize = m_game->GetFontSize(DecriptionString, 9);
				if (DecriptionString == "")
				{
					itemdescsize = m_game->GetFontSize(message, 9);
				}
				int m_itemHeight = this->m_game->ResourceManager->GetResource(23, m_item.graphic * 2, true)->_height;
				int m_itemWidth = this->m_game->ResourceManager->GetResource(23, m_item.graphic * 2, true)->_width;
				int x = (114) + (22 * Cell.X) + (Cell.X * 4) + 8 + m_itemWidth;

				RECT DrawBox = { 0,0 ,0,0 };
				DrawBox.left =  rcRect.left;
				DrawBox.top =  rcRect.top;
				DrawBox.bottom = rcRect.bottom + itemdescsize.y + 6;
				DrawBox.right = rcRect.right + 4;
				if (itemdescsize.x > rcRect.right)
				{
					DrawBox.right = itemdescsize.x + 4;
				}
				if (Cell.X > 7)
				{
					x = (114) + (22 * Cell.X) + (Cell.X * 4) + 8 - itemdescsize.x;
				}
				int y = (340) + (4 * Cell.Y) + (Cell.Y * 22) + 4;
				if (y + DrawBox.bottom + 4 > 480)
				{
					y -= ((y + DrawBox.bottom) - (480)) ;
				}

				sf::Vector3f* BoxPos = new sf::Vector3f(x, y, 0);
				sf::Vector3f* BoxCenter = new sf::Vector3f(0, 0, 0);
				sf::Color Boxcol = sf::Color::Color(255, 255, 255, 150);

				this->m_game->Draw(this->p_BlackBoxTexture, BoxPos->x, BoxPos->y, Boxcol, 0, 0, DrawBox.right, DrawBox.bottom, sf::Vector2f(1, 1), depth - 0.02f);
				
				RECT BoxRect = { 0,0 ,0,0 };
				BoxRect.left = x + 2 + DrawBox.left;
				BoxRect.top = y + 1 + DrawBox.top;
				BoxRect.bottom = y + 1 + DrawBox.bottom;
				BoxRect.right = x + 1 + DrawBox.right;
				this->m_game->DrawTextW(message, BoxRect.left, BoxRect.top, sf::Color::White, 9, false, depth - 0.03f, 0);
		
				BoxRect.left = x + 2 + DrawBox.left;
				BoxRect.top = y + 10 + DrawBox.top + rcRect.bottom;
				BoxRect.bottom = y + 1 + DrawBox.bottom + rcRect.bottom;
				BoxRect.right = x + 1 + DrawBox.right;
				this->m_game->DrawTextW(DecriptionString, BoxRect.left, BoxRect.top, sf::Color(255,255,200), 9, false, depth - 0.03f, 0);
			
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
		this->RenderPaperdoll(depth);
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
void Map_UI_Inventory::RenderPaperdoll(float depth)
{
	std::map<int, Map_Player*>::iterator _Player = this->m_game->map->m_Players.find(this->paperdoll._PlayerID);
	if (_Player != this->m_game->map->m_Players.end())
	{
		RECT BoxRect = { 0,0 ,0,0 };
		BoxRect.left = 0;
		BoxRect.top = _Player->second->Gender * 290;
		BoxRect.bottom = BoxRect.top + 290;
		BoxRect.right = 380;
		sf::Vector3f* Pos = new sf::Vector3f(PPdollX, PPdollY, 0.07);
		sf::Vector3f* Centre = new sf::Vector3f(0, 0, 0);
		
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 49, false), Pos->x, Pos->y, sf::Color::White, BoxRect.left, BoxRect.top, BoxRect.right, BoxRect.bottom, sf::Vector2f(1,1), depth);
		this->UI_Element_PpdollOkay->Draw();

		for (int i = 0; i < 15; i++)
		{
			Pos = new sf::Vector3f(PPdollX + PaperdollInformation[i].xoff, PPdollY + PaperdollInformation[i].yoff, depth);
			EIF_Data m_item = World::EIF_File->Get(this->paperdoll._paperdoll[i]);
			this->m_game->Draw(this->m_game->ResourceManager->GetResource(23, m_item.graphic * 2, true), Pos->x, Pos->y, sf::Color::White, 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
		}

		sf::Color col = sf::Color::Color(255, 255, 255, 200);
		BoxRect = { 0,0 ,0,0 };
		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 23;
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;

		this->m_game->DrawTextW(this->paperdoll._name.c_str(), BoxRect.left, BoxRect.top, col, 9, false, depth - 0.03f, 0);


		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 23 + (30 * 1);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;
		this->paperdoll._home = "Wanderer";
		this->m_game->DrawTextW(this->paperdoll._home.c_str(), BoxRect.left, BoxRect.top, col, 9, false, depth - 0.03f, 0);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 23 + (30 * 2);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;
		this->paperdoll._class = "Warrior";
		this->m_game->DrawTextW(this->paperdoll._class.c_str(), BoxRect.left, BoxRect.top, col, 9, false, depth - 0.03f, 0);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 23 + (30 * 3);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;
		this->m_game->DrawTextW(this->paperdoll._partner.c_str(), BoxRect.left, BoxRect.top, col, 9, false, depth - 0.03f, 0);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 23 + (30 * 4);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;
		this->m_game->DrawTextW(this->paperdoll._title.c_str(), BoxRect.left, BoxRect.top, col, 9, false, depth - 0.03f, 0);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 23 + (30 * 5);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;
		this->m_game->DrawTextW(this->paperdoll._job.c_str(), BoxRect.left, BoxRect.top, col, 9, false, depth - 0.03f, 0);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 23 + (30 * 6);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;
		this->m_game->DrawTextW(this->paperdoll._guild.c_str(), BoxRect.left, BoxRect.top, col, 9, false, depth - 0.03f, 0);

		BoxRect.left = this->PPdollX + 232;
		BoxRect.top = this->PPdollY + 23 + (30 * 7);
		BoxRect.bottom = BoxRect.top + 100;
		BoxRect.right = BoxRect.left + 250;
		this->m_game->DrawTextW(this->paperdoll._rank.c_str(), BoxRect.left, BoxRect.top, col, 9, false, depth - 0.03f, 0);

		delete Pos;
		delete Centre;
	}
}
int startx = 0;
int starty = 0;
void Map_UI_Inventory::UpdatePaperdoll()
{
	this->UI_Element_PpdollOkay->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	
if (this->m_MapUI->MouseX > this->PPdollX && this->m_MapUI->MouseX < this->PPdollX + 380)
	{
		if (this->m_MapUI->MouseY > this->PPdollY && this->m_MapUI->MouseY < this->PPdollY + 290)
		{
			PaperdollCheckElements();
			if (this->m_MapUI->MousePressed)
			{
				startx = PPdollX - this->m_MapUI->MouseX;
				starty = PPdollY - this->m_MapUI->MouseY;
			}
		}
	}
	if (this->m_MapUI->MouseHeld && startx != 0 && starty != 0)
	{
		this->PPdollX = this->m_MapUI->MouseX + startx;
		this->PPdollY = this->m_MapUI->MouseY + starty;
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
	this->UI_Element_PpdollOkay->SetPosition(std::pair<int, int>(PPdollX + 277, PPdollY + 254));
}
void Map_UI_Inventory::RenderDropJunk()
{
	RECT BoxRect = { 0,0 ,0,0 };
	BoxRect.left = 38;
	BoxRect.top = 0;
	BoxRect.bottom = BoxRect.top + 170;
	BoxRect.right = BoxRect.left+265;
	sf::Vector3f* Pos = new sf::Vector3f(DropMenuX, DropMenuY, 0.07);
	sf::Vector3f* Centre = new sf::Vector3f(0, 0, 0);
	//this->m_MapUI->Sprite->Draw(this->p_DropJunkTexture.get(), &BoxRect, Centre, Pos, sf::Color::Color(255, 255, 255, 255));
	this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 27, false), Pos->x, Pos->y, sf::Color::White, BoxRect.left, BoxRect.top, BoxRect.right, BoxRect.bottom, sf::Vector2f(1, 1), 0.001f);
	
	sf::Color col = sf::Color::Color(214, 230, 230, 200);
	
	EIF_Data m_item = this->m_game->world->EIF_File->Get(this->DropID);
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
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 27, false), Pos->x, Pos->y, sf::Color::White, BoxRect.left, BoxRect.top, BoxRect.right, BoxRect.bottom, sf::Vector2f(1, 1), 0.001f);

		//this->m_MapUI->Sprite->Draw(this->p_DropJunkTexture.get(), &BoxRect, Centre, Pos, sf::Color::Color(255, 255, 255, 255));
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
	//this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 27, false), Pos->x, Pos->y, sf::Color::White, BoxRect.left, BoxRect.top, BoxRect.right, BoxRect.bottom, sf::Vector2f(1, 1), 0.001f);
	this->m_game->DrawText(renderstr, BoxRect.left, BoxRect.top, col, 14, false, 0.001f);
	//this->m_game->DefaultFont->DrawTextA(this->m_MapUI->Sprite, renderstr.c_str(), -1, &BoxRect, NULL, col);
	this->UI_Element_DropCancel->Draw(0.001);
	this->UI_Element_DropOkay->Draw(0.001);
	this->DropJunkTextbox->Render(0.001);
	this->DropJunkScrollBar->Draw(0.0005f);
	delete Pos;
	delete Centre;
}
void Map_UI_Inventory::UpdateDropJunk()
{
	this->UI_Element_DropCancel->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	this->UI_Element_DropOkay->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	this->DropJunkScrollBar->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_game->MouseWheelVal, this->m_MapUI->MousePressed, this->m_MapUI->MouseHeld, this->m_MapUI->FPS);
	if (this->m_MapUI->MouseX > this->DropMenuX && this->m_MapUI->MouseX < this->DropMenuX + 265)
	{
		if (this->m_MapUI->MouseY > this->DropMenuY && this->m_MapUI->MouseY < this->DropMenuY + 170)
		{
			int DropJunkBarX = this->DropJunkScrollBar->GetPosition().first;
			int DropJunkBarY = this->DropJunkScrollBar->GetPosition().second;
			int Height = this->DropJunkScrollBar->GetBarHeight();
			if (this->m_MapUI->MouseX > DropJunkBarX && this->m_MapUI->MouseX < DropJunkBarX + Height + 16 && this->m_MapUI->MouseY > DropJunkBarY && this->m_MapUI->MouseY < DropJunkBarY + 16)
			{
				
			}
			else if (this->m_MapUI->MousePressed)
			{
				startx = DropMenuX - this->m_MapUI->MouseX;
				starty = DropMenuY - this->m_MapUI->MouseY;
			}
				
			
		}
	}
	if (this->m_MapUI->MouseHeld && startx != 0 && starty != 0)
	{
		this->DropMenuX = this->m_MapUI->MouseX + startx;
		this->DropMenuY = this->m_MapUI->MouseY + starty;
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
	this->UI_Element_DropCancel->SetPosition(std::pair<int, int>(DropMenuX + 154, DropMenuY + 126));
	this->UI_Element_DropOkay->SetPosition(std::pair<int, int>(DropMenuX + 61, DropMenuY + 126));
	this->DropJunkScrollBar->SetPosition(DropMenuX + 10, DropMenuY + 96);
	
	if (this->m_game->RAWMousePressed)
	{
		this->DropJunkTextbox->text = to_string(this->DropJunkScrollBar->GetIndex());
		this->DropJunkTextbox->Rendertext = to_string(this->DropJunkScrollBar->GetIndex());
		this->DropJunkTextbox->UpdateBlinkerOffset();
	}
	else if (this->DropJunkTextbox->text.length() > 0)
	{
		this->DropJunkScrollBar->SetIndex(std::stoi(this->DropJunkTextbox->text));
		if (this->DropJunkScrollBar->GetIndex() > this->DropJunkScrollBar->GetMaxIndex())
		{
			this->DropJunkScrollBar->SetIndex(this->DropJunkScrollBar->GetMaxIndex());
			this->DropJunkTextbox->text = to_string(this->DropJunkScrollBar->GetMaxIndex());
			this->DropJunkTextbox->Rendertext = to_string(this->DropJunkScrollBar->GetMaxIndex());
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
				SItem::SendDrop(this->m_game->world->connection->ClientStream, this->DropID, this->DropJunkScrollBar->GetIndex(), this->DropX, this->DropY, this->m_game);
			}
			else
			{
				SItem::SendJunk(this->m_game->world->connection->ClientStream, this->DropID, this->DropJunkScrollBar->GetIndex(), this->m_game);
			}
		}
	}
}
void Map_UI_Inventory::PaperdollCheckElements()
{
	for (int i = 0; i < 15; i++)
	{
		EIF_Data m_item = World::EIF_File->Get(this->paperdoll._paperdoll[i]);
		int Height = this->m_game->ResourceManager->GetResource(23, m_item.graphic * 2, true)->_height;
		int Width = this->m_game->ResourceManager->GetResource(23, m_item.graphic * 2, true)->_width;

		int xloc = this->PPdollX + PaperdollInformation[i].xoff;
		int yloc = this->PPdollY + PaperdollInformation[i].yoff;
		if (this->m_MapUI->MouseX > xloc && this->m_MapUI->MouseX < xloc + Width)
		{
			if (this->m_MapUI->MouseY > yloc && this->m_MapUI->MouseY < yloc + Height)
			{
				this->m_MapUI->DrawHelpMessage("Information", m_item.name.c_str());
				if (this->m_game->MouseRightPressed && m_item.id != 0 && paperdoll.Modifiable)
				{
					int subid = 0;
					if(PaperdollInformation[i].location == EquipLocation::Armlet2 || PaperdollInformation[i].location == EquipLocation::Ring2 || PaperdollInformation[i].location == EquipLocation::Bracer2)
					{
						subid++;
					}
					SPaperdoll::SendPaperdollRemove(this->m_game->world->connection->ClientStream, m_item.id, subid, this->m_game);
				}
			}
		}
	}
}
Map_UI_Inventory::~Map_UI_Inventory()
{

}

#pragma once
#include "..\..\Utilities\Button.h"
#include "..\..\Utilities\UI_ScrollBar.h"
#include "..\..\Utilities\Textbox.h"
class Map_UI_Inventory
{
public:

	struct InventoryGridCell
	{
	public:
		InventoryGridCell()
		{
			X = 0;
			Y = 0;
			ID = -1;
			MouseOver = false;
			MousePressed = false;
		}
		InventoryGridCell(int _X, int _Y)
		{
			X = _X;
			Y = _Y;
			ID = -1;
			MouseOver = false;
			MousePressed = false;
		}
		int X;
		int Y;
		int ID;
		bool MouseOver;
		bool MousePressed;
	};
	enum EquipLocation
	{
		Boots,
		Accessory,
		Gloves,
		Belt,
		Armor,
		Necklace,
		Hat,
		Shield,
		Weapon,
		Ring1,
		Ring2,
		Armlet1,
		Armlet2,
		Bracer1,
		Bracer2
	};
	struct PaperdollContainer
	{
		int _gender = 0;
		int _PlayerID = -1;
		bool Modifiable = false;
		std::string _name = "";
		std::string _home = "";
		std::string _class = "";
		std::string _partner = "";
		std::string _title = "";
		std::string _job = "";
		std::string _guild = "";
		std::string _rank = "";
		std::array<int, 15> _paperdoll;
		std::array<int, 15> _cosmetic_paperdoll;
	};

	PaperdollContainer paperdoll;
	std::array<int, 15> cosmetic_paperdoll;
	 InventoryGridCell InventoryGrid[56];
	/**
* One type of item in a Characters inventory
*/
	struct InventoryItem
	{
		short id;
		int amount;

		InventoryItem() = default;
		InventoryItem(short id, int amount) : id(id), amount(amount) { }
	};
	
	std::shared_ptr<IDirect3DTexture9> p_PPDollTexture;
	std::shared_ptr<IDirect3DTexture9> p_DropJunkTexture;
	Textbox* DropJunkTextbox;
	Button* UI_Element_PpdollOkay;
	Button* UI_Element_DropOkay;
	Button* UI_Element_DropCancel;
	bool PaperdollVisible = false;
	int Weight = 0;
	int MaxWeight = 0;
	int childMPindex = -1;
	int childMOindex = -1;
	int PPdollX = 145;
	int PPdollY = 20;
	LPDIRECT3DTEXTURE9 p_BlackBoxTexture;
	bool IsDropMenuActive = false;
	bool DropOrJunk = false;
	int DropMenuX = 320;
	int DropMenuY = 220;
	int DropAmount = 0;
	int DropID = -1;
	int DropX = 0;
	int DropY = 0;
	UI_Scrollbar* DropJunkScrollBar;
	Button* UI_Element_InventoryPPdoll;
	Button* UI_Element_InventoryButton;
	Button* UI_Element_InventoryJunk;
	Button* UI_Element_InventoryDrop;
	std::vector<InventoryItem> inventory;
	//Map_UI_Inventory();
	Map_UI_Inventory(void* m_MapUI, void* m_Game);
	void AddItem(InventoryItem _item) 
	{
		AddInventoryItem(_item);
	}
	void MoveItem(int _item);
	void RemoveItem(InventoryItem _item)
	{
		for (int i = 0; i < this->inventory.size(); i++)
		{
			if (inventory[i].id == _item.id)
			{
				inventory[i].amount -= _item.amount;
				if (inventory[i].amount <= 0)
				{
					inventory.erase(inventory.begin() + i);
					for (int ii = 0; ii < 56; ii++)
					{
						if (InventoryGrid[ii].ID == _item.id)
						{
							InventoryGrid[ii].ID = -1;
							InventoryGrid[ii].MouseOver = false;
							InventoryGrid[ii].MousePressed = false;
						}
					}
					this->childMPindex = -1;
				}
				return;
			}
		}
	}
	void RemoveItem(int ID, int amount)
	{
		for (int i = 0; i < this->inventory.size(); i++)
		{
			if (inventory[i].id == ID)
			{
				inventory[i].amount -= amount;
				if (inventory[i].amount <= 0)
				{
					inventory.erase(inventory.begin() + i);
					for (int ii = 0; ii < 56; ii++)
					{
						if (InventoryGrid[ii].ID == ID)
						{
							InventoryGrid[ii].ID = -1;
							InventoryGrid[ii].MouseOver = false;
							InventoryGrid[ii].MousePressed = false;
						}
					}
					this->childMPindex = -1;
				}
				return;
			}
		}
	}

	void ClearInventory() { this->inventory.clear();  int Count = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 14; x++)
		{
			Map_UI_Inventory::InventoryGridCell cell = InventoryGridCell(x, y);
			this->InventoryGrid[Count] = cell;
			Count++;
		}
	}
	};
	void DisplayDropDialogue(bool _DropOrJunk, int DropMaxamount, int ID, int X, int Y)
	{
		this->DropJunkScrollBar->SetIndex(1);
		this->DropJunkScrollBar->SetNumberOfLines(1);
		this->DropJunkTextbox->text = L"1";
		this->DropJunkTextbox->Rendertext = L"1";
		this->DropJunkScrollBar->SetMaxIndex(DropMaxamount);
		this->DropAmount = DropMaxamount;
		this->DropID = ID;
		this->DropX = X;
		this->DropY = Y;
		this->DropOrJunk = _DropOrJunk;
		this->IsDropMenuActive = true;
	}
	int ContainsItem(int ItemID)
	{
		for each (InventoryItem item in inventory)
		{
			if (item.id == ItemID)
			{
				return item.amount;
			}
		}
		return 0;
	}
	bool SetAmount(int ItemID, int Amount)
	{
		for each (InventoryItem item in inventory)
		{
			if (item.id == ItemID)
			{
				item.amount = Amount;
				return true;
			}
		}
		return false;
	}
	void PaperdollCheckElements();
	void RenderPaperdoll();
	void UpdatePaperdoll();
	void UpdateDropJunk();
	void RenderDropJunk();
	void RecalculateInventory();
	void AddInventoryItem(InventoryItem m_Item);
	void Update();
	void Render();
	~Map_UI_Inventory();
};


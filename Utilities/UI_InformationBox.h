#pragma once

class Game;
class UI_InformationBox : UI_Element
{
private:
	std::shared_ptr<IDirect3DTexture9> InfoBxBGTexture;
	std::shared_ptr<IDirect3DTexture9> InfoIcons;
	Button* Bt_Cancel;
	Button* Bt_History;
	Button* Bt_Okay;
	Button* Bt_Back;
	Button* Bt_Next;
	Button* Bt_Add;
	Button* Bt_Progress;
	UI_Scrollbar* UI_InfoScrollbar;
	Game* m_game;
	bool isdragging = false;
	bool isdragselected = false;
	int DragX = 0;
	int DragY = 0;
	int CurrentIndex = 0;
	int MaxIndex = 0;	
	int _ElementHeight = 12;
	Textbox* TB_ScrollBox;
	UI_Scrollbar* ScrollBoxScrollBar;
	enum MessageType
	{
		_Text = 0,
		_Item,
		_NPC,
		_BuyItem,
		_SellItem,
		_CraftItem,
		_BuyItemEntry,
		_SellItemEntry,
		_CraftItemEntry,
		_IngredientEntry,
		_StorageItemEntry,
		_QuestRewardEntry
	};
	struct _Hyperlink
	{
		RECT _TextPos;
		int _Goto;
	};
	struct _MessageContainer
	{
		MessageType Message_Type = MessageType::_Text;
		int sizeofentry = 1;
		bool isHighlightable = false;
		std::string Message = "";
		vector<int> Parameters;
		vector<_Hyperlink> _Hyperlinks;
	};
	MessageType PhaseType = MessageType::_Text;
	typedef vector<_MessageContainer> ContainerPhase;
	void AlignInterface();
	std::string m_Title = "";
	int ReturnLineIndexInPhase(int PhaseIndex, int Lineindex);
	void RenderScrollBox(ID3DXSprite* _Sprite);
	bool Phasechanged = false;
	bool ScrollBoxVisible = false;
	bool ShopBuyActive = false;
	int ScrollBoxX = 190;
	int ScrollBoxY = 80;
	int ScrollBoxAmount = 0;
	int ScrollBoxID = -1;
	int ScrollValueAmount = 0;
	bool AwaitingResponse = false;
	Button* UI_ScrollBoxElement_Okay;
	Button* UI_ScrollBoxElement_Cancel;
	void DrawCraftItemBox(ID3DXSprite* _Sprite, _MessageContainer _entry);
public:
	enum ScrollBoxType
	{
		_SBT_BuyItem = 0,
		_SBT_SellItem,
		_SBT_CraftItem
	};
	struct ItemEntry
	{
		int Item_ID;
		int Item_Amount;
	};
	struct CraftItemEntry
	{
		int Item_ID;
		vector<ItemEntry> Item_Requirements;
	};

	UI_InformationBox(Game* p_game);
	map<int, ContainerPhase> ContainerData;
	vector<Button*> InterfaceButtons;
	int PhaseID = 0;
	vector<int> PreviousPhraseIDs;

	void CreateMessage(std::string  Title, std::string Message, bool ShowCancel = false);
	//void CreateShop(std::string ShopTitle, vector<ItemEntry> BuyItems, vector<ItemEntry> SellItems, vector <CraftItemEntry> CraftItems);
	
	//Add a _MessageContainer to the PhaseIndex with a BuyIcon (and a parameter inside specifying to goto the item entries are stored (size of container + 1))
	void AddShopBuyItem(int ShopBuyIndex, int Item_ID, int Item_Amount, int Item_MaxAmount, int PhaseIndex = -1);
	void AddShopSellItem(int ShopSelIndex, int Item_ID, int Item_Amount, int PhaseIndex = -1);
	void AddShopCraftItem(int ShopCraftIndex, CraftItemEntry Item_Entry, int PhaseIndex = -1);
	void AddStorageItem(int ItemID, int ItemAmount, int PhaseIndex = -1);

	void ShowInformationBox(std::string title, map<int, ContainerPhase> _ContainerData, bool ShowCancel = false);
	void ShowInformationBox(std::string title, std::string Message, bool ShowCancel = false);
	void AddMessage(std::string Message);
	void DrawContainerEntry(ID3DXSprite* _Sprite, _MessageContainer _entry, int EntryIndex);
	void NewBox() 
	{ 
		ShopBuyActive = false;
		this->ContainerData = map<int, ContainerPhase>();
		this->PreviousPhraseIDs.push_back(this->PhaseID);
		this->PhaseID = 0;
		this->UI_InfoScrollbar->SetIndex(0);
		this->UI_InfoScrollbar->SetNumberOfLines(1);
		this->MaxIndex = ReturnLineIndexInPhase(this->PhaseID, this->ContainerData[this->PhaseID].size());
		this->UI_InfoScrollbar->SetMaxIndex((this->ContainerData[this->PhaseID].size() + 6));

		this->InterfaceButtons.clear();
		if (this->PhaseID == 0)
		{
			this->InterfaceButtons.push_back(this->Bt_Cancel);
			this->PreviousPhraseIDs.clear();
		}
		else
		{
			this->InterfaceButtons.push_back(this->Bt_Cancel);
			this->InterfaceButtons.push_back(this->Bt_Back);
		}
		this->Phasechanged = true;
	}

	void ChangePhase(int _PhaseID, bool Backpressed = false);
	void SetTitle(std::string _title) { this->m_Title = _title; }
	void CloseBox();
	void Update();
	void Draw(ID3DXSprite* _Sprite);
	bool CheckCraftIngredients(CraftItemEntry _item);
	ScrollBoxType _ScrollType;
	void UpdateScrollBox();
	void ShowScrollBox(ScrollBoxType boxtype, int ItemID, int Value, int MaxAmount);
	~UI_InformationBox();
};


#pragma once

class Game;
class UI_InformationBox : UI_Element
{
private:
	std::shared_ptr<IDirect3DTexture9> InfoBxBGTexture;
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
	enum MessageType
	{
		Text = 0,
		Item,
		NPC,
		BuyItem,
		SellItem,
		CraftItem
	};
	struct _Hyperlink
	{
		RECT _TextPos;
		int _Goto;
	};
	struct _MessageContainer
	{
		MessageType Message_Type = MessageType::Text;
		bool isHighlightable = false;
		std::string Message = "";
		vector<int> Parameters;
		vector<_Hyperlink> _Hyperlinks;
	};
	typedef vector<_MessageContainer> ContainerPhase;
	void AlignInterface();
	std::string m_Title = "";
public:
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
	int PhaseID;
	int PreviousPhaseID;

	void CreateMessage(std::string Title, std::string Message, bool ShowCancel = false);
	void CreateShop(std::string ShopTitle, ItemEntry BuyItems, ItemEntry SellItems, CraftItemEntry CraftItems);

	void ShowInformationBox(std::string title, map<int, ContainerPhase> _ContainerData, bool ShowCancel = false);
	void ShowInformationBox(std::string title, std::string Message, bool ShowCancel = false);
	void AddMessage(std::string Message);
	void SetTitle(std::string _title) { this->m_Title = _title; }
	void CloseBox();
	void Update();
	void Draw(ID3DXSprite* _Sprite);

	~UI_InformationBox();
};


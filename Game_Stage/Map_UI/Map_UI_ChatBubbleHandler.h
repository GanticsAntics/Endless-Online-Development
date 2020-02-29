#pragma once
class Map_UI_ChatBubbleHandler
{
	struct BubbleContainer
	{
		bool _IsNPC = false;
		int Width;
		int Height;
		int _PlayerID;
		std::string _Message;
		time_t _StartTime;
		sf::Color BG_color;
		sf::Color TextCol_color;
	};

	void RenderChatBubble(BubbleContainer _Message, int index);
private:
	Map_UI* m_MapUI;
	Game* m_game;
public:
	Resource_Manager::TextureData* ChatBox_TopLeft;
	Resource_Manager::TextureData* ChatBox_BottomLeft;
	Resource_Manager::TextureData* ChatBox_Left;
	Resource_Manager::TextureData* ChatBox_Top;
	Resource_Manager::TextureData* ChatBoxBG;
	Resource_Manager::TextureData* ChatBoxTail;
	//Map_UI_Inventory();

	std::vector<BubbleContainer> ChatBubbleList;
	Map_UI_ChatBubbleHandler(Map_UI* m_MapUI, Game* m_Game);
	void AddMapMessage(std::string Message, int PlayerID, bool IsNPC = false, sf::Color BG_color = sf::Color::Color(200,255,255,255), sf::Color TextCol_color = sf::Color::Color(200, 0, 0, 0));
	void Update();
	void Render(float depth);
	~Map_UI_ChatBubbleHandler();
};


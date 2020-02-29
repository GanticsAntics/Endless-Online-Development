#pragma once
#include <d3d9.h>
class TextTools
{
public:
	static std::vector<std::string> SnipTextToWidth(std::string szText, int m_width, int FontSize, Game* m_game);
	static std::string SnipMessageTextToWidth(std::string szText, int m_width, int Fontsize, Game* m_game);
	enum ChatIndex
	{
		Public = 0,
		Whisper1,
		Whisper2,
		Global,
		Guild,
		System,
		Announcements,
		WhoIsOnline
	};
	struct ChatContainer
	{
		int Chat_Icon = 0;
		int MessageLength = 1;
		ChatIndex ChatIndex = ChatIndex::Public;
		std::string CharacterName;
		std::vector<std::string> Message;
		sf::Color message_col = sf::Color::White;//(255,0,0,0);
	};
	static std::vector<ChatContainer>* ChatGroups[8];
	static std::string SnipChatBoxTextToWidth(std::vector<ChatContainer>* szText, int m_width, Game* m_game);
	static void AppendChat(ChatIndex m_ChatIndex, int m_width, int FontSize, int iconindex, std::string playername, std::string m_message, Game* m_game);
	static void AppendChat(ChatIndex m_ChatIndex, int m_width, int FontSize, int iconindex, std::string playername, std::string m_message, Game* m_game, sf::Color message_col);
	//static void AppendChat(ChatContainer m_message);
	TextTools();
	~TextTools();
};


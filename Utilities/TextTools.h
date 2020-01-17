#pragma once
#include <d3d9.h>
class TextTools
{
public:
	static int GetTextWidth(std::string szText, ID3DXFont* pFont);
	static std::vector<std::string> SnipTextToWidth(std::string szText, int m_width, ID3DXFont* pFont);
	static std::string SnipMessageTextToWidth(std::string szText, int m_width, ID3DXFont* pFont);
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
		D3DCOLOR message_col = D3DCOLOR_ARGB(255,0,0,0);
	};
	static std::vector<ChatContainer>* ChatGroups[8];
	static std::string SnipChatBoxTextToWidth(std::vector<ChatContainer>* szText, int m_width, ID3DXFont* pFont);
	static void AppendChat(ChatIndex m_ChatIndex, int m_width, int iconindex, std::string playername, std::string m_message, ID3DXFont* pFont);
	static void AppendChat(ChatIndex m_ChatIndex, int m_width, int iconindex, std::string playername, std::string m_message, ID3DXFont* pFont, D3DCOLOR message_col);
	//static void AppendChat(ChatContainer m_message);
	TextTools();
	~TextTools();
};


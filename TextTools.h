#pragma once
#include <d3d9.h>
class TextTools
{
public:
	static int GetTextWidth(std::string szText, ID3DXFont* pFont);
	static std::vector<std::string> SnipTextToWidth(std::string szText, int m_width, ID3DXFont* pFont);
	struct ChatContainer
	{
		int MessageLength = 1;
		int ChatIndex = 0;
		std::string CharacterName;
		std::vector<std::string> Message;
		D3DCOLOR message_col = D3DCOLOR_ARGB(255,0,0,0);
	};
	static std::vector<ChatContainer>* AllChat;
	static std::string SnipChatBoxTextToWidth(std::vector<ChatContainer>* szText, int m_width, ID3DXFont* pFont);
	static void AppendChat(int ChatIndex, int m_width, std::string playername, std::string m_message, ID3DXFont* pFont);
	static void AppendChat(int ChatIndex, int m_width, std::string playername, std::string m_message, ID3DXFont* pFont, D3DCOLOR message_col);
	//static void AppendChat(ChatContainer m_message);
	TextTools();
	~TextTools();
};


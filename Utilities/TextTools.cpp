#include "..\stdafx.h"
#include "TextTools.h"


TextTools::TextTools()
{
}

std::vector<TextTools::ChatContainer>* TextTools::ChatGroups[8] = { new std::vector<TextTools::ChatContainer>(), new std::vector<TextTools::ChatContainer>(),new std::vector<TextTools::ChatContainer>() ,new std::vector<TextTools::ChatContainer>() ,new std::vector<TextTools::ChatContainer>() ,new std::vector<TextTools::ChatContainer>() ,new std::vector<TextTools::ChatContainer>(),new std::vector<TextTools::ChatContainer>() };
std::string TextTools::SnipMessageTextToWidth(std::string szText, int width, int Fontsize, Game* m_game)
{
	std::string builder;
	int strpos = 0;
	///Generate list of words and then build a new string based on the width.

	std::string returnstr;
	std::string tempreturnstr;
	for (int i = 0; i < szText.size(); i++)
	{
		//if (pFont)
		{
			// calculate required rect
			tempreturnstr += szText[i];
			sf::Vector2f TextRect = m_game->GetFontSize(tempreturnstr, Fontsize);

			int charsremaining = -1;
			if (TextRect.x > width)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i + j < szText.size())
					{
						if (szText[i + j] == ' ')
						{
							charsremaining = j;
						}
					}
					else
					{
						break;
					}
				}
				if (charsremaining >= 0)
				{
					returnstr += tempreturnstr.substr(0, tempreturnstr.size()) + szText.substr(i + 1, charsremaining);
					returnstr += "\n";
					tempreturnstr.clear();
					i += charsremaining;
				}
				else
				{
					returnstr += tempreturnstr.substr(0, tempreturnstr.size());
					returnstr += "-\n";
					tempreturnstr.clear();
				}
			}
		}
		if (i + 1 == szText.size())
		{
			returnstr += tempreturnstr;
		}
	}
	return returnstr;
}
std::vector<std::string> TextTools::SnipTextToWidth(std::string szText, int width, int Fontsize, Game* m_game)
{
	std::string builder;
	int strpos = 0;
	std::vector<std::string> Words;
	std::vector<std::string> Sentences;
	///Generate list of words and then build a new string based on the width.
	for (int i = 0; i < szText.length(); i++)
	{
		if (szText[i] == ' ' || szText[i] == '\n')
		{
			Words.push_back(szText.substr(i - strpos, strpos + 1));
			strpos = 0;
			continue;
		}
		if (i == szText.length() - 1 && strpos > 0)
		{
			Words.push_back(szText.substr(i - strpos, strpos + 1));
			strpos = 0;
			continue;
		}
		strpos++;
	}

	std::string returnstr;
	std::string tempreturnstr;
	for (int i = 0; i < Words.size(); i++)
	{
		//if (pFont)
		{
			// calculate required rect
			tempreturnstr += Words[i];
			sf::Vector2f TextRect = m_game->GetFontSize(tempreturnstr, Fontsize);
			if (returnstr.find('\n') != std::string::npos)
			{
				Sentences.push_back(returnstr);
				returnstr.clear();
				tempreturnstr.clear();
				continue;
			}
			if (TextRect.x > width)
			{
				Sentences.push_back(returnstr);
				returnstr.clear();
				tempreturnstr.clear();
			}
			returnstr += Words[i];
		}
	}
	Sentences.push_back(returnstr);
	// return width
	return Sentences;
}
void TextTools::AppendChat(ChatIndex m_ChatIndex, int width, int FontSize, int IconIndex, std::string playername, std::string m_message, Game* m_game, sf::Color message_col)
{
	std::string builder;
	int strpos = 0;
	std::vector<std::string> Words;
	std::vector<std::string> Sentences;

	///Generate list of words and then build a new string based on the width.
	for (int i = 0; i < m_message.length(); i++)
	{
		std::string msg = m_message.substr(i - strpos, strpos + 1);
		std::string Space = playername + "  " + msg;
		sf::Vector2f TextRect = m_game->GetFontSize(Space, FontSize);
		//pFont->DrawTextA(NULL, msg.c_str(), msg.size(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
		if (m_message[i] == ' ' || m_message[i] == '\n' || TextRect.x > width)
		{
			Words.push_back(m_message.substr(i - strpos, strpos));
			strpos = 1;
			continue;
		}
		if (i == m_message.length() - 1 && strpos > 0)
		{
			Words.push_back(m_message.substr(i - strpos, strpos + 1));
			strpos = 1;
			continue;
		}
		strpos++;
	}
	
	std::string returnstr;
	std::string tempreturnstr;
	for (int i = 0; i < Words.size(); i++)
	{
		tempreturnstr += Words[i];
		std::string Space = playername + "  " + tempreturnstr;
		sf::Vector2f TextRect = m_game->GetFontSize(Space, FontSize);

		if (TextRect.x > width)
		{
			Sentences.push_back(returnstr);
			returnstr.clear();
			tempreturnstr.clear();
		}
		returnstr += Words[i];
		if (i == Words.size() - 1 && returnstr != "")
		{
			Sentences.push_back(returnstr);
			returnstr.clear();
			tempreturnstr.clear();
		}
	}

	ChatContainer newcontainer;
	newcontainer.CharacterName += playername;
	newcontainer.ChatIndex = m_ChatIndex;
	newcontainer.Message = Sentences;
	newcontainer.MessageLength = Sentences.size();
	newcontainer.message_col = message_col;
	newcontainer.Chat_Icon = IconIndex;
	TextTools::ChatGroups[m_ChatIndex]->push_back(newcontainer);
}
void TextTools::AppendChat(ChatIndex m_ChatIndex, int width, int FontSize, int IconIndex, std::string playername, std::string pm_message, Game* m_game)
{
	std::string builder;
	int strpos = 0;
	std::vector<std::string> Words;
	std::vector<std::string> Sentences;
	///Generate list of words and then build a new string based on the width.
	std::string m_message = TextTools::SnipMessageTextToWidth(pm_message, width, FontSize, m_game);
	for (int i = 0; i < m_message.size(); i++)
	{
		std::string msg = m_message.substr(i - strpos, strpos + 1);
		if (m_message[i] == ' ' || m_message[i] == '\n')
		{
			Words.push_back(msg);
			strpos = 0;
			continue;
		}
		if (i == m_message.size() - 1 && strpos > 0)
		{
			Words.push_back(msg);
			strpos = 0;
			continue;
		}
		strpos++;
	}

	std::string returnstr;
	std::string tempreturnstr;
	
	for (int i = 0; i < Words.size(); i++)
	{
		//if (pFont)
		{
			// calculate required rect
			tempreturnstr += Words[i];
			std::string Space = playername + "  " + tempreturnstr;
			sf::Vector2f TextRect = m_game->GetFontSize(Space, FontSize);
			//pFont->DrawTextA(NULL, Space.c_str(), Space.size(), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
			if (tempreturnstr.find('\n') != std::string::npos)
			{
				Sentences.push_back(tempreturnstr);
				returnstr.clear();
				tempreturnstr.clear();
				continue;
			}
			if (TextRect.x > width)
			{
				Sentences.push_back(tempreturnstr);
				returnstr.clear();
				tempreturnstr.clear();
			}
			returnstr += Words[i];
		}
	}
	Sentences.push_back(returnstr);
	ChatContainer newcontainer;
	newcontainer.CharacterName += playername;
	newcontainer.ChatIndex = m_ChatIndex;
	newcontainer.Message = Sentences;
	newcontainer.MessageLength = Sentences.size();
	newcontainer.Chat_Icon = IconIndex;
	TextTools::ChatGroups[m_ChatIndex]->push_back(newcontainer);
}
TextTools::~TextTools()
{
}

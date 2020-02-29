#include "..\stdafx.h"
#include "Handler.h"


CLIENT_F_FUNC(Talk)
{	
	game->map->ThreadLock.lock();
		switch(action)
		{		
			case PACKET_PLAYER: 
				{
	
				short ID = reader.GetShort();
				std::string Message = reader.GetEndString();
				std::string playername = game->map->m_Players[(ID)]->name;
				playername[0] = std::toupper(playername[0]);
				TextTools::AppendChat(TextTools::ChatIndex::Public, 420,10, 0 ,playername, Message, game, sf::Color::Black);
				game->Map_UserInterface->map_talk->UI_ChatScrollbars[0]->BottomLineIndex();
				sf::Color bgcol = sf::Color(255, 255, 255, 150);
				if (Message == "<3")
				{
					bgcol = sf::Color(66, 244, 66, 150);
				}
				if (Message == "Hotdog")
				{
					bgcol = sf::Color(66, 66, 244, 150);
				}
				game->Map_UserInterface->map_ChatBubbleHandler->AddMapMessage(Message, ID, false, bgcol, sf::Color(0,0,0,200));
				break;
				}
			case PACKET_MSG:
			{

				std::string playername = reader.GetBreakString();
				std::string Message = reader.GetBreakString();
				playername[0] = std::toupper(playername[0]);
				TextTools::AppendChat(TextTools::ChatIndex::Global, 380,10, 4, playername, Message, game);
				game->Map_UserInterface->map_talk->UI_ChatScrollbars[TextTools::ChatIndex::Global]->BottomLineIndex();
				break;
			}
			default:
				game->map->ThreadLock.unlock();
				return false;
		}
		game->map->ThreadLock.unlock();
		return true;
}
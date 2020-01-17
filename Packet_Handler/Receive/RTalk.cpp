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
				TextTools::AppendChat(TextTools::ChatIndex::Public, 380, 0 ,playername, Message, game->MessageFont);
				game->Map_UserInterface->map_talk->UI_ChatScrollbars[0]->BottomLineIndex();
				D3DCOLOR bgcol = D3DCOLOR_ARGB(150, 255, 255, 255);
				if (Message == "<3")
				{
					bgcol = D3DCOLOR_ARGB(150, 244, 66, 66);
				}
				if (Message == "Hotdog")
				{
					bgcol = D3DCOLOR_ARGB(150, 66, 244, 66);
				}
				game->Map_UserInterface->map_ChatBubbleHandler->AddMapMessage(Message, ID, false, bgcol, D3DCOLOR_ARGB(200,0,0,0));
				break;
				}
			case PACKET_MSG:
			{

				std::string playername = reader.GetBreakString();
				std::string Message = reader.GetBreakString();
				playername[0] = std::toupper(playername[0]);
				TextTools::AppendChat(TextTools::ChatIndex::Global, 380, 4, playername, Message, game->MessageFont);
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
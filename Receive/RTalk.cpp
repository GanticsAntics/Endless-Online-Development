#include "Handler.h"


CLIENT_F_FUNC(Talk)
{	
		switch(action)
		{		
			case PACKET_PLAYER: 
				{
	
				short ID = reader.GetShort();
				std::string Message = reader.GetEndString();
				std::string playername = game->map->m_Players[(ID)]->name;
				playername[0] = std::toupper(playername[0]);
				TextTools::AppendChat(0, 380, playername, Message, game->MessageFont);
				game->Map_UserInterface->map_talk->UI_TextScrollbar->BottomLineIndex();
				break;
				}
			default:
				return false;
		}
		return true;
}
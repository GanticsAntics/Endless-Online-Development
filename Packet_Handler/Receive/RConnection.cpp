#include "..\stdafx.h"
#include "Handler.h"
#include "..\Send\SConnection.h"

CLIENT_F_FUNC(Connection)
{	
		switch(action)
		{		
			case PACKET_PLAYER: 
				{
					unsigned short val1 = reader.GetShort();
					unsigned char val2 = reader.GetChar();
					unsigned short Val3 = (val1 - val2);
					game->world->PacketCount = Val3;
					SConnection::Ping(game->world->connection->ClientStream, (LPVOID*) game);
					break;
				}
			default:
				return false;
		}
		return true;
}
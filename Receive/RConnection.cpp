#include "Handler.h"
#include "..\Send\SConnection.h"

CLIENT_F_FUNC(Connection)
{	
		switch(action)
		{		
			case PACKET_PLAYER: 
				{
					short val1 = reader.GetShort();
					unsigned char val2 = reader.GetChar();
					unsigned char PCVal = val2 + (val1 * 7) - 13;
					
					unsigned short Val3 = (val1 - val2);
					//short valnew = val1 + val2;
					game->world->PacketCount = Val3;
					SConnection::Ping(game->world->connection->ClientStream, (LPVOID*) game);
					break;
				}
			default:
				return false;
		}
		return true;
}
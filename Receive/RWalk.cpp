#include "Handler.h"


CLIENT_F_FUNC(Walk)
{	
		switch(action)
		{		
			case PACKET_PLAYER: 
				{
					short PlayerID = reader.GetShort();
					int Direction = reader.GetChar();
					int FromX = reader.GetChar();
					int FromY = reader.GetChar();
					game->map->WalkPlayer(PlayerID, Direction, FromX, FromY);
					
					break;
				}
			default:
				return false;
		}
		return true;
}
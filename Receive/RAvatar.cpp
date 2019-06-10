#include "Handler.h"


CLIENT_F_FUNC(Avatar)
{	
		switch(action)
		{		
			case PACKET_REMOVE: 
				{
					int PlayerID = reader.GetShort();
					int Animation = reader.GetChar();

					game->map->RemovePlayer(PlayerID);
					break;
			}
			default:
				return false;
		}
		return true;
}
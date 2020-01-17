#include "..\stdafx.h"
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
			case PACKET_AGREE:
			{
				int PlayerID = reader.GetShort();
				int PPdollID = reader.GetChar();
				unsigned char sound = reader.GetChar(); // sound

				int ShoeID = reader.GetShort() - 1;
				int ArmorID = reader.GetShort() - 1;
				int HatID = reader.GetShort() - 1;
				int WeaponID = reader.GetShort() -1;
				int ShieldID = reader.GetShort() - 1;
				game->map->ChangeAvatar(PlayerID, ShoeID, HatID, WeaponID, ShieldID, ArmorID);
				break;
			}
			default:
				return false;
		}
		return true;
}
#include "..\stdafx.h"
#include "Handler.h"


CLIENT_F_FUNC(Appear)
{	
		switch(action)
		{		
			case PACKET_REPLY: 
				{
				int Type = reader.GetByte();
				reader.GetByte();
				if (Type == 1)
				{
					int Index = reader.GetChar();
					Map_NPC* new_npc = new Map_NPC();
					new_npc->Initialize((LPVOID*)game);
					new_npc->Index = Index;
					new_npc->ID = reader.GetShort();
					new_npc->x = reader.GetChar();
					new_npc->y = reader.GetChar();
					new_npc->direction = reader.GetChar();
					

					//if (game->map->FindNPCInList(Index) == -1)
					{
						game->map->AddNPC(new_npc);
					}
				}
					
					break;
				}
			default:
				return false;
		}
		return true;
}
#include "Handler.h"
#include "..\Send\SRefresh.h"

CLIENT_F_FUNC(NPC)
{	
		switch(action)
		{		
			case PACKET_REPLY: 
				{
					int FromID = reader.GetShort();
					int Direction = reader.GetChar();
					int Index = reader.GetShort();
					int Damage = reader.GetThree();
					double HpLeft = reader.GetShort(); //As a percent?
					break;
				}
			case PACKET_PLAYER:
			{
				int Index = reader.GetChar();
				if (Index == 254) ///Attacking
				{
					int Index = reader.GetChar();
					int Hp = reader.GetChar();
					int NpcDir = reader.GetChar();
					int PlayerID = reader.GetShort();
					int Damage = reader.GetThree();
					int procDirection = NpcDir;
					if (NpcDir == 1)
					{
						procDirection = 3;
					}
					if (NpcDir == 2)
					{
						procDirection = 1;
					}
					if (NpcDir == 3)
					{
						procDirection = 2;
					}
					int npcid = (Index);
					if (npcid >= 0)
					{
						game->map->m_NPCs[npcid]->direction = procDirection;
						game->map->m_NPCs[npcid]->SetStance(Map_NPC::NPC_Stance::Attacking);

					}
					
				}
				else ///Walking
				{
					//int ID = reader.GetChar();
 					int x = reader.GetChar();
					int y = reader.GetChar();
					int Dir = reader.GetChar();
					//if (game->map->FindNPCInList(ID) != -1)
					{
						game->map->WalkNPC(Index, Dir, x, y);
						//game->map->
						//Stage.Map.NPCs[ID].AnimIndex = 0;
						//Stage.Map.NPCs[ID].Walk(x, y, Dir);
					}
					//else
					{
						//SRefresh::RequestRefresh(game->world->connection->ClientStream, game);
					}
				}
				break;
								
			}
			case PACKET_SPEC:
			{
				int KillerID = reader.GetShort();
				int KillerDirection = reader.GetChar();
				int NPCIndex = reader.GetShort();

				if (reader.Remaining() > 0)
				{
					int NPCDropUID = reader.GetShort();
					int NPCDropItemID = reader.GetShort();
					int x = reader.GetChar();
					int y = reader.GetChar();
					int ItemAmount = reader.GetInt();
					int damage = reader.GetThree();
				}
				game->map->KillNPC(NPCIndex);
				/*int Index = reader.GetByte();
				if (Index != -1) ///NPC Death Drop
				{
					int PlayerID = reader.GetShort();
					int Dir = reader.GetChar();
					int NPCIndex = reader.GetShort();
					game->map->RemoveNPC(Dir);
				}
				else 
				{

				}*/

			}
			default:
				return false;
		}
		return true;
}
#include "..\stdafx.h"
#include "Handler.h"
#include "..\Send\SWarp.h"

CLIENT_F_FUNC(Warp)
{	
		switch(action)
		{		
			case PACKET_REQUEST: 
				{
					int ID = reader.GetChar();
					short MapID = reader.GetShort();
					int x = 0;
					int y = 0;
					if (ID == 1)//warp LOCAL
					{
						x = reader.GetChar();
						y = reader.GetChar();
						game->map->m_Players[World::WorldCharacterID]->x = x;
						game->map->m_Players[World::WorldCharacterID]->y = y;
					}
					else if (ID == 2)//warp to a new map
					{
						std::array<eo2_byte, 4U> MapRID;
						for (int i = 0; i < 4; i++)
						{
							MapRID[i] = reader.GetByte();
						}
						unsigned int MapFileSize = reader.GetThree();
						game->map->LoadMap(MapID);
						x = reader.GetChar();
						y = reader.GetChar();
						game->map->ThreadLock.lock();
						if (game->map->m_emf.rid != MapRID || game->map->m_emf.MapFileSize != MapFileSize)
						{
							World::DebugPrint("Requesting Map Data File. . .");
							game->map->IsVisible = false;
							Connection::FileContainer m_FileContainer;
							m_FileContainer.File_Type = Connection::FileType::Map;
							m_FileContainer.ID = MapID;
							game->world->connection->FileQueue.push_back(m_FileContainer);
							SWarp::AcceptFile(game->world->connection->ClientStream, (LPVOID*)game);
						}
						game->map->ThreadLock.unlock();
					}
					//if (ID != 2)//warp to a new map
					{
						SWarp::AcceptWarp(game->world->connection->ClientStream, MapID, x, y, (LPVOID)game);
					}
					break;
				}
			case PACKET_AGREE:
			{
				reader.GetChar();
				int MapID = reader.GetShort();
				
				int anim = reader.GetChar();
				int CharacterSize = reader.GetChar();
				reader.GetByte();
				game->map->ThreadLock.lock();
				Map_Player* MainPlayer = game->map->m_Players[World::WorldCharacterID];
				int exp = MainPlayer->exp;	
				game->map->ThreadLock.unlock();
				//game->map->LoadMap(MapID);
				
				game->map->ClearMap();
			
				for (int i = 0; i < CharacterSize; i++)
				{
					Map_Player* newplayer = new Map_Player();
					newplayer->name = reader.GetBreakString();
					newplayer->ID = reader.GetShort();
					newplayer->mapid = reader.GetShort();
					newplayer->x = reader.GetShort();
					newplayer->y = reader.GetShort();
					newplayer->direction = reader.GetChar();

					int procDirection = newplayer->direction;
					if (newplayer->direction == 1)
					{
						procDirection = 3;
					}
					if (newplayer->direction == 2)
					{
						procDirection = 1;
					}
					if (newplayer->direction == 3)
					{
						procDirection = 2;
					}
					newplayer->direction = procDirection;

					reader.GetChar(); // Unknown
					
					newplayer->guildtag = reader.GetFixedString(3);//PaddedGuildTag
					newplayer->level = reader.GetChar();
					newplayer->Gender = reader.GetChar();
					newplayer->HairStyle = reader.GetChar() - 1;
					newplayer->HairCol = reader.GetChar();
					newplayer->SkinCol = reader.GetChar();
					newplayer->maxhp = reader.GetShort();
					newplayer->hp = reader.GetShort();
					newplayer->maxtp = reader.GetShort();
					newplayer->tp = reader.GetShort();

					newplayer->ShoeID = reader.GetShort() - 1;
					reader.GetShort();
					reader.GetShort();
					reader.GetShort();
					newplayer->ArmorID = reader.GetShort() - 1;
					reader.GetShort();
					newplayer->HatID = reader.GetShort() - 1;
					newplayer->ShieldID = reader.GetShort() - 1;
					newplayer->WeaponID = reader.GetShort() - 1;

					unsigned char is_sitting = reader.GetChar();
					if (is_sitting == 1)
					{
						newplayer->SetStance(Map_Player::PlayerStance::ChairSitting);
					}
					else if (is_sitting == 2)
					{
						newplayer->SetStance(Map_Player::PlayerStance::GroundSitting);
					}
					else
					{
						newplayer->SetStance(Map_Player::PlayerStance::Standing);
					}
					unsigned char is_hideinvisible = reader.GetChar();
					reader.GetByte();

					if (newplayer->ID == World::WorldCharacterID)
					{
						MainPlayer->exp = exp;
						MainPlayer->CharacterID = World::WorldCharacterID;
						MainPlayer->guildtag = newplayer->guildtag;
						MainPlayer->mapid = newplayer->mapid;
						MainPlayer->x = newplayer->x;
						MainPlayer->y = newplayer->y;
						MainPlayer->direction = newplayer->direction;
						MainPlayer->level = newplayer->level;
						MainPlayer->Gender = newplayer->Gender;
						MainPlayer->HairStyle = newplayer->HairStyle;
						MainPlayer->HairCol = newplayer->HairCol;
						MainPlayer->SkinCol = newplayer->SkinCol;
						MainPlayer->maxhp = newplayer->maxhp;
						MainPlayer->hp = newplayer->hp;
						MainPlayer->maxtp = newplayer->maxtp;
						MainPlayer->tp = newplayer->tp;
						MainPlayer->ShoeID = newplayer->ShoeID;
						MainPlayer->ArmorID = newplayer->ArmorID;
						MainPlayer->HatID = newplayer->HatID;
						MainPlayer->ShieldID = newplayer->ShieldID;
						MainPlayer->WeaponID = newplayer->WeaponID;
						MainPlayer->SetStance(newplayer->Stance);
						//game->map->CharacterID = MainPlayer->CharacterID;
						game->map->AddPlayer(MainPlayer);
					
					}
					else
					{
						game->map->AddPlayer(newplayer);
					}
				}
				
				while (true)
				{
					int index = reader.GetChar();
					if (index == 254) { break; }
					Map_NPC* new_npc = new Map_NPC();
					new_npc->Initialize((LPVOID*)game);
					new_npc->Index = index;
					new_npc->ID = reader.GetShort();
					new_npc->x = reader.GetChar();
					new_npc->y = reader.GetChar();
					new_npc->direction = reader.GetChar();
					game->map->AddNPC(new_npc);
				}
				while (true)
				{
					int remaining = reader.Remaining();
					if (remaining <= 1)
					{
						break;
					}
					Map::Map_Item m_item;

					int ItemIndex = reader.GetShort();
					m_item.ItemID = reader.GetShort();
					m_item.x = reader.GetChar();
					m_item.y = reader.GetChar();
					m_item.amount = reader.GetThree();
					game->map->AddItem(ItemIndex, m_item);
				}
				game->map->IsVisible = true;
				break;
			}
			default:
				return false;
		}
		return true;
}
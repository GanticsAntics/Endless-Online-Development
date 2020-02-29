#include "..\stdafx.h"
#include "Handler.h"


CLIENT_F_FUNC(Refresh)
{	
		switch(action)
		{
			case PACKET_REPLY:
			{
				int numberofplayers = reader.GetChar();
				reader.Getbyte();
				game->map->ThreadLock.lock();
				Map_Player* MainPlayer = game->map->m_Players[World::WorldCharacterID];
				int exp = MainPlayer->exp;
				game->map->ThreadLock.unlock();
				std::vector<int> preserveIDList;
				//				game->map->ClearMap();
				for (int i = 0; i < numberofplayers; i++)
				{
					Map_Player* newplayer = new Map_Player();
					newplayer->Initialize(game);
					newplayer->name = reader.GetBreakString();
					newplayer->ID = reader.GetShort();
					preserveIDList.push_back(newplayer->ID);
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
					reader.Getbyte();

					bool playerfound = false;
					for (auto p : game->map->m_Players)
					{
						if (newplayer->ID == p.first)
						{
							playerfound = true;
							p.second->exp = exp;
							p.second->guildtag = newplayer->guildtag;
							p.second->mapid = newplayer->mapid;
							p.second->x = newplayer->x;
							p.second->y = newplayer->y;
							p.second->direction = newplayer->direction;
							p.second->level = newplayer->level;
							p.second->Gender = newplayer->Gender;
							p.second->HairStyle = newplayer->HairStyle;
							p.second->HairCol = newplayer->HairCol;
							p.second->SkinCol = newplayer->SkinCol;
							p.second->maxhp = newplayer->maxhp;
							p.second->hp = newplayer->hp;
							p.second->maxtp = newplayer->maxtp;
							p.second->tp = newplayer->tp;
							p.second->ShoeID = newplayer->ShoeID;
							p.second->ArmorID = newplayer->ArmorID;
							p.second->HatID = newplayer->HatID;
							p.second->ShieldID = newplayer->ShieldID;
							p.second->WeaponID = newplayer->WeaponID;
							p.second->SetStance(newplayer->Stance);
							p.second->UpdateAppearence();
							delete newplayer;
						}
					}
					if (!playerfound)
					{
						game->map->AddPlayer(newplayer);
					}
				}

				for (auto p : game->map->m_Players)
				{
					bool keepplayer = false;
					for (int i : preserveIDList)
					{
						if (p.first == i)
						{
							keepplayer = true;
						}
					}
					if (!keepplayer)
					{
						game->map->RemovePlayer(p.first);
					}
				}

				while(true)
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
			
				break;
			}
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
#include "..\stdafx.h"
#include "Handler.h"
#include "..\Send\SWelcome.h"

CLIENT_F_FUNC(Welcome)
{
		switch(action)
		{
			case PACKET_REPLY: 
				{
					int response = reader.GetShort();
					switch (response) 
					{
						case (1):
						{
							int PlayerID = reader.GetShort();
							int CharacterID = reader.GetInt();
							int MapID = reader.GetShort();
							World::WorldCharacterID = PlayerID;
							game->map->LoadMap(MapID);
							std::array<eo2_byte, 4U> MapRID;
							for (int i = 0; i < 4; i++)
							{
								MapRID[i] = reader.Getbyte();
							}
							unsigned int MapFileSize = reader.GetThree();
							if (game->map->m_emf.rid != MapRID || game->map->m_emf.MapFileSize != MapFileSize)
							{
								World::DebugPrint("Requesting Map Data File. . .");
								game->map->IsVisible = false;
								Connection::FileContainer m_FileContainer;
								m_FileContainer.File_Type = Connection::FileType::Map;
								m_FileContainer.ID = MapID;
								game->world->connection->FileQueue.push_back(m_FileContainer);
								SWelcome::RequestFile(game->world->connection->ClientStream, 1, (LPVOID*)game);
							}
							//EMF_File::

							std::array<eo2_byte, 4U> ItemRID;
							for (int i = 0; i < 4; i++)
							{
								ItemRID[i] = reader.Getbyte();
							}
							std::array<eo2_byte, 2U> ItemFileLen;
							for (int i = 0; i < 2; i++)
							{
								ItemFileLen[i] = reader.Getbyte();
							}
							if (game->EIF_File->rid != ItemRID || game->EIF_File->len != ItemFileLen)
							{
								World::DebugPrint("Requesting Item Data File. . .");
								Connection::FileContainer m_FileContainer;
								m_FileContainer.File_Type = Connection::FileType::EIF;
								m_FileContainer.ID = 1;
								game->world->connection->FileQueue.push_back(m_FileContainer);
								SWelcome::RequestFile(game->world->connection->ClientStream, 2, (LPVOID*)game);
							}

							std::array<eo2_byte, 4U> NPCRID;
							for (int i = 0; i < 4; i++)
							{
								NPCRID[i] = reader.Getbyte();
							}
							std::array<eo2_byte, 2U> NPCFileLen;
							for (int i = 0; i < 2; i++)
							{
								NPCFileLen[i] = reader.Getbyte();
							}
							if (game->ENF_File->rid != NPCRID || game->ENF_File->len != NPCFileLen)
							{
								World::DebugPrint("Requesting NPC Data File. . .");
								Connection::FileContainer m_FileContainer;
								m_FileContainer.File_Type = Connection::FileType::ENF;
								m_FileContainer.ID = 1;
								game->world->connection->FileQueue.push_back(m_FileContainer);
								SWelcome::RequestFile(game->world->connection->ClientStream, 3, (LPVOID*)game);
							}

							std::array<eo2_byte, 4U> SpellRID;
							for (int i = 0; i < 4; i++)
							{
								SpellRID[i] = reader.Getbyte();
							}
							std::array<eo2_byte, 2U> SpellFileLen;
							for (int i = 0; i < 2; i++)
							{
								SpellFileLen[i] = reader.Getbyte();
							}
							if (game->ESF_File->rid != SpellRID || game->ESF_File->len != SpellFileLen)
							{
								World::DebugPrint("Requesting Spell Data File. . .");
								Connection::FileContainer m_FileContainer;
								m_FileContainer.File_Type = Connection::FileType::ESF;
								m_FileContainer.ID = 1;
								game->world->connection->FileQueue.push_back(m_FileContainer);
								SWelcome::RequestFile(game->world->connection->ClientStream, 4, (LPVOID*)game);
							}

							std::array<eo2_byte, 4U> ClassRID;
							for (int i = 0; i < 4; i++)
							{
								ClassRID[i] = reader.Getbyte();
							}
							std::array<eo2_byte, 2U> ClassFileLen;
							for (int i = 0; i < 2; i++)
							{
								ClassFileLen[i] = reader.Getbyte();
							}
							if (game->ECF_File->rid != ClassRID || game->ECF_File->len != ClassFileLen)
							{
								World::DebugPrint("Requesting Class Data File. . .");
								Connection::FileContainer m_FileContainer;
								m_FileContainer.File_Type = Connection::FileType::ECF;
								m_FileContainer.ID = 1;
								game->world->connection->FileQueue.push_back(m_FileContainer);
								SWelcome::RequestFile(game->world->connection->ClientStream, 5, (LPVOID*)game);
							}
							
							game->map->ClearMap();
		
							Map_Player* MainPlayer = new Map_Player();
							MainPlayer->Initialize(game);
							MainPlayer->ID = World::WorldCharacterID;
							MainPlayer->name = reader.GetBreakString();
							MainPlayer->title = reader.GetBreakString();

							std::string GuildName = reader.GetBreakString();
							std::string GuildRank = reader.GetBreakString();

							MainPlayer->clas = reader.GetChar();

							std::string CharacterPaddedGuildTag = reader.GetFixedString(3);

							unsigned char CharacterStatus = reader.GetChar();

							MainPlayer->level = reader.GetChar();
							MainPlayer->exp = reader.GetInt();
							MainPlayer->usage = reader.GetInt();

							MainPlayer->guildname = GuildName;
							MainPlayer->guildrank = GuildRank;
							MainPlayer->guildtag = CharacterPaddedGuildTag;
							MainPlayer->hp = reader.GetShort();
							MainPlayer->maxhp = reader.GetShort();
							MainPlayer->tp = reader.GetShort();
							MainPlayer->maxtp = reader.GetShort();
							MainPlayer->maxsp = reader.GetShort();
							MainPlayer->statpoints = reader.GetShort();
							MainPlayer->skillpoints = reader.GetShort();
							MainPlayer->karma = reader.GetShort();
							MainPlayer->mindam = reader.GetShort();
							MainPlayer->maxdam = reader.GetShort();
							MainPlayer->accuracy = reader.GetShort();
							MainPlayer->evade = reader.GetShort();
							MainPlayer->armor = reader.GetShort();

							MainPlayer->str = reader.GetShort();
							MainPlayer->wis = reader.GetShort();
							MainPlayer->intl = reader.GetShort();
							MainPlayer->agi = reader.GetShort();
							MainPlayer->con = reader.GetShort();
							MainPlayer->cha = reader.GetShort();


							game->Map_UserInterface->map_inventory->paperdoll.Modifiable = true;
							game->Map_UserInterface->map_inventory->paperdoll._name = MainPlayer->name;
							game->Map_UserInterface->map_inventory->paperdoll._name[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._name[0]);
							game->Map_UserInterface->map_inventory->paperdoll._home = MainPlayer->home;
							game->Map_UserInterface->map_inventory->paperdoll._home[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._home[0]);
							game->Map_UserInterface->map_inventory->paperdoll._class = MainPlayer->clas;
							game->Map_UserInterface->map_inventory->paperdoll._class[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._class[0]);
							game->Map_UserInterface->map_inventory->paperdoll._partner = MainPlayer->partner;
							game->Map_UserInterface->map_inventory->paperdoll._partner[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._partner[0]);
							game->Map_UserInterface->map_inventory->paperdoll._title = MainPlayer->title;
							game->Map_UserInterface->map_inventory->paperdoll._title[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._title[0]);
							game->Map_UserInterface->map_inventory->paperdoll._job = "Unemployed";
							game->Map_UserInterface->map_inventory->paperdoll._job[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._job[0]);
							game->Map_UserInterface->map_inventory->paperdoll._guild = "GM";
							game->Map_UserInterface->map_inventory->paperdoll._guild[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._guild[0]);
							game->Map_UserInterface->map_inventory->paperdoll._rank = "Hotdog";
							game->Map_UserInterface->map_inventory->paperdoll._rank[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._rank[0]);
							for (int i = 0; i < 15; i++)
							{
								game->Map_UserInterface->map_inventory->paperdoll._paperdoll[i] = reader.GetShort();
							}

							unsigned char CharGuildRank = reader.GetChar();

							int JailMapID = reader.GetShort();
							int Unknown1 = reader.GetShort();
							unsigned char Unknown2 = reader.GetChar();
							unsigned char Unknown3 = reader.GetChar();
							short LightGuardChatFlood = reader.GetShort();
							short GuardianChatFlood = reader.GetShort();
							short GMChatFlood = reader.GetShort();
							short Unknown4 = reader.GetShort();

							short PlayerUsage = reader.GetShort();
							reader.Getbyte();
							
							game->map->AddPlayer(MainPlayer);
							SWelcome::LoginWelcome(game->world->connection->ClientStream, MainPlayer->CharacterID, (LPVOID*)game);
							break;
						}
						case (2):
						{
						
							reader.Getbyte(); //Unknown
							std::string BuildString;
							for (int i = 0; i < 9; i++)
							{
								BuildString += reader.GetBreakString() + "\n\n";
							}
							game->Map_UserInterface->map_news->UI_TextScrollbar->SetInputString(BuildString);
							int weight = reader.GetChar();
							int maxweight = reader.GetChar();
							game->Map_UserInterface->map_inventory->ClearInventory();
							Map_UI_Inventory::InventoryItem newitem;
							newitem.id = 1;
							newitem.amount = 0;
							game->Map_UserInterface->map_inventory->AddItem(newitem);
							while (true)
							{
								int index = reader.Getbyte();
								if (index == 255) { break; }
								Map_UI_Inventory::InventoryItem newitem;
								int Index2 = reader.Getbyte();
								newitem.id = PacketProcessor::Number(index, Index2);
								newitem.amount = reader.GetInt();
								game->Map_UserInterface->map_inventory->AddItem(newitem);
							}
		
							std::string character_spells = reader.GetBreakString();
							for (int i = 0; i < character_spells.length() / 4; i++)
							{
								int pos = i * 4;
								short SpellID = PacketProcessor::Number(character_spells[pos], character_spells[pos + 1]);
								short level = PacketProcessor::Number(character_spells[pos + 2], character_spells[pos + 3]);
							}
							int numberofplayers = reader.GetChar();
							reader.Getbyte();
							for (int i = 0; i < numberofplayers; i++)
							{
								Map_Player* newplayer = new Map_Player();
								newplayer->Initialize(game);
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
								std::map<int, Map_Player*>::iterator _Player = game->map->m_Players.find(World::WorldCharacterID);
								if (newplayer->name == _Player->second->name)
								{
									game->Map_UserInterface->map_inventory->Weight = weight;
									game->Map_UserInterface->map_inventory->MaxWeight = maxweight;
									_Player->second->guildtag = newplayer->guildtag;
									
									_Player->second->weight = weight;
									_Player->second->maxweight = maxweight;
									_Player->second->CharacterID = newplayer->ID;
									_Player->second->mapid = newplayer->mapid;
									_Player->second->x = newplayer->x;
									_Player->second->y = newplayer->y;
									_Player->second->direction = newplayer->direction;
									_Player->second->level = newplayer->level;
									_Player->second->Gender = newplayer->Gender;
									_Player->second->HairStyle = newplayer->HairStyle;
									_Player->second->HairCol = newplayer->HairCol;
									_Player->second->SkinCol = newplayer->SkinCol;
									_Player->second->maxhp = newplayer->maxhp;
									_Player->second->hp = newplayer->hp;
									_Player->second->maxtp = newplayer->maxtp;
									_Player->second->tp = newplayer->tp;
									_Player->second->ShoeID = newplayer->ShoeID;
									_Player->second->ArmorID = newplayer->ArmorID;
									_Player->second->HatID = newplayer->HatID;
									_Player->second->ShieldID = newplayer->ShieldID;
									_Player->second->WeaponID = newplayer->WeaponID;
									_Player->second->SetStance(newplayer->Stance);
									//game->map->ThreadLock.lock();
									_Player->second->UpdateAppearence();
									//game->map->ThreadLock.unlock();
									//World::WorldCharacterID = MainPlayer->CharacterID;
								}
								else
								{
									game->map->AddPlayer(newplayer);
									//newplayer->UpdateAppearence();
								}
								reader.Getbyte();
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
							int counter = 0;
							int remaining = reader.Remaining();
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
								counter++;
							}
							counter++;
							game->SetStage(Game::GameStage::PInGame);
							game->Map_UserInterface->isactive = true;
							game->map->IsVisible = true;
							break;
						}
					}
				}
			default:
					return false;
		}	
		return true;
}
#include "Handler.h"


CLIENT_F_FUNC(Paperdoll)
{	
		switch(action)
		{		
			case PACKET_REPLY: 
			{

				std::string _name = reader.GetBreakString();
				std::string _home = reader.GetBreakString();
				std::string _partner = reader.GetBreakString();
				std::string _title = reader.GetBreakString();
				std::string _guilderStr = reader.GetBreakString();
				std::string _guildrank = reader.GetBreakString();
				int _PlayerID = reader.GetShort();
				int _class = reader.GetChar();
				int _gender = reader.GetChar();
				reader.GetChar();

				game->Map_UserInterface->map_inventory->paperdoll.Modifiable = true;
				game->Map_UserInterface->map_inventory->paperdoll._PlayerID = _PlayerID;
				game->Map_UserInterface->map_inventory->paperdoll._gender = _gender;
				game->Map_UserInterface->map_inventory->paperdoll._name = _name;
				game->Map_UserInterface->map_inventory->paperdoll._name[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._name[0]);
				game->Map_UserInterface->map_inventory->paperdoll._home = _home;
				game->Map_UserInterface->map_inventory->paperdoll._home[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._home[0]);
				game->Map_UserInterface->map_inventory->paperdoll._class = "";
				game->Map_UserInterface->map_inventory->paperdoll._class[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._class[0]);
				game->Map_UserInterface->map_inventory->paperdoll._partner = _partner;
				game->Map_UserInterface->map_inventory->paperdoll._partner[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._partner[0]);
				game->Map_UserInterface->map_inventory->paperdoll._title = _title;
				game->Map_UserInterface->map_inventory->paperdoll._title[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._title[0]);
				game->Map_UserInterface->map_inventory->paperdoll._job = "";
				game->Map_UserInterface->map_inventory->paperdoll._job[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._job[0]);
				game->Map_UserInterface->map_inventory->paperdoll._guild = _guilderStr;
				game->Map_UserInterface->map_inventory->paperdoll._guild[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._guild[0]);
				game->Map_UserInterface->map_inventory->paperdoll._rank = _guildrank;
				game->Map_UserInterface->map_inventory->paperdoll._rank[0] = toupper(game->Map_UserInterface->map_inventory->paperdoll._rank[0]);
				for (int i = 0; i < 15; i++)
				{
					game->Map_UserInterface->map_inventory->paperdoll._paperdoll[i] = reader.GetShort();
				}

				game->Map_UserInterface->map_inventory->PaperdollVisible = true;


				break;
			}
			case PACKET_REMOVE:
			{

				int PlayerID = reader.GetShort();
				int PPdollID = reader.GetChar();
				unsigned char sound = reader.GetChar(); // sound

				int ShoeID = reader.GetShort() - 1;
				int ArmorID = reader.GetShort() - 1;
				int HatID =  reader.GetShort() - 1;
				int WeaponID = reader.GetShort() - 1;
				int ShieldID = reader.GetShort() - 1;

				int ItemID = reader.GetShort();
				int ItemSubLoc = reader.GetChar();

				int maxhp = reader.GetShort();
				int maxtp = reader.GetShort();
				int str = reader.GetShort();
				int intl = reader.GetShort();
				int wis = reader.GetShort();
				int agi = reader.GetShort();
				int con = reader.GetShort();
				int cha = reader.GetShort();
				int mindam = reader.GetShort();
				int maxdam = reader.GetShort();
				int accuracy = reader.GetShort();
				int evade = reader.GetShort();
				int armor = reader.GetShort();

				if (PlayerID == World::WorldCharacterID)
				{
					int pos = 0;
					for (int i = 0; i < 15; i++)
					{
						if (game->Map_UserInterface->map_inventory->paperdoll._paperdoll[i] == ItemID)
						{
							pos = i;
							if (ItemSubLoc > 0)
							{
								continue;
							}
							else
							{
								break;
							}
						}
					}
					game->Map_UserInterface->map_inventory->paperdoll._paperdoll[pos] = 0;
					Map_UI_Inventory::InventoryItem item;
					item.amount = 1;
					item.id = ItemID;
					game->Map_UserInterface->map_inventory->AddItem(item);
					game->map->ChangeAvatar(PlayerID, ShoeID, HatID, WeaponID, ShieldID, ArmorID);
				}


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
				int WeaponID = reader.GetShort() - 1;
				int ShieldID = reader.GetShort() - 1;

				int ItemID = reader.GetShort();
				int ItemSubLoc = reader.GetChar();

				int maxhp = reader.GetShort();
				int maxtp = reader.GetShort();
				int str = reader.GetShort();
				int intl = reader.GetShort();
				int wis = reader.GetShort();
				int agi = reader.GetShort();
				int con = reader.GetShort();
				int cha = reader.GetShort();
				int mindam = reader.GetShort();
				int maxdam = reader.GetShort();
				int accuracy = reader.GetShort();
				int evade = reader.GetShort();
				int armor = reader.GetShort();

				if (PlayerID == World::WorldCharacterID)
				{
					int pos = 0;
					EIF_Data m_item = World::EIF_File->Get(ItemID);
					int itemloc = 0;
					switch (m_item.type)
					{
					case(EIF::Type::Boots):
					{
						itemloc = 0;
						break;
					}
					case(EIF::Type::Accessory):
					{
						itemloc = 1;
						break;
					}
					case(EIF::Type::Gloves):
					{
						itemloc = 2;
						break;
					}
					case(EIF::Type::Belt):
					{
						itemloc = 3;
						break;
					}
					case(EIF::Type::Armor):
					{
						itemloc = 4;
						break;
					}
					case(EIF::Type::Necklace):
					{
						itemloc = 5;
						break;
					}
					case(EIF::Type::Hat):
					{
						itemloc = 6;
						break;
					}
					case(EIF::Type::Shield):
					{
						itemloc = 7;
						break;
					}
					case(EIF::Type::Weapon):
					{
						itemloc = 8;
						break;
					}
					case(EIF::Type::Ring):
					{
						itemloc = 9;
						break;
					}
					case(EIF::Type::Armlet):
					{
						itemloc = 11;
						break;
					}
					case(EIF::Type::Bracer):
					{
						itemloc = 13;
						break;
					}
					}
					int subid = 0;
					for (int i = 0; i < 15; i++)
					{
						if (i > itemloc) { break; }
						if (game->Map_UserInterface->map_inventory->paperdoll._paperdoll[i] == ItemID) { subid++; }
					}
					game->Map_UserInterface->map_inventory->paperdoll._paperdoll[itemloc + subid] = ItemID;
					Map_UI_Inventory::InventoryItem item;
					item.amount = 1;
					item.id = ItemID;

					game->Map_UserInterface->map_inventory->RemoveItem(item);
					game->map->ChangeAvatar(PlayerID, ShoeID, HatID, WeaponID, ShieldID, ArmorID);
				}
				break;
			}
			default:
				return false;
		}
		return true;
}
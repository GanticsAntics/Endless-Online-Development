#include "..\stdafx.h"
#include "Handler.h"


CLIENT_F_FUNC(Shop)
{	
		switch(action)
		{		
			case PACKET_OPEN: 
				{
					int ID = reader.GetShort();
					std::string ShopTitle = reader.GetBreakString();
					//game
					std::string ShopBuyItems = reader.GetBreakString();
					game->world->W_UI_Infobox->NewBox();
					game->world->W_UI_Infobox->CreateMessage(ShopTitle, "Welcome to my shop! :3", true);
					game->world->W_UI_Infobox->SetLocation(70, 20);
					bool buytabfilled = false;
					vector<UI_InformationBox::ItemEntry> sellitementries;
					for (int i = 0; i < ShopBuyItems.length() / 9; i++)
					{
						int pos = i * 9;
						short ItemID = PacketProcessor::Number(ShopBuyItems[pos], ShopBuyItems[pos + 1]);
						int BuyAmount = PacketProcessor::Number(ShopBuyItems[pos + 2], ShopBuyItems[pos + 3], ShopBuyItems[pos + 4]);
						int SellAmount = PacketProcessor::Number(ShopBuyItems[pos + 5], ShopBuyItems[pos + 6], ShopBuyItems[pos + 7]);
						char MaxBuyAmount = PacketProcessor::Number(ShopBuyItems[pos + 8]);
						if (BuyAmount > 0)
						{
							game->world->W_UI_Infobox->AddShopBuyItem(1, ItemID, BuyAmount, MaxBuyAmount, 0);
							buytabfilled = true;
						}
						if (SellAmount > 0)
						{
							UI_InformationBox::ItemEntry newent;
							newent.Item_ID = ItemID;
							newent.Item_Amount = SellAmount;
							sellitementries.push_back(newent);
						}
					}
					int addon = 0;
					for each (UI_InformationBox::ItemEntry entry in sellitementries)
					{
						if (game->Map_UserInterface->map_inventory->ContainsItem(entry.Item_ID) > 0)
						{
							game->world->W_UI_Infobox->AddShopSellItem(2, entry.Item_ID, entry.Item_Amount, 0);
							addon = 1;
						}
					}

					std::string ShopCraftItems = reader.GetBreakString();

					for (int i = 0; i < ShopCraftItems.length() / 14; i++)
					{
						int pos = i * 14;
						UI_InformationBox::CraftItemEntry newentry;
						short ItemID = PacketProcessor::Number(ShopCraftItems[pos], ShopCraftItems[pos + 1]);
						newentry.Item_ID = ItemID;
						for (int j = 0; j < 4; j++)
						{
							int pos2 = j * 3;
							short IngredientID = PacketProcessor::Number(ShopCraftItems[2 + pos + pos2], ShopCraftItems[2 + pos + pos2 + 1]);
							unsigned char IngredientAmount = PacketProcessor::Number(ShopCraftItems[2 + pos + pos2 + 2]);
							if (IngredientID == 0)
							{
								break;
							}
							UI_InformationBox::ItemEntry newing;
							newing.Item_ID = IngredientID;
							newing.Item_Amount = IngredientAmount;
							newentry.Item_Requirements.push_back(newing);
						}
						game->world->W_UI_Infobox->AddShopCraftItem(2 + addon, newentry, 0);
					}

					break;
				}
			case PACKET_BUY:
			{
				int goldamount = reader.GetInt();
				int ItemID = reader.GetShort();
				int Amount = reader.GetInt();
				unsigned char weight = reader.GetChar();
				unsigned char Maxweight = reader.GetChar();
				Map_UI_Inventory::InventoryItem invitem;
				invitem.id = ItemID;
				invitem.amount = Amount;

				Map_UI_Inventory::InventoryItem remitem;
				remitem.amount = game->Map_UserInterface->map_inventory->ContainsItem(1) - goldamount;
				remitem.id = 1;
				
				game->Map_UserInterface->map_inventory->RemoveItem(remitem);
				game->Map_UserInterface->map_inventory->AddInventoryItem(invitem);
				game->Map_UserInterface->map_inventory->Weight = weight;
				game->Map_UserInterface->map_inventory->MaxWeight = Maxweight;
				game->Map_UserInterface->DrawHelpMessage("Notification", "You purchased " + std::to_string(invitem.amount) + "x " + World::EIF_File->Get(ItemID).name);

				break;
			}
			case PACKET_SELL:
			{
				//Current Item amount, Current ID
				int itemamount = reader.GetInt();
				int ItemID = reader.GetShort();
				//Current Gold
				int goldamount = reader.GetInt();
				unsigned char weight = reader.GetChar();
				unsigned char Maxweight = reader.GetChar();

				Map_UI_Inventory::InventoryItem golditem;
				golditem.id = 1;
				golditem.amount = goldamount - game->Map_UserInterface->map_inventory->ContainsItem(1);
				game->Map_UserInterface->map_inventory->AddInventoryItem(golditem);

				int soldamount = (game->Map_UserInterface->map_inventory->ContainsItem(ItemID) - itemamount);
				Map_UI_Inventory::InventoryItem sinvitem;
				sinvitem.id = ItemID;
				sinvitem.amount = itemamount;
				game->Map_UserInterface->map_inventory->RemoveItem(ItemID, game->Map_UserInterface->map_inventory->ContainsItem(ItemID));
				if (itemamount > 0)
				{
					game->Map_UserInterface->map_inventory->AddInventoryItem(sinvitem);
				}


				game->Map_UserInterface->map_inventory->Weight = weight;
				game->Map_UserInterface->map_inventory->MaxWeight = Maxweight;
				game->Map_UserInterface->DrawHelpMessage("Notification", "You sold " + std::to_string(soldamount) + "x " + World::EIF_File->Get(ItemID).name);
				
				break;
			}
			case PACKET_CREATE:
			{
				//Current Item amount, Current ID
				short ItemID = reader.GetShort();
				unsigned char weight = reader.GetChar();
				unsigned char Maxweight = reader.GetChar();

				vector<UI_InformationBox::ItemEntry> ingredientlist;
				std::string IngredientAmounts = reader.GetEndString();
				for (int i = 0; i < IngredientAmounts.length() / 6; i++)
				{
					int pos = i * 6;
					short iItemID = PacketProcessor::Number(IngredientAmounts[pos], IngredientAmounts[pos + 1]);
					int AmountLeft = PacketProcessor::Number(IngredientAmounts[pos + 2], IngredientAmounts[pos + 3], IngredientAmounts[pos + 4], IngredientAmounts[pos + 5]);
					if (iItemID > 0)
					{
						Map_UI_Inventory::InventoryItem sinvitem;
						sinvitem.id = iItemID;
						sinvitem.amount = AmountLeft;
						game->Map_UserInterface->map_inventory->RemoveItem(iItemID, game->Map_UserInterface->map_inventory->ContainsItem(iItemID));
						if (AmountLeft > 0)
						{
							game->Map_UserInterface->map_inventory->AddInventoryItem(sinvitem);
						}
					}
					else
					{
						break;
					}
				}
				Map_UI_Inventory::InventoryItem additem;
				additem.amount = 1;
				additem.id = ItemID;
				game->Map_UserInterface->map_inventory->AddInventoryItem(additem);
				game->Map_UserInterface->map_inventory->Weight = weight;
				game->Map_UserInterface->map_inventory->MaxWeight = Maxweight;
				game->Map_UserInterface->DrawHelpMessage("Notification", "You crafted 1 " + World::EIF_File->Get(ItemID).name);

				break;
			}
			default:
				return false;
		}
		return true;
}
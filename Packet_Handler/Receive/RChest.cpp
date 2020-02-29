#include "..\stdafx.h"
#include "Handler.h"

std::string chestmsg = "Drag items over to store, right click to retrieve.";
CLIENT_F_FUNC(Chest)
{
	switch (action)
	{
	case PACKET_OPEN:
	{
		World::ChestX = reader.GetChar();
		World::ChestY = reader.GetChar();
		int NumberOfItems = reader.Remaining() / 5;
		game->world->W_UI_Infobox->NewBox();
		game->world->W_UI_Infobox->CreateMessage("Chest", chestmsg, true);
		game->world->W_UI_Infobox->SetLocation(150, 20);
		for (int i = 0; i < NumberOfItems; i++)
		{
			unsigned short ItemID = reader.GetShort();
			int Amount = reader.GetThree();
			game->world->W_UI_Infobox->AddStorageItem(ItemID, Amount,0);
		}
		break;
	}
	case PACKET_REPLY:
	{
		int id = reader.GetShort();
		int amount = reader.GetInt();
		int weight = reader.GetChar();
		int maxweight = reader.GetChar();
		game->Map_UserInterface->map_inventory->SetItem(id, amount);
		game->map->m_Players[World::WorldCharacterID]->weight = weight;
		game->map->m_Players[World::WorldCharacterID]->maxweight = maxweight;

		EIF_Data m_item = World::EIF_File->Get(id);
		game->Map_UserInterface->DrawHelpMessage("Notification", "You dropped " + std::to_string(amount) + "x " + m_item.name);


		int NumberOfItems = reader.Remaining() / 5;
		game->world->W_UI_Infobox->NewBox();
		game->world->W_UI_Infobox->CreateMessage("Chest", chestmsg, true);
		for (int i = 0; i < NumberOfItems; i++)
		{
			unsigned short ItemID = reader.GetShort();
			int Amount = reader.GetThree();
			game->world->W_UI_Infobox->AddStorageItem(ItemID, Amount, 0);
		}
		break;
	}

	case PACKET_GET:
	{
		Map_UI_Inventory::InventoryItem newitem;
		newitem.id = reader.GetShort();
		newitem.amount = reader.GetThree();
		int weight = reader.GetChar();
		int maxweight = reader.GetChar();
		game->Map_UserInterface->map_inventory->AddItem(newitem);
		game->map->m_Players[World::WorldCharacterID]->weight = weight;
		game->map->m_Players[World::WorldCharacterID]->maxweight = maxweight;

		EIF_Data m_item = World::EIF_File->Get(newitem.id);
		game->Map_UserInterface->DrawHelpMessage("Notification", "You picked up " + std::to_string(newitem.amount) + "x " + m_item.name);


		int NumberOfItems = reader.Remaining() / 5;
		game->world->W_UI_Infobox->NewBox();
		game->world->W_UI_Infobox->CreateMessage("Chest", chestmsg, true);
		for (int i = 0; i < NumberOfItems; i++)
		{
			unsigned short ItemID = reader.GetShort();
			int Amount = reader.GetThree();
			game->world->W_UI_Infobox->AddStorageItem(ItemID, Amount, 0);
		}
		break;
	}
	default:
		return false;
	}
	return true;
}
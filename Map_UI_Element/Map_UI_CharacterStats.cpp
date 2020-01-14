#include "..\Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_CharStats_MapUI;
Game* Ptr_CharStats_Game;
Map_UI_CharacterStats::Map_UI_CharacterStats(void* m_UIElement, void* m_Game)
{
	Ptr_CharStats_MapUI = (Map_UI*)m_UIElement;
	Ptr_CharStats_Game = (Game*)m_Game;

		this->UI_Element_CharacterStatsButton = new Button(m_Game, 62, 430, 0, 95, 36, 19, false, Ptr_CharStats_Game->resource->CreateTexture(2, 25, false).Texture);
}

void Map_UI_CharacterStats::Update()
{
	this->UI_Element_CharacterStatsButton->Update(Ptr_CharStats_MapUI->MouseX, Ptr_CharStats_MapUI->MouseY, Ptr_CharStats_MapUI->MousePressed);
	if (this->UI_Element_CharacterStatsButton->MouseClickedOnElement())
	{
		Ptr_CharStats_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_CharacterStats, 0);
	}
	switch (Ptr_CharStats_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_CharacterStats):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_CharacterStats::Render()
{
	this->UI_Element_CharacterStatsButton->Draw(Ptr_CharStats_MapUI->Sprite);
	switch (Ptr_CharStats_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_CharacterStats):
	{
		Ptr_CharStats_Game->Draw(Ptr_CharStats_MapUI->Sprite, Ptr_CharStats_Game->resource->CreateTexture(2, 34, false).Texture, 102, 332, 0.1f, D3DCOLOR_ARGB(255, 255, 255, 255));
		D3DCOLOR fontcol = D3DCOLOR_ARGB(222, 255, 255, 255);
		int x = 153;
		int y = 339;
		RECT rct;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		std::string m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->str);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->intl);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->wis);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->agi);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->con);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->cha);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);
	
		x = 260;
		y = 339;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->hp);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->tp);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);


		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->mindam) + " - " + to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->maxdam);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->accuracy);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->armor);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->evade);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		x = 260 + 122;
		y = 339;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->name;
		m_message[0] = std::toupper(m_message[0]);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->guildname;
		m_message[0] = std::toupper(m_message[0]);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->weight) + " / " + to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->maxweight);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->statpoints);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->skillpoints);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		x = 260 +121+ 100;
		y = 339 + 36;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		int amount = 0;
		for (int i = 0; i < Ptr_CharStats_MapUI->map_inventory->inventory.size(); i++)
		{
			if (Ptr_CharStats_MapUI->map_inventory->inventory[i].id == 1)
			{
				amount = Ptr_CharStats_MapUI->map_inventory->inventory[i].amount;
			}
		}
		m_message = to_string(amount);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->exp);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		int tnl = std::round(std::pow((Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->level + 1), 3.0) * 133.1) - std::round(std::pow((Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->level), 3.0) * 133.1);
		m_message = to_string(tnl);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->karma);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		x = 254 + 101 + 200;
		y = 339;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(Ptr_CharStats_Game->map->m_Players[World::WorldCharacterID]->level);
		Ptr_CharStats_Game->MessageFont->DrawTextA(Ptr_CharStats_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);
		break;
	}
	default:
		return;
	}
}

Map_UI_CharacterStats::~Map_UI_CharacterStats()
{

}

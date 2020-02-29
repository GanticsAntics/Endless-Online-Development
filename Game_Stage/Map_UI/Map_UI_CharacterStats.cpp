#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "Map_UI_CharacterStats.h"

Map_UI_CharacterStats::Map_UI_CharacterStats(Map_UI* m_UIElement, Game* p_game)
{
	this->m_MapUI = (Map_UI*)m_UIElement;
	this->m_game = p_game;

	this->UI_Element_CharacterStatsButton = new Button(this->m_game, 62, 430, 0, 95, 36, 19, false, this->m_game->ResourceManager->GetResource(2, 25, false));
}

void Map_UI_CharacterStats::Update()
{
	this->UI_Element_CharacterStatsButton->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_MapUI->MousePressed);
	if (this->UI_Element_CharacterStatsButton->MouseClickedOnElement())
	{
		this->m_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_CharacterStats, 0);
	}
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_CharacterStats):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_CharacterStats::Render(float depth)
{
	this->UI_Element_CharacterStatsButton->Draw();
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_CharacterStats):
	{
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 34, false), 102, 332, sf::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
		sf::Color fontcol = sf::Color::Color(222, 255, 255, 255);
		int x = 153;
		int y = 339;
		RECT rct;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		std::string m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->str);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);
		//this->m_game->MessageFont->DrawTextA(this->m_MapUI->Sprite, m_message.c_str(), -1, &rct, DT_NOCLIP, fontcol);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->intl);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->wis);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->agi);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->con);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->cha);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);
	
		x = 260;
		y = 339;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->hp);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->tp);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);


		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->mindam) + " - " + to_string(this->m_game->map->m_Players[World::WorldCharacterID]->maxdam);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->accuracy);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->armor);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->evade);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		x = 260 + 122;
		y = 339;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = this->m_game->map->m_Players[World::WorldCharacterID]->name;
		m_message[0] = std::toupper(m_message[0]);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = this->m_game->map->m_Players[World::WorldCharacterID]->guildname;
		m_message[0] = std::toupper(m_message[0]);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->weight) + " / " + to_string(this->m_game->map->m_Players[World::WorldCharacterID]->maxweight);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->statpoints);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->skillpoints);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		x = 260 +121+ 100;
		y = 339 + 36;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		int amount = 0;
		for (int i = 0; i < this->m_MapUI->map_inventory->inventory.size(); i++)
		{
			if (this->m_MapUI->map_inventory->inventory[i].id == 1)
			{
				amount = this->m_MapUI->map_inventory->inventory[i].amount;
			}
		}
		m_message = to_string(amount);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->exp);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		int tnl = std::round(std::pow((this->m_game->map->m_Players[World::WorldCharacterID]->level + 1), 3.0) * 133.1) - std::round(std::pow((this->m_game->map->m_Players[World::WorldCharacterID]->level), 3.0) * 133.1);
		m_message = to_string(tnl);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);
//
		y += 18;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->karma);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);

		x = 254 + 101 + 200;
		y = 339;
		rct.left = x;
		rct.right = x + 200;
		rct.top = y;
		rct.bottom = y + 50;
		m_message = to_string(this->m_game->map->m_Players[World::WorldCharacterID]->level);
		this->m_game->DrawTextW(m_message, rct.left, rct.top, fontcol, 13, false, depth);
		break;
	}
	default:
		return;
	}
}

Map_UI_CharacterStats::~Map_UI_CharacterStats()
{

}

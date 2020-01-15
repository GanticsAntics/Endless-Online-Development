#pragma once
#include "World.h"
#include "Map_UI_Inventory.h"
#include "Map_UI_Element/Map_UI_News.h"
#include "Map_UI_Element/Map_UI_Party.h"
#include "Map_UI_Element/Map_UI_Skills.h"
#include "Map_UI_Element/Map_UI_Map.h"
#include "Map_UI_Element/Map_UI_PassiveSkills.h"
#include "Map_UI_Element/Map_UI_Talk.h"
#include "Map_UI_Element/Map_UI_CharacterStats.h"
#include "Map_UI_Element/Map_UI_WhoIsOnline.h"
#include "Map_UI_Element/Map_UI_Party.h"
#include "Map_UI_Element/Map_UI_KeyboardMacros.h"
#include "Map_UI_Element/Map_UI_GameSettings.h"
#include "Map_UI_Element/Map_UI_GameHelp.h"
#include "Map_UI_Element/UI_ChatBubbleHandler.h"
#include "Map_UI_Element/Map_UI_SelectPlayer.h"

class Map_UI
{
public:
	Map_UI();
	ID3DXSprite* Sprite;
	World* m_world;
	IDirect3DDevice9Ptr m_Device;
	Textbox* ChatTextbox;
	std::shared_ptr<IDirect3DTexture9> HudStatsTexture;
	bool isactive = false;
	enum UI_ElementStage
	{
		UI_Element_News = 0,
		UI_Element_Inventory,
		UI_Element_Map,
		UI_Element_Skills,
		UI_Element_PassiveSkills,
		UI_Element_Talk,
		UI_Element_CharacterStats,
		UI_Element_WhoIsOnline,
		UI_Element_Party,
		UI_Element_KeyboardMacros,
		UI_Element_GameSettings,
		UI_Element_GameHelp,
	};
	time_t HelpMessageTimer;
	std::string HelpMessageTitle = "";
	std::string HelpMessage= "";
	UI_ElementStage UI_Stage = UI_ElementStage::UI_Element_News;
	int Substage = 0;
	Map_UI_News* map_news;
	Map_UI_Inventory* map_inventory;
	Map_UI_CharacterStats* map_characterstats;
	Map_UI_GameHelp* map_gamehelp;
	Map_UI_GameSettings* map_gamesettings;
	Map_UI_KeyboardMacros* map_macro;
	Map_UI_Map* map_mapUI;
	Map_UI_Party* map_party;
	Map_UI_PassiveSkills* map_passiveskills;
	Map_UI_Skills* map_skills;
	Map_UI_Talk* map_talk;
	Map_UI_WhoIsOnline* map_whoisonline;
	UI_ChatBubbleHandler* map_ChatBubbleHandler;
	Map_UI_SelectPlayer* PlayerSelect;
	bool StatBarDrawn[4] = { false,false,false,false };
	int MouseX;
	int MouseY;
	bool MousePressed;
	bool MouseHeld;
	int FPS;
	void SetStage(UI_ElementStage m_Stage, int m_substage = 0) { this->UI_Stage = m_Stage; this->Substage = m_substage; }
	void Initialize(World* _world, IDirect3DDevice9Ptr m_Device, LPVOID* m_game);
	void UI_SendMessage();
	void Render();
	void Update();
	void DrawHUDStats();
	void DrawHelpMessage(std::string title, std::string Message);
	~Map_UI();
};

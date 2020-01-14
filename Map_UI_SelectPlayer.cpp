#include "stdafx.h"
#include "Map_UI_SelectPlayer.h"
#include "..\Map_UI.h"
#include "..\Game.h"

Map_UI* Ptr_SelectPlayer_MapUI;
Game* Ptr_SelectPlayer_Game;
Map_UI_SelectPlayer::Map_UI_SelectPlayer(void* m_UIElement, void* m_Game)
{
	Ptr_SelectPlayer_MapUI = (Map_UI*)m_UIElement;
	Ptr_SelectPlayer_Game = (Game*)m_Game;
	//imgw = 16,16
	

}

void Map_UI_SelectPlayer::Update()
{
	
	switch (Ptr_SelectPlayer_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_News):
	{

		
		break;
	}
	default:
		return;
	}
}

void Map_UI_SelectPlayer::Render()
{
	switch (Ptr_SelectPlayer_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_News):
	{
	

		break;
	}
	default:
		return;
	}
}
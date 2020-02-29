#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\game.h"

Map_UI_News::Map_UI_News(Map_UI* m_UIElement, Game* m_Game)
{
	this->m_MapUI = m_UIElement;
	this->m_game = m_Game;
	//imgw = 16,16
	this->UI_TextScrollbar = new UI_Scrollbar(569, 352, 450, 117, -465, 0, 82, "",this->m_game->ResourceManager->GetResource(2, 29, false), this->m_game, this->m_game->MessageFont, this->m_game->ResourceManager->GetResource(2, 32, true));
	this->UI_TextScrollbar->SetButtonsEnabled(true);
	this->UI_TextScrollbar->SetVertical(true);
	
}	
int ScrollBarFPSCounter = 0;
void Map_UI_News::Update()
{
	//ScrollBarFPSCounter++;
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_News):
	{

		this->UI_TextScrollbar->Update(this->m_MapUI->MouseX, this->m_MapUI->MouseY, this->m_game->MouseWheelVal, this->m_MapUI->MousePressed, this->m_MapUI->MouseHeld, this->m_game->FPS);
		//ScrollBarFPSCounter = 0;
		break;
	}
	default:
		return;
	}
}

void Map_UI_News::Render(float depth)
{
	switch (this->m_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_News):
	{
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 48, false), 102, 332, sf::Color(255, 255, 255, 255),0,0,-1,-1,sf::Vector2f(1,1), depth);
		this->UI_TextScrollbar->Draw(depth);
		
		break;
	}
	default:
		return;
	}
}

Map_UI_News::~Map_UI_News()
{

}

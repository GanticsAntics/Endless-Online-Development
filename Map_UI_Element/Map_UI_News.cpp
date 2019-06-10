#include "..\Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_News_MapUI;
Game* Ptr_News_Game;
Map_UI_News::Map_UI_News(void* m_UIElement, void* m_Game)
{
	Ptr_News_MapUI = (Map_UI*)m_UIElement;
	Ptr_News_Game = (Game*)m_Game;
	//imgw = 16,16
	this->UI_TextScrollbar = new UI_Scrollbar(568, 351, 450, 117, -465, 0, 82, "",Ptr_News_Game->ScrollBarTexture.Texture, m_Game, Ptr_News_Game->MessageFont);
}
int ScrollBarFPSCounter = 0;
void Map_UI_News::Update()
{
	ScrollBarFPSCounter++;
	switch (Ptr_News_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_News):
	{

		this->UI_TextScrollbar->Update(Ptr_News_MapUI->MouseX, Ptr_News_MapUI->MouseY, Ptr_News_MapUI->MousePressed, Ptr_News_MapUI->MouseHeld, Ptr_News_Game->FPS);
		ScrollBarFPSCounter = 0;
		break;
	}
	default:
		return;
	}
}

void Map_UI_News::Render()
{
	switch (Ptr_News_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_News):
	{
		Ptr_News_Game->Draw(Ptr_News_MapUI->Sprite, Ptr_News_Game->resource->CreateTexture(2, 48, true).Texture, 102, 332, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		this->UI_TextScrollbar->Draw(Ptr_News_MapUI->Sprite);
		
		break;
	}
	default:
		return;
	}
}

Map_UI_News::~Map_UI_News()
{

}

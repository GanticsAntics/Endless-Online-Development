#include "..\Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_WhoIsOnline_MapUI;
Game* Ptr_WhoIsOnline_Game;
Map_UI_WhoIsOnline::Map_UI_WhoIsOnline(void* m_UIElement, void* m_Game)
{
	Ptr_WhoIsOnline_MapUI = (Map_UI*)m_UIElement;
	Ptr_WhoIsOnline_Game = (Game*)m_Game;

	this->UI_Element_WhoIsOnlineButton = new Button(m_Game, 590, 350, 0, 114, 36, 19, false, Ptr_WhoIsOnline_Game->resource->CreateTexture(2, 25, false).Texture);
}

void Map_UI_WhoIsOnline::Update()
{
	this->UI_Element_WhoIsOnlineButton->Update(Ptr_WhoIsOnline_MapUI->MouseX, Ptr_WhoIsOnline_MapUI->MouseY, Ptr_WhoIsOnline_MapUI->MousePressed);
	if (this->UI_Element_WhoIsOnlineButton->MouseClickedOnElement())
	{
		Ptr_WhoIsOnline_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_WhoIsOnline);
	}
	switch (Ptr_WhoIsOnline_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_WhoIsOnline):
	{
		break;
	}
	default:
		return;
	}
}

void Map_UI_WhoIsOnline::Render()
{
	this->UI_Element_WhoIsOnlineButton->Draw(Ptr_WhoIsOnline_MapUI->Sprite);
	switch (Ptr_WhoIsOnline_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_WhoIsOnline):
	{
		Ptr_WhoIsOnline_Game->Draw(Ptr_WhoIsOnline_MapUI->Sprite, Ptr_WhoIsOnline_Game->resource->CreateTexture(2, 36, false).Texture, 102, 332, 0.1f, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	default:
		return;
	}
}

Map_UI_WhoIsOnline::~Map_UI_WhoIsOnline()
{

}

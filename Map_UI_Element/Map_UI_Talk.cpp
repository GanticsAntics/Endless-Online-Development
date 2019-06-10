#include "..\Map_UI.h"
#include "..\Game.h"
Map_UI* Ptr_Talk_MapUI;
Game* Ptr_Talk_Game;
Map_UI_Talk::Map_UI_Talk(void* m_UIElement, void* m_Game)
{
	Ptr_Talk_MapUI = (Map_UI*)m_UIElement;
	Ptr_Talk_Game = (Game*)m_Game;

	this->UI_Element_TalkButton = new Button(m_Game, 62, 410, 0, 76, 36, 19, false, Ptr_Talk_Game->resource->CreateTexture(2, 25, false).Texture);
	this->UI_TextScrollbar = new UI_Scrollbar(568, 333,600, 117, -445, 0, 82, TextTools::AllChat , Ptr_Talk_Game->ScrollBarTexture.Texture, m_Game, Ptr_Talk_Game->MessageFont);
	
	/*for (int i = 0; i < 200; i++)
	{
		TextTools::ChatContainer newcontainer;
		newcontainer.CharacterName = "XHotdog";
		std::string message = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
		newcontainer.MessageLength = 1;
		newcontainer.message_col = D3DCOLOR_ARGB(255, 0,0,0);
		TextTools::AppendChat(newcontainer.ChatIndex, 380, newcontainer.CharacterName, message, Ptr_Talk_Game->MessageFont, newcontainer.message_col);
	}*/

}

void Map_UI_Talk::Update()
{
	this->UI_Element_TalkButton->Update(Ptr_Talk_MapUI->MouseX, Ptr_Talk_MapUI->MouseY, Ptr_Talk_MapUI->MousePressed);
	if (this->UI_Element_TalkButton->MouseClickedOnElement())
	{
		Ptr_Talk_MapUI->SetStage(Map_UI::UI_ElementStage::UI_Element_Talk);
	}
	switch (Ptr_Talk_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Talk):
	{
		this->UI_TextScrollbar->Update(Ptr_Talk_MapUI->MouseX, Ptr_Talk_MapUI->MouseY, Ptr_Talk_MapUI->MousePressed, Ptr_Talk_MapUI->MouseHeld, Ptr_Talk_Game->FPS);
		break;
	}
	default:
		return;
	}
}

void Map_UI_Talk::Render()
{
	this->UI_Element_TalkButton->Draw(Ptr_Talk_MapUI->Sprite);
	switch (Ptr_Talk_MapUI->UI_Stage)
	{
	case(Map_UI::UI_ElementStage::UI_Element_Talk):
	{
		Ptr_Talk_Game->Draw(Ptr_Talk_MapUI->Sprite, Ptr_Talk_Game->resource->CreateTexture(2, 28, false).Texture, 102, 332, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		this->UI_TextScrollbar->Draw(Ptr_Talk_MapUI->Sprite);
		break;
	}
	default:
		return;
	}
}

Map_UI_Talk::~Map_UI_Talk()
{

}

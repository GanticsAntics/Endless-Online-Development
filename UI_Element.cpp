#include "stdafx.h"
#include "UI_Element.h"
#include "Game.h"

Game* p_game;

UI_Element::UI_Element()
{
	this->MouseClicked = false;
	this->MouseOver = false;
	this->AnimDirectionTopDown = false;
}


UI_Element::~UI_Element()
{
}

void UI_Element::Initialize(VOID* m_Game)
{
	p_game = (Game*)m_Game;
}
void UI_Element::UpdateElement()
{
	if (p_game->MouseX > this->Position.first && p_game->MouseY > this->Position.second && p_game->MouseX < (this->Position.first + this->Size.first) && p_game->MouseY < (this->Position.second + this->Size.second))
	{
		if (!this->HighlightOnMouseDown)
		{
			this->AnimID = 1;
		}
		this->MouseOver = true;
		if (p_game->MousePressed)
		{
			if (this->HighlightOnMouseDown)
			{
				this->AnimID = 1;
			}
			this->MouseClicked = true;
		}
		else
		{
			this->MouseClicked = false;
		}

	}
	else
	{
		if (!this->HighlightOnMouseDown)
		{
			this->AnimID = 0;
			this->MouseOver = false;
		}
	}
}
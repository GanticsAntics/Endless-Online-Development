#include "..\stdafx.h"

UI_Element::UI_Element()
{
	this->MouseClicked = false;
	this->MouseOver = false;
	this->AnimDirectionTopDown = false;
}


UI_Element::~UI_Element()
{
}

void UI_Element::Initialize(Game* p_game)
{
	this->m_game = p_game;
}
void UI_Element::UpdateElement()
{
	if (m_game->MouseX > this->Position.first && m_game->MouseY > this->Position.second && m_game->MouseX < (this->Position.first + this->Size.first) && m_game->MouseY < (this->Position.second + this->Size.second))
	{
		if (!this->HighlightOnMouseDown)
		{
			this->AnimID = 1;
		}
		this->MouseOver = true;
		if (m_game->MousePressed)
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
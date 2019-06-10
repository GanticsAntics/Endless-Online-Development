#include "stdafx.h"
#include "Map_NPC.h"
#include "Game.h"
#include "World.h"
Game* m_n_Game;
Map_NPC::Map_NPC()
{
}


Map_NPC::~Map_NPC()
{
}

void Map_NPC::Initialize(LPVOID* M_Game)
{
	m_n_Game = (Game*)M_Game;

}
void Map_NPC::SetStance(NPC_Stance m_Stance)
{
	this->Stance = m_Stance;
	this->FrameID = 0;
	FrameCounter = 0;
}
int  Map_NPC::FindWalkDirection(int dest_x, int dest_y)
{
	this->destination_x = dest_x;
	this->destination_y = dest_y;

	int desx = this->x - dest_x;
	int desy = this->y - dest_y;
	if (desx < 0)
	{
		return 2;
	}
	else if (desx > 0)
	{
		return 3;
	}
	else if (desy < 0)
	{
		return 0;
	}
	else if (desy > 0)
	{
		return 1;
	}
	return 0;
}
void Map_NPC::MoveNPC(int FPS, int DestX, int DestY)
{
	//std::string str = "Move From " + this->name + ". Player ID " + std::to_string(this->CharacterID);
	   //World::DebugPrint(str.c_str());
	
	int move_direction = this->FindWalkDirection(DestX, DestY);
	this->direction = move_direction;
	moveFPS++;
	if (moveFPS > FPS / 8)
	{
		switch (move_direction)
		{
		case(0):
		{
			this->yoffset += 4;
			this->xoffset -= 8;
			break;
		}
		case(1):
		{
			this->xoffset -= 8;
			this->yoffset -= 4;
			break;
		}
		case(2):
		{
			this->xoffset -= 8;
			this->yoffset += 4;
			break;
		}
		case(3):
		{
			this->yoffset -= 4;
			this->xoffset -= 8;
			break;
		}
		}
		moveFPS = 0;
		WalkCounter++;
	}
	if (WalkCounter >= 4)
	{
		switch (move_direction)
		{
		case(0):
		{
			this->y++;
			break;
		}
		case(1):
		{
			this->y--;
			break;
		}
		case(2):
		{
			this->x++;
			break;
		}
		case(3):
		{
			this->x--;
			break;
		}
		}
		this->destination_x = -1;
		this->destination_y = -1;
		this->xoffset = 0;
		this->yoffset = 0;
		WalkCounter = 0;
		this->SetStance(Map_NPC::NPC_Stance::Standing);
	}
}
void Map_NPC::Update(int FPS)
{
	if (this->destination_x >= 0 || this->destination_y >= 0)
	{
		MoveNPC(FPS, destination_x, destination_y);
	}

	this->FrameCounter++;
	switch (this->Stance)
	{
	case(NPC_Stance::Standing):
	{
		this->FrameID = 0;
		this->FrameCounter = 0;
		break;
	}
	case(NPC_Stance::Walking):
	{
		if (FrameCounter > (FPS / 8))
		{
			this->FrameID++;
			if (this->FrameID > 3)
			{
				this->FrameID = 0;
				this->SetStance(NPC_Stance::Standing);
			}
			FrameCounter = 0;
		}
		break;
	}
	case(NPC_Stance::Attacking):
	{
		if (FrameCounter > (FPS / 4))
		{
			this->FrameID++;
			if (this->FrameID > 1)
			{
				this->FrameID = 0;
				this->SetStance(NPC_Stance::Standing);
			}
			FrameCounter = 0;
		}
		break;
	}
	case(NPC_Stance::Dead):
	{
		if (FrameCounter > (FPS))
		{
			this->FrameID++;
			if (this->FrameID > 0)
			{
				this->FrameID = 0;
			}
		}
		break;
	}
	}
}

void Map_NPC::Render(ID3DXSprite* _Sprite, int x, int y, float depth)
{
	int IndexOffSet = 0;
	int DirectionOffset = 0;
	if (this->Stance == Map_NPC::Standing) { IndexOffSet = 0; DirectionOffset = 2; }
	if (this->Stance == Map_NPC::Walking) { IndexOffSet = 4; DirectionOffset = 4;}
	if (this->Stance == Map_NPC::Attacking) { IndexOffSet = 4 + 8; DirectionOffset = 2;}
	int Scaleflip = 0;
	if (this->direction == 1 || this->direction == 2)
	{
		Scaleflip = 1;
	}

	int TextureIndex = 1 + IndexOffSet + FrameID + (World::ENF_File->data[this->ID].graphic - 1) * 40;
	if (this->direction == 1 || this->direction == 3)
	{
 		TextureIndex += DirectionOffset;
	}
	m_n_Game->resource->CreateTexture(21, TextureIndex, true);
	int height = m_n_Game->resource->GetImageInfo(21, TextureIndex, true).Height;
	int width = m_n_Game->resource->GetImageInfo(21, TextureIndex, true).Width;
	
	D3DXMATRIX mat;
	D3DXMATRIX * originalTransform = new D3DXMATRIX();
	_Sprite->GetTransform(originalTransform);
	D3DXVECTOR2 * position = new D3DXVECTOR2(0, 0);
	D3DXVECTOR2 * spriteCentre = new D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 * Scale = new D3DXVECTOR2(1 - (Scaleflip * 2), 1);
	D3DXVECTOR2 * ScaleCntre = new D3DXVECTOR2(x + 6, 1);
	D3DXMatrixTransformation2D(&mat, ScaleCntre, 0, Scale, NULL, 0.0f, position);

	D3DXVECTOR3 * Pos = new D3DXVECTOR3(x + 6 - (width / 2) + this->xoffset, y + this->yoffset + 64 - height, depth);
	D3DXVECTOR3 * Center = new D3DXVECTOR3(0, 0, 0);

	_Sprite->SetTransform(&mat);
	_Sprite->Draw(m_n_Game->resource->CreateTexture(21, TextureIndex, true).Texture.get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	_Sprite->SetTransform(originalTransform);

	delete originalTransform;
	delete Scale;
	delete ScaleCntre;
	delete spriteCentre;
	delete position;
	delete Pos;
	delete Center;
	
}
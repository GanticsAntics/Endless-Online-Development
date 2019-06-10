#include "stdafx.h"
#include "Map_Player.h"
#include "World.h"

Map_Player::Map_Player()
{
}


Map_Player::~Map_Player()
{
}

void Map_Player::SetStance(PlayerStance m_Stance)
{
	this->Stance = m_Stance;
	fpscounter = 0;
	this->frame_ID = 0;
}
int  Map_Player::FindWalkDirection(int dest_x, int dest_y)
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

void Map_Player::MovePlayer(int FPS, int dest_x, int dest_y)
{
	//std::string str = "Move From " + this->name + ". Player ID " + std::to_string(this->CharacterID);
	//World::DebugPrint(str.c_str());
	int move_direction = this->FindWalkDirection(dest_x, dest_y);
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
		this->SetStance(CharacterModel::PlayerStance::Standing);
	}
}
void Map_Player::Update(int FPS)
{
	if (this->destination_x >= 0 || this->destination_y >= 0)
	{
		MovePlayer(FPS, destination_x, destination_y);
	}

	fpscounter++;
	switch (this->Stance)
	{
		case(PlayerStance::Standing):
		{
			this->frame_ID = 0;
			fpscounter = 0;
			break;
		}
		case(PlayerStance::Walking):
		{
			if (fpscounter > (FPS / 8))
			{
				this->frame_ID++;
				if (this->frame_ID > 3)
				{
					this->frame_ID = 0;
					this->SetStance(CharacterModel::Standing);
				}
				fpscounter = 0;
			}
			break;
		}
		case(PlayerStance::BluntAttacking):
		{
			if (fpscounter > (FPS / 4))
			{
				this->frame_ID++;
				if (this->frame_ID > 1)
				{
					this->frame_ID = 0;
					this->SetStance(CharacterModel::Standing);
				}
				fpscounter = 0;
			}
			break;
		}
		case(PlayerStance::BowAttacking):
		{
			if (fpscounter > (FPS))
			{
				this->frame_ID++;
				if (this->frame_ID > 0)
				{
					this->frame_ID = 0;
					this->SetStance(CharacterModel::Standing);
				}
			}
			break;
		}
		case(PlayerStance::Spelling):
		{
			if (fpscounter > (FPS))
			{
				this->frame_ID = 0;
				fpscounter = 0;
				this->SetStance(CharacterModel::Standing);
			}
			break;
		}
		case(PlayerStance::GroundSitting):
		{
			this->frame_ID = 0;
			fpscounter = 0;
			break;
		}
		case(PlayerStance::ChairSitting):
		{
			this->frame_ID = 0;
			fpscounter = 0;
			break;
		}
	}
}
#include "..\..\stdafx.h"
#include "Map_Player.h"
#include "..\..\World.h"
#include "..\..\game.h"

Map_Player::Map_Player()
{
}


Map_Player::~Map_Player()
{
}
void Map_Player::Initialize(Game* M_Game)
{
	this->m_game = M_Game;
	this->Deathcounter = 0;
	this->InitializeModel(M_Game);
}
void Map_Player::SetStance(PlayerStance m_Stance)
{
	this->Stance = m_Stance;
	fpscounter = 0;
	this->frame_ID = 0;
	//startwalkanimationtimer = clock();
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
	endwalkanimationtimer = clock();
	//std::string str = "Move From " + this->name + ". Player ID " + std::to_string(this->CharacterID);
	//World::DebugPrint(str.c_str());
	int move_direction = this->FindWalkDirection(dest_x, dest_y);
	this->direction = move_direction;
	moveFPS++;
	if (endwalkanimationtimer - startwalkanimationtimer > (1000/8.5))
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
				this->xoffset += 8;
				this->yoffset -= 4;
				break;
			}
			case(2):
			{
				this->xoffset += 8;
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
		this->frame_ID++;
		startwalkanimationtimer = clock();
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
		this->frame_ID = 0;
		this->SetStance(CharacterModel::PlayerStance::Standing);
	}
}

void Map_Player::DealDamage(int Damage)
{
	this->hp -= Damage;
	std::string p_Damage = to_string(Damage);
	this->Damage.clear();
	this->time = 0;
	for (int i = 0; i < p_Damage.size(); i++)
	{
		unsigned char damage = p_Damage[i];
		this->Damage.push_back(damage);
	}
	std::reverse(this->Damage.begin(), this->Damage.end());
	this->isattacked = true;
}

void Map_Player::PlayerKill()
{
	this->SetStance(Map_Player::PlayerStance::Standing);
	this->Deathcounter += 1;
}
void Map_Player::Update(int FPS)
{
	if (this->destination_x >= 0 || this->destination_y >= 0)
	{
		MovePlayer(FPS, destination_x, destination_y);
	}
	if (this->Damage.size() > 0)
	{
		this->time++;
	}
	if (this->Deathcounter > 0)
	{
		Deathcounter++;
	}
	if (this->time > FPS/2)
	{
		this->Damage.clear();
		this->time = 0;
		this->isattacked = false;
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
		case(PlayerStance::BluntAttacking):
		{
			if (this->frame_ID == 0 && fpscounter > (FPS / 5))
			{
				this->frame_ID++;
				fpscounter = 0;
			}
			if (fpscounter > (FPS / 3))
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
			if (fpscounter > (FPS / 3))
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

void Map_Player::Map_PlayerRender(sf::Sprite* _Sprite, int x, int y, float depth, sf::Color m_Color)
{
	this->Render(x, y, depth, m_Color);

	if (this->isattacked)
	{
		int _x = this->x;
		int _y = this->y;
		RECT IconSrcRect;
		IconSrcRect.left = 0;
		IconSrcRect.top = 28;
		IconSrcRect.bottom = IconSrcRect.top + 7;
		IconSrcRect.right = 40;
		int scalex = 1;

		if (this->direction == 1 || this->direction == 2)
		{
			scalex = -1;
		}
		sf::Vector3f* IconPos = new sf::Vector3f(x + 6 - 35 / 2 + this->xoffset * scalex, y + this->yoffset + 50 - 70, 0);
		sf::Vector3f* IconCentre = new sf::Vector3f(0, 0, 0);
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color::White, IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), depth);
		//_Sprite->Draw(m_this->m_game->Map_UserInterface->HudStatsTexture.get(), &IconSrcRect, IconCentre, IconPos, sf::Color::Color(255, 255, 255, 255));

		float HPPercent = (float)this->hp / (float)this->maxhp;
		int hpcolormultiplier = 0;
		if (HPPercent < 0.7f)
		{
			hpcolormultiplier++;
		}
		if (HPPercent < 0.4f)
		{
			hpcolormultiplier++;
		}
		IconSrcRect.left = 0;
		IconSrcRect.top = 35 + (hpcolormultiplier * 7);
		IconSrcRect.bottom = IconSrcRect.top + 7;
		IconSrcRect.right = HPPercent * 40;

		this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color::White, IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), depth);
		//m_this->m_game->map->Sprite->Draw(m_this->m_game->Map_UserInterface->HudStatsTexture.get(), &IconSrcRect, IconCentre, IconPos, sf::Color::Color(255, 255, 255, 255));
		IconPos->y -= 14;
		IconPos->x += 20;
		IconPos->x += (this->Damage.size() * 9) / 2;
		IconPos->y -= (7 * ((float)this->time / ((float)m_game->FPS / 2.5)));
		for (int i = 0; i < this->Damage.size(); i++)
		{
			unsigned char damage = this->Damage[i] - 48;

			IconSrcRect.left = 40 + (damage * 9);
			IconSrcRect.top = 28;
			IconSrcRect.bottom = IconSrcRect.top + 12;
			IconSrcRect.right = IconSrcRect.left + 9;
			if (damage == 0 && this->Damage.size() == 1)
			{
				IconSrcRect.left = 132;
				IconSrcRect.top = 28;
				IconSrcRect.bottom = IconSrcRect.top + 12;
				IconSrcRect.right = IconSrcRect.left + 30;
				IconPos->x -= 18;
			}
			else
			{
				IconPos->x -= 9;
			}

			float alpha = 255 - (160 * ((float)this->time / ((float)m_game->FPS / 2)));
			//m_this->m_game->map->Sprite->Draw(m_this->m_game->Map_UserInterface->HudStatsTexture.get(), &IconSrcRect, IconCentre, IconPos, sf::Color::Color(int)alpha, 255, 255, 255));
			this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color(255,255,255,alpha), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), depth);
		}
		delete IconPos;
		delete IconCentre;
	}
}
#include "..\..\stdafx.h"
#include "Map_NPC.h"
#include "..\..\game.h"
#include "..\..\World.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#undef max
#undef min
Map_NPC::Map_NPC()
{
}


Map_NPC::~Map_NPC()
{
}

void Map_NPC::Initialize(LPVOID* M_Game)
{
	m_Game = (Game*)M_Game;
	this->Deathcounter = 0;
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
	if (this->Deathcounter > 0)
	{
		Deathcounter++;
	}
	if (this->destination_x >= 0 || this->destination_y >= 0)
	{
		MoveNPC(FPS, destination_x, destination_y);
	}
	if (this->Damage.size() > 0)
	{
		this->time++;
	}
	if (this->time > FPS / 2.5)
	{
		this->Damage.clear();
		this->time = 0;
		this->isattacked = false;
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

void Map_NPC::DealDamage(short HpLeft, int _damage)
{
	this->MaxHP = World::ENF_File->data[this->ID].hp;
	this->HP = (float)(HpLeft / 100.0f)*(float)this->MaxHP;
	std::string p_Damage = to_string(_damage);
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
void Map_NPC::NPCKill()
{
	this->SetStance(Map_NPC::NPC_Stance::Standing);
	this->Deathcounter += 1;
}
void Map_NPC::Render(sf::Sprite* _Sprite, int x, int y, float depth, sf::Color m_color)
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
	int height = this->m_Game->ResourceManager->GetResource(21, TextureIndex, true)->_height;
	int width = this->m_Game->ResourceManager->GetResource(21, TextureIndex, true)->_width;
	
	sf::Vector2f Scale =  sf::Vector2f(1 - (Scaleflip * 2), 1);
	sf::Vector2f * ScaleCntre = new sf::Vector2f(x + 32, 1);
	//D3DXMatrixTransformation2D(&mat, ScaleCntre, 0, Scale, NULL, 0.0f, position);
	int offsety = max(0, (std::min(41, width - 23)) / 4);
	sf::Vector3f * Pos = new sf::Vector3f(x + 32 - (width / 2) + this->xoffset, offsety + y +  this->yoffset + 22 - height, depth);
	sf::Vector3f * Center = new sf::Vector3f(0, 0, 0);
	m_color = sf::Color::Color(255 - (int)(255 * ((float)this->Deathcounter / ((float)m_Game->FPS / 2.5))), 255, 255, 255);

	//_Sprite->SetTransform(&mat);
	this->m_Game->Draw(this->m_Game->ResourceManager->GetResource(21, TextureIndex, true), Pos->x, Pos->y, sf::Color::White, 0, 0, -1, -1, Scale, depth);
	//_Sprite->Draw(m_n_Game->ResourceManager->CreateTexture(21, TextureIndex, true)._Texture.get(), NULL, Center, Pos, m_color);
	//_Sprite->SetTransform(originalTransform);

	//delete originalTransform;
	delete ScaleCntre;
	delete Pos;
	delete Center;
	
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
		//Pos = new sf::Vector3f(x + 32 - (width / 2) + this->xoffset, offsety + y + this->yoffset + 22 - height, depth);
		sf::Vector3f* IconPos = new sf::Vector3f(x + 32 - 35/2 +this->xoffset * scalex, y + this->yoffset +22 - height, 0);
		sf::Vector3f* IconCentre = new sf::Vector3f(0, 0, 0);
	//	m_n_Game->map->Sprite->Draw(m_n_Game->Map_UserInterface->HudStatsTexture.get(), &IconSrcRect, IconCentre, IconPos, sf::Color::Color(255, 255, 255, 255));
		this->m_Game->Draw(this->m_Game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color(255, 255, 255, 255), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), 0.02f);

		float HPPercent = (float)this->HP / (float)this->MaxHP;
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
		IconSrcRect.top = 35 + (hpcolormultiplier*7);
		IconSrcRect.bottom = IconSrcRect.top + 7;
		IconSrcRect.right = HPPercent*40;
		//m_n_Game->map->Sprite->Draw(m_n_Game->Map_UserInterface->HudStatsTexture.get(), &IconSrcRect, IconCentre, IconPos, sf::Color::Color(255, 255, 255, 255));
		this->m_Game->Draw(this->m_Game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color(255, 255, 255, 255), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), 0.02f);

		IconPos->y -= 14;
		IconPos->x += 20;
		IconPos->x += (this->Damage.size() * 9) / 2;
		IconPos->y -= (7 * ((float)this->time / ((float)m_Game->FPS / 2.5)));
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
			
			float alpha = 255 - ( 160 * ((float)this->time / ((float)m_Game->FPS/2.5)));
			//m_n_Game->map->Sprite->Draw(m_n_Game->Map_UserInterface->HudStatsTexture.get(), &IconSrcRect, IconCentre, IconPos, sf::Color::Color(int)alpha, 255, 255, 255));
			this->m_Game->Draw(this->m_Game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color(255, 255, 255, alpha), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), 0.02f);

		}
		delete IconPos;
		delete IconCentre;
	}
}
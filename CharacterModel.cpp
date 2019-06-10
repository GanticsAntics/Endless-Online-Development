#include "stdafx.h"
#include "Game.h"

///Horidly programmed charaacter alignments..
Game* _game;
boost::shared_ptr<IDirect3DTexture9> CharacterStandTexture;
boost::shared_ptr<IDirect3DTexture9> CharacterWalkTexture;
boost::shared_ptr<IDirect3DTexture9> CharacterAttackBluntTexture;
boost::shared_ptr<IDirect3DTexture9> CharacterSpellTexture;
boost::shared_ptr<IDirect3DTexture9> CharacterSitChairTexture;
boost::shared_ptr<IDirect3DTexture9> CharacterSitGroundTexture;
boost::shared_ptr<IDirect3DTexture9> CharacterAttackBowTexture;
boost::shared_ptr<IDirect3DTexture9> CharacterEmoteTexture;
void CharacterModel::Initialize(LPVOID* m_game)
{
	this->admin =  0;
	this->Gender =  0;
	this->direction = 0;
	this->HairCol = 0;
	this->HairStyle = 0;
	this->name = "";
	this->SkinCol = 0;

	this->WeaponID = -1;
	this->ShieldID = -1;
	this->ArmorID =-1;
	this->ShoeID = -1;
	this->HatID =-1;
	this->xoffset = 0;
	this->yoffset = 0;
	_game = (Game*)m_game;
	CharacterStandTexture = _game->resource->CreateTexture(8, 1, true).Texture;
	CharacterWalkTexture = _game->resource->CreateTexture(8, 2, true).Texture;
	CharacterAttackBluntTexture = _game->resource->CreateTexture(8, 3, true).Texture;
	CharacterSpellTexture = _game->resource->CreateTexture(8, 4, true).Texture;
	CharacterSitChairTexture = _game->resource->CreateTexture(8, 5, true).Texture;
	CharacterSitGroundTexture = _game->resource->CreateTexture(8, 6, true).Texture;
	CharacterAttackBowTexture = _game->resource->CreateTexture(8, 7, true).Texture;
	CharacterEmoteTexture = _game->resource->CreateTexture(8, 8, true).Texture;
	this->SetCharacter(this->Gender,this->HairStyle,this->HairCol,this->SkinCol,this->direction);
}

void CharacterModel::SetCharacter(byte _Gender, byte _HairStyle, byte _HairCol, byte _SkinCol, byte _direction)
{
	this->Gender = _Gender;
	this->HairStyle = _HairStyle;
	this->HairCol = _HairCol;
	this->SkinCol = _SkinCol;
	this->direction = _direction;
	this->Stance = PlayerStance::Standing;

	this->SrcRect = RECT();
	this->SrcRect.top = 0 + (58 *this->SkinCol);
	this->SrcRect.bottom = this->SrcRect.top + 58;
	this->SrcRect.left = 0 + (this->Gender * 35) + (18*(this->direction % 2)) + (this->Gender % 2);
	this->SrcRect.right = this->SrcRect.left + 18;

}

int spritesheetx = 0;
void CharacterModel::AlignCharacter()
{
	switch (this->Stance)
	{
		case(PlayerStance::Standing):
		{
			spritesheetx = 72;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (58 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 58;
			this->SrcRect.left = (18 * this->frame_ID)+ (this->Gender * 35) + (18 * (this->direction % 2)) + (this->Gender % 2);
			this->SrcRect.right = this->SrcRect.left + 18;
			break;
		}
		case(PlayerStance::Walking):
		{
			spritesheetx = 416;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (61 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 61;
			this->SrcRect.left = (26 * this->frame_ID) + (this->Gender * 208) + (104 * (this->direction % 2));
			this->SrcRect.right = this->SrcRect.left + 26;
			break;
		}
		case(PlayerStance::BluntAttacking):
		{
			spritesheetx = 192;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (58 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 58;
			this->SrcRect.left = (24 * this->frame_ID) + (this->Gender * 96) + (48 * (this->direction % 2));
			this->SrcRect.right = this->SrcRect.left + 24;
			break;
		}
		case(PlayerStance::Spelling):
		{
			spritesheetx = 72;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (62 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 62;
			this->SrcRect.left = (18 * this->frame_ID) + (this->Gender * 36) + (18 * (this->direction % 2));
			this->SrcRect.right = this->SrcRect.left + 18;
			break;
		}
		case(PlayerStance::ChairSitting):
		{
			spritesheetx = 96;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (52 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 52;
			this->SrcRect.left = (24 * this->frame_ID) + (this->Gender * 48) + (24 * (this->direction % 2));
			this->SrcRect.right = this->SrcRect.left + 24;
			break;
		}
		case(PlayerStance::GroundSitting):
		{
			spritesheetx = 96;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (43 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 43;
			this->SrcRect.left = (24 * this->frame_ID) + (this->Gender * 48) + (24 * (this->direction % 2));
			this->SrcRect.right = this->SrcRect.left + 24;
			break;
		}
		case(PlayerStance::BowAttacking):
		{
			spritesheetx = 100;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (58 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 58;
			this->SrcRect.left = (25 * this->frame_ID) + (this->Gender * 50) + (25 * (this->direction % 2));
			this->SrcRect.right = this->SrcRect.left + 25;
			break;
		}
	}

}
constexpr float ep = 0.0001f;  // gap between depth of each tile on a layer
constexpr float epi = 0.00001f; // gap between each interleaved layer
enum LayerType
{
	Skin,
	Weapon,
	Shield,
	Hat,
	Shoes,
	Armour,
	BackHair,
	FrontHair
};

struct LayerInfo
{
	LayerType Layer_Type;
	int file;
	int StandXOff;
	int StandYOff;
	int Walk1XOff;
	int Walk1YOff;
	int Walk2XOff;
	int Walk2YOff;
	int Walk3XOff;
	int Walk3YOff;
	int Walk4XOff;
	int Walk4YOff;
	int BluntAttack1XOff;
	int BluntAttack1YOff;
	int BluntAttack2XOff;
	int BluntAttack2YOff;
	int Spell1XOff;
	int Spell1YOff;
	int RangeAttack1XOff;
	int RangeAttack1YOff;
	int GroundSitXOff;
	int GroundSitYOff;
	int ChairSitXOff;
	int ChairSitYOff;
	float depth;
};

///All of the equipment alignments are sourced in this table and based on the above struct.
static constexpr LayerInfo layer_info[8] = {
	{ LayerType::Skin      , 8,   0,0,   -4,-1,   -4,-1,   -4,-1,   -4,-1,   -4,0,   -4,0,    0,-4,    -9,1,    0,18,   0,18,  ep * 2 }, // Skin
	{ LayerType::Weapon    ,18,  32,17,  32,17,   32,17,   32,17,   32,17,   37,16,   37,16,   32,17,     32,17,     0,0,    32,17,   ep * 1 }, // Weapon
	{ LayerType::Shield    ,20,  15,15,  15,15,   15,15,   15,15,   15,15,   15,15,   15,15,    15,15,   15,15,    10,-5,    10,-5,  ep * 1 }, // Shield
	{ LayerType::Hat       ,16,   4,13,  4,13,    4,13,    4,13,    4,13,   4,13,   4,13,   4,13,   4,13,  4,13,   4,13,  ep * 3 }, // Hat
	{ LayerType::Shoes     ,12,   8,-37, 8,-36,  8,-36,    8,-36,   8,-36,   8,-37, 11,-36,  8,-37,   8,-36,   4,-39,   4, -50,  ep * 2 }, // Shoes
	{ LayerType::Armour    ,14,   8,12,  8,13,    8,13,    8,13,    8,13,   8,12,   11,13,   8,12,   13,11,   3,1,   3, 1,  ep * 2 }, // Armor
	{ LayerType::BackHair  ,10,   6,13,  6,13,    6,13,    6,13,    6,13,   6,13,   11,9,    6,13,   6,13,   1,-4,   1,-4,  ep * 1 }, // BackHair
	{ LayerType::FrontHair ,10,   6,13,  6,13,    6,13,    6,13,    6,13,   6,13,   11,9,   6,13,    6,13,   1,-4,   1,-4,  ep * 3 }, // FrontHair
};

///Pulls the offset positions of player sprite tiles.
std::pair<int, int> RetrieveOffset(int layerindex, CharacterModel::PlayerStance m_stance, int m_frameid)
{
	int x = 0;
	int y = 0;
	LayerInfo layer = layer_info[layerindex];
	switch (m_stance)
	{
		case(CharacterModel::PlayerStance::Standing):
		{
			x = layer.StandXOff;
			y = layer.StandYOff;
			break;
		}
		case(CharacterModel::PlayerStance::Walking):
		{
			switch (m_frameid)
			{
				case(0):
				{
					x = layer.Walk1XOff;
					y = layer.Walk1YOff;
					break;
				}
				case(1):
				{
					x = layer.Walk2XOff;
					y = layer.Walk2YOff;
					break;
				}
				case(2):
				{
					x = layer.Walk3XOff;
					y = layer.Walk3YOff;
					break;
				}
				case(3):
				{
					x = layer.Walk4XOff;
					y = layer.Walk4YOff;
					break;
				}
			}
			break;
		}
		case(CharacterModel::PlayerStance::BluntAttacking):
		{
			switch (m_frameid)
			{
				case(0):
				{
					x = layer.BluntAttack1XOff;
					y = layer.BluntAttack1YOff;
					break;
				}
				case(1):
				{
					x = layer.BluntAttack2XOff;
					y = layer.BluntAttack2YOff;
					break;
				}
			}
			break;
		}
		case(CharacterModel::PlayerStance::BowAttacking):
		{
			switch (m_frameid)
			{
				case(0):
				{
					x = layer.RangeAttack1XOff;
					y = layer.RangeAttack1YOff;
					break;
				}
			}
			break;
		}
		case(CharacterModel::PlayerStance::ChairSitting):
		{
			switch (m_frameid)
			{
				case(0):
				{
					x = layer.ChairSitXOff;
					y = layer.ChairSitYOff;
					break;
				}
			}
			break;
		}
		case(CharacterModel::PlayerStance::GroundSitting):
		{
			switch (m_frameid)
			{
				case(0):
				{
					x = layer.GroundSitXOff;
					y = layer.GroundSitYOff;
					break;
				}
			}
			break;
		}
		case(CharacterModel::PlayerStance::Spelling):
		{
			switch (m_frameid)
			{
				case(0):
				{
					x = layer.Spell1XOff;
					y = layer.Spell1YOff;
					break;
				}
			}
			break;
		}
	}
	return std::pair<int, int>(x, y);
}

void CharacterModel::Render(ID3DXSprite* _Sprite, int x, int y, float depth)
{
	this->AlignCharacter();
	int IndexOffSet = 0;
	if (this->Stance == PlayerStance::Walking) { IndexOffSet = 2; }
	if (this->Stance == PlayerStance::Spelling) { IndexOffSet = 2 + 8; }
	if (this->Stance == PlayerStance::BluntAttacking) { IndexOffSet = 2 + 8 + 2; }
	if (this->Stance == PlayerStance::ChairSitting) { IndexOffSet = 2 + 8 + 2 + 4; }
	if (this->Stance == PlayerStance::GroundSitting) { IndexOffSet = 2 + 8 + 2 + 4 + 2; }
	if (this->Stance == PlayerStance::BowAttacking) { IndexOffSet = 2 + 8 + 2 + 4 + 4 ; }

	bool ShieldIsWing = false;
	switch(ShieldID)
	{
		case(9):
		{
			ShieldIsWing = true;
			break;
		}
		case(10):
		{
			ShieldIsWing = true;
			break;
		}
		case(13):
		{
			ShieldIsWing = true;
			break;
		}
		case(14):
		{
			ShieldIsWing = true;
			break;
		}
		case(15):
		{
			ShieldIsWing = true;
			break;
		}
		case(17):
		{
			ShieldIsWing = true;
			break;
		}
		case(18):
		{
			ShieldIsWing = true;
			break;
		}
	default:
		break;
	}
	int Addint = 0;
	if (this->direction == 1 || this->direction == 3)
	{
		switch (this->Stance)
		{
		case(PlayerStance::Standing):
		{
			Addint += 1;
			break;
		}
		case(PlayerStance::Walking):
		{
			Addint += 4;
			break;
		}
		case(PlayerStance::BluntAttacking):
		{
			Addint += 2;
			break;
		}
		case(PlayerStance::BowAttacking):
		{
			Addint += 1;
			break;
		}
		case(PlayerStance::GroundSitting):
		{
			Addint += 1;
			break;
		}
		case(PlayerStance::ChairSitting):
		{
			Addint += 1;
			break;
		}
		case(PlayerStance::Spelling):
		{
			Addint += 1;
			break;
		}
		}
	}
	D3DXMATRIX mat;
	D3DXMATRIX* originalTransform = new D3DXMATRIX();
	_Sprite->GetTransform(originalTransform);
	int Scaleflip = 0;
	if (this->direction == 1 || this->direction == 2)
	{
		Scaleflip = 1;
	}
	D3DXVECTOR2* position = new D3DXVECTOR2(0, 0);
	D3DXVECTOR2* Scale = new D3DXVECTOR2(1 - (Scaleflip * 2), 1);
	D3DXVECTOR2* ScaleCntre = new D3DXVECTOR2(x + ((18) / 2), 0);
	D3DXMatrixTransformation2D(&mat, ScaleCntre, 0, Scale, NULL, 0.0f, position);
	_Sprite->SetTransform(&mat);

	for (int itemlayer = 0; itemlayer < 8; itemlayer++)
	{
		LayerInfo layerinfo = layer_info[itemlayer];
		switch (layerinfo.Layer_Type)
		{
			case(LayerType::Skin):
			{
				std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);
			
				D3DXVECTOR3 * Pos = new D3DXVECTOR3(x + offsetpos.first - 0 + this->xoffset, y + offsetpos.second + this->yoffset, depth - layerinfo.depth);
				D3DXVECTOR3 * Center = new D3DXVECTOR3(0, 0, 0);
				
				switch (this->Stance)
				{
				case(PlayerStance::Standing):
				{
					_Sprite->Draw(CharacterStandTexture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
				case(PlayerStance::Walking):
				{
					Pos->x -= ((this->Gender % 2) * 1);
					_Sprite->Draw(CharacterWalkTexture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
				case(PlayerStance::BluntAttacking):
				{
					Pos->x -= ((this->Gender % 2) * 1);
					_Sprite->Draw(CharacterAttackBluntTexture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
				case(PlayerStance::Spelling):
				{
					_Sprite->Draw(CharacterSpellTexture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
				case(PlayerStance::ChairSitting):
				{
					Pos->x -= ((this->Gender % 2) * 1);
					_Sprite->Draw(CharacterSitChairTexture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
				case(PlayerStance::GroundSitting):
				{
					Pos->x -= ((this->Gender % 2) * 1);
					_Sprite->Draw(CharacterSitGroundTexture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
				case(PlayerStance::BowAttacking):
				{
					Pos->x += ((this->Gender % 2) * 1);
					Pos->y -= ((this->Gender % 2) * 1);
					_Sprite->Draw(CharacterAttackBowTexture.get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
				}
				delete Pos;
				delete Center;
				break;
			}
			case(LayerType::BackHair):
			{
				std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);
				int TextureIndex = 1 + (this->HairStyle * 40) + (this->HairCol * 4);
				float idepth = depth;
				int xpos = x;
				if (this->direction == 1 || this->direction == 3)
				{
					idepth -= ep * 2;
					TextureIndex += 3;
				}

				D3DXVECTOR3* Pos = new D3DXVECTOR3(xpos - offsetpos.first + this->xoffset, y - offsetpos.second + this->yoffset, idepth - layerinfo.depth);
				D3DXVECTOR3 * Center = new D3DXVECTOR3(0, 0, 0);
				if (this->Stance == PlayerStance::BowAttacking)
				{
					if ((this->direction == 1 || this->direction == 3))
					{
						Pos->x -= 2;
						Pos->y +=1;
					}
				}
				if (this->Stance == PlayerStance::BluntAttacking)
				{
					if (this->frame_ID == 1 && (this->direction == 1 || this->direction == 3))
					{
						Pos->y -= 2;
					}
				}
				_Sprite->SetTransform(&mat);
				_Sprite->Draw(_game->resource->CreateTexture(layerinfo.file - this->Gender, TextureIndex, true).Texture.get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
				_Sprite->SetTransform(originalTransform);
				delete Pos;
				delete Center;
				break;
			}
			case(LayerType::FrontHair):
			{
				if (this->direction == 2 || this->direction == 0)
				{
					std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);

					int TextureIndex = 2 + (this->HairStyle * 40) + (this->HairCol * 4);

					D3DXVECTOR3* Pos = new D3DXVECTOR3(x - offsetpos.first + this->xoffset, y - offsetpos.second + this->yoffset, depth - layerinfo.depth);
					D3DXVECTOR3 * Center = new D3DXVECTOR3(0, 0, 0);
					if (this->Stance == PlayerStance::BowAttacking)
					{
						if ((this->direction == 1 || this->direction == 3))
						{
							Pos->x -= 2;
							Pos->y += 1;
						}
					}
					if (this->Stance == PlayerStance::BluntAttacking)
					{
						if (this->frame_ID == 1 && (this->direction == 1 || this->direction == 3))
						{
							Pos->y -= 2;
						}
					}
					_Sprite->SetTransform(&mat);
					_Sprite->Draw(_game->resource->CreateTexture(layerinfo.file - this->Gender, TextureIndex, true).Texture.get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
					_Sprite->SetTransform(originalTransform);

					delete Pos;
					delete Center;
				}
				break;
			}
			case(LayerType::Weapon):
			{
				std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);
				float newdepth = depth;
				int TextureIndex = Addint + 1 + IndexOffSet + this->frame_ID + (this->WeaponID * 100);
				D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
				if (this->direction == 0 || this->direction == 2)
				{
					if (this->Stance == PlayerStance::BluntAttacking)
					{
						if (this->frame_ID == 1)
						{
							newdepth -= ep * 1;
							D3DXVECTOR3* Posx = new D3DXVECTOR3(x - offsetpos.first + this->xoffset, y + this->yoffset - offsetpos.second, newdepth - layerinfo.depth);
							_Sprite->Draw(_game->resource->CreateTexture(layerinfo.file - this->Gender, Addint + 1 + IndexOffSet  + (this->WeaponID * 100) +4, true).Texture.get(), NULL, Center, Posx, D3DCOLOR_ARGB(255, 255, 255, 255));
							delete Posx;
						}
					}
					if (this->Stance == PlayerStance::BowAttacking)
					{
						newdepth -= ep * 1;
					}
				}

				D3DXVECTOR3* Pos = new D3DXVECTOR3(x - offsetpos.first + this->xoffset, y - offsetpos.second + this->yoffset, newdepth - layerinfo.depth);

				if (this->Stance != PlayerStance::ChairSitting && this->Stance != PlayerStance::GroundSitting)
				{
					_Sprite->Draw(_game->resource->CreateTexture(layerinfo.file - this->Gender, TextureIndex, true).Texture.get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
				}

				delete Pos;
				delete Center;
				break;
			}
			case(LayerType::Shield):
			{
				std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);
				if (this->ShieldID >= 0)
				{
					if (ShieldIsWing)
					{
						std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);

						int ShieldIndex = 0;
						if (this->Stance == PlayerStance::Spelling)
						{
							ShieldIndex--;
						}
						if (this->direction == 3 || this->direction == 1)
						{
							ShieldIndex+=1;
						}
						if (this->Stance == PlayerStance::BluntAttacking || this->Stance == PlayerStance::BowAttacking)
						{
							if (this->frame_ID == 1)
							{
								ShieldIndex += 1;
							}
							ShieldIndex ++;
						}
						float newdepth = depth;
						if (this->direction == 1 || this->direction == 3)
						{
							newdepth -= ep * 2;
						}
						int TextureIndex = 1 + ShieldIndex + (this->ShieldID * 50);


						D3DXVECTOR3 * Pos = new D3DXVECTOR3(x - offsetpos.first + this->xoffset, y - offsetpos.second + this->yoffset, newdepth - layerinfo.depth);
						D3DXVECTOR3 * Center = new D3DXVECTOR3(0, 0, 0);

						_Sprite->Draw(_game->resource->CreateTexture(layerinfo.file - this->Gender, TextureIndex, true).Texture.get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

						delete Pos;
						delete Center;
					}
					else
					{
						std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);

						float newdepth = depth;
						{
							newdepth -= ep * 3;
						}
						int TextureIndex = Addint + 1 + IndexOffSet + this->frame_ID + (this->ShieldID * 50);


						D3DXVECTOR3 * Pos = new D3DXVECTOR3(x - offsetpos.first + this->xoffset, y - offsetpos.second + this->yoffset + 30, newdepth - layerinfo.depth);
						D3DXVECTOR3 * Center = new D3DXVECTOR3(0, 0, 0);

						_Sprite->Draw(_game->resource->CreateTexture(layerinfo.file - this->Gender, TextureIndex, true).Texture.get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

						delete Pos;
						delete Center;
						}
				}
				break;
			}
			case(LayerType::Shoes):
			{
				std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);

				int TextureIndex = Addint + 1 + IndexOffSet + this->frame_ID + (this->ShoeID * 40);
				if (this->Stance == PlayerStance::BluntAttacking )
				{
					IndexOffSet = 2 + 8;
					Addint = 0;
					if (this->direction == 1 || this->direction == 3)
					{
						Addint = 1;
					}

					if (this->frame_ID == 0)
					{
						TextureIndex = Addint + 1 + (this->ShoeID * 40);
					}
					if (this->frame_ID == 1)
					{
						TextureIndex = Addint + 1 + IndexOffSet + (this->ShoeID * 40);
					}
				}
				if (this->Stance == PlayerStance::Spelling)
				{
					if (this->direction == 1 || this->direction == 3)
					{
						Addint = 1;
					}
					TextureIndex = Addint + 1 + (this->ShoeID * 40);
				}

				D3DXVECTOR3 * Pos = new D3DXVECTOR3(x - offsetpos.first + this->xoffset, y - offsetpos.second + this->yoffset, depth - layerinfo.depth);
				D3DXVECTOR3 * Center = new D3DXVECTOR3(0, 0, 0);
				if (this->Stance == PlayerStance::ChairSitting)
				{
					if (this->direction == 1 || this->direction == 3)
					{
						Pos->y -= 5;
						Pos->x += 2;
						Addint += 1;
					}
					TextureIndex -= 2;
				}
				if (this->Stance == PlayerStance::GroundSitting)
				{
					if (this->direction == 1 || this->direction == 3)
					{
						Pos->x += 2;
						Pos->y -= 5;
						Addint += 1;
					}
					TextureIndex -= 4;
				}

				_Sprite->Draw(_game->resource->CreateTexture(layerinfo.file - this->Gender, TextureIndex, true).Texture.get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

				delete Pos;
				delete Center;
				break;
			}
			case(LayerType::Armour):
			{

				std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);
				if (this->Stance == PlayerStance::BluntAttacking)
				{
					if (this->direction == 1 || this->direction == 3)
					{
						Addint += 3;
					}
					else
					{
						Addint += 2;
					}
				
				}
				int TextureIndex = Addint + 1 + IndexOffSet + this->frame_ID + (this->ArmorID * 50);

				D3DXVECTOR3* Pos =    new D3DXVECTOR3(x - offsetpos.first + this->xoffset, y - offsetpos.second + this->yoffset, depth - layerinfo.depth);
				D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
				if (this->Stance == PlayerStance::BowAttacking)
				{
					Pos->x += ((this->Gender % 2) * 2);
					Pos->y -= ((this->Gender % 2) * 1);
				}

				_Sprite->Draw(_game->resource->CreateTexture(layerinfo.file - this->Gender, TextureIndex, true).Texture.get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

				delete Pos;
				delete Center;
				break;
			}
			case(LayerType::Hat):
			{
				if (this->HatID >= 0)
				{
					std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, this->Stance, this->frame_ID);

					int TextureIndex =  1 + IndexOffSet + (this->HatID * 10);

					D3DXVECTOR3 * Pos = new D3DXVECTOR3(x - offsetpos.first + this->xoffset, y - offsetpos.second + this->yoffset, depth - layerinfo.depth);
					D3DXVECTOR3 * Center = new D3DXVECTOR3(0, 0, 0);

					//Fuck hats
					//_Sprite->Draw(_game->resource->CreateTexture(layerinfo.file - this->Gender, TextureIndex, true).Texture.get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

					delete Pos;
					delete Center;
				}
				break;
			}
		}

	}

	_Sprite->SetTransform(originalTransform);
	delete position;
	delete Scale;
	delete ScaleCntre;
	delete originalTransform;
}
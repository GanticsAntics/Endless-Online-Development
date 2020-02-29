#include "..\..\stdafx.h"
#include "..\..\game.h"

std::shared_ptr<sf::Texture> CharacterStandTexture;
std::shared_ptr<sf::Texture> CharacterWalkTexture;
std::shared_ptr<sf::Texture> CharacterAttackBluntTexture;
std::shared_ptr<sf::Texture> CharacterSpellTexture;
std::shared_ptr<sf::Texture> CharacterSitChairTexture;
std::shared_ptr<sf::Texture> CharacterSitGroundTexture;
std::shared_ptr<sf::Texture> CharacterAttackBowTexture;
std::shared_ptr<sf::Texture> CharacterEmoteTexture;
int PPdollDrawWidth = 200;
int PPdollDrawHeight = 180;
void CharacterModel::InitializeModel(Game* p_game)
{
	this->xoffset = 0;
	this->yoffset = 0;
	this->m_game = p_game;
	CharacterStandTexture = this->m_game->ResourceManager->CreateTexture(8, 1, true)._Texture;
	CharacterWalkTexture = this->m_game->ResourceManager->CreateTexture(8, 2, true)._Texture;
	CharacterAttackBluntTexture = this->m_game->ResourceManager->CreateTexture(8, 3, true)._Texture;
	CharacterSpellTexture = this->m_game->ResourceManager->CreateTexture(8, 4, true)._Texture;
	CharacterSitChairTexture = this->m_game->ResourceManager->CreateTexture(8, 5, true)._Texture;
	CharacterSitGroundTexture = this->m_game->ResourceManager->CreateTexture(8, 6, true)._Texture;
	CharacterAttackBowTexture = this->m_game->ResourceManager->CreateTexture(8, 7, true)._Texture;
	CharacterEmoteTexture = this->m_game->ResourceManager->CreateTexture(8, 8, true)._Texture;
	this->SetCharacter(this->Gender, this->HairStyle, this->HairCol, this->SkinCol, this->direction);

	this->tex = new sf::RenderTexture();
	this->spr = new sf::Sprite();
	PaperdollTextureTargets = std::unique_ptr<sf::RenderTexture>(tex);
	PaperdollSpriteTargets = std::unique_ptr<sf::Sprite>(spr);
	PaperdollTextureTargets->create(PPdollDrawWidth, PPdollDrawHeight);
	PaperdollTextureTargets->clear(sf::Color::Blue);

}

void CharacterModel::SetCharacter(unsigned char _Gender,unsigned char  _HairStyle,unsigned char  _HairCol,unsigned char  _SkinCol,unsigned char  _direction, int _armorid, int _weaponid, int _shoeid, int _hatid, int _shieldid)
{
	this->Gender = _Gender;
	this->HairStyle = _HairStyle;
	this->HairCol = _HairCol;
	this->SkinCol = _SkinCol;
	this->direction = _direction;
	this->Stance = PlayerStance::Standing;

	this->ShieldID = _shieldid;
	this->ArmorID = _armorid;
	this->WeaponID = _weaponid;
	this->ShoeID = _shoeid;
	this->HatID = _hatid;

	this->SrcRect = RECT();
	this->SrcRect.top = 0 + (58 *this->SkinCol);
	this->SrcRect.bottom = this->SrcRect.top + 58;
	this->SrcRect.left = 0 + (this->Gender * 35) + (18*(this->direction % 2)) + (this->Gender % 2);
	this->SrcRect.right = this->SrcRect.left + 18;
	//this->PrerenderPaperdoll();
}
enum LayerType
{
	BackHair,
	Skin,
	Weapon,
	Shield,
	Hat,
	Shoes,
	Armour,
	FrontHair
};
struct LayerInfo
{
	LayerType Layer_Type;
	int file;
	int StandXOff;	int StandYOff;
	int Walk1XOff;	int Walk1YOff;
	int Walk2XOff;	int Walk2YOff;
	int Walk3XOff;	int Walk3YOff;
	int Walk4XOff;	int Walk4YOff;
	int BluntAttack1XOff;	int BluntAttack1YOff;
	int BluntAttack2XOff;	int BluntAttack2YOff;
	int Spell1XOff;	int Spell1YOff;
	int RangeAttack1XOff;	int RangeAttack1YOff;
	int GroundSitXOff;	int GroundSitYOff;
	int ChairSitXOff;	int ChairSitYOff;
	float depth;
};

void CharacterModel::AlignCharacter(PlayerStance m_stance, int FrameID, int m_Direction)
{
	int spritesheetx = 0;
	
	switch (m_stance)
	{
		case(PlayerStance::Standing):
		{
			spritesheetx = 72;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (58 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 58;
			this->SrcRect.left = (18 * FrameID)+ (this->Gender * 36) + (18 * (m_Direction % 2));
			this->SrcRect.right = this->SrcRect.left + 18;
			break;
		}
		case(PlayerStance::Walking):
		{
			//Note : I had to add a pixel for the male walk animations (when direction % 2 = 1) due to the sprite sheet not being perfect..
			spritesheetx = 416;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (61 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 61;
			this->SrcRect.left = (26 * FrameID) + (this->Gender * 208) + ((104)* (m_Direction % 2));
			this->SrcRect.right = this->SrcRect.left + 26;
			break;
		}
		case(PlayerStance::BluntAttacking):
		{
			spritesheetx = 192;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (58 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 58;
			this->SrcRect.left = (24 * FrameID) + (this->Gender * 96) + (48 * (m_Direction % 2));
			this->SrcRect.right = this->SrcRect.left + 24;
			break;
		}
		case(PlayerStance::Spelling):
		{
			spritesheetx = 72;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (62 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 62;
			this->SrcRect.left = (18 * FrameID) + (this->Gender * 36) + (18 * (m_Direction % 2));
			this->SrcRect.right = this->SrcRect.left + 18;
			break;
		}
		case(PlayerStance::ChairSitting):
		{
			spritesheetx = 96;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (52 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 52;
			this->SrcRect.left = (24 * FrameID) + (this->Gender * 48) + (24 * (m_Direction % 2));
			this->SrcRect.right = this->SrcRect.left + 24;
			break;
		}
		case(PlayerStance::GroundSitting):
		{
			spritesheetx = 96;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (43 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 43;
			this->SrcRect.left = (24 * FrameID) + (this->Gender * 48) + (24 * (m_Direction % 2));
			this->SrcRect.right = this->SrcRect.left + 24;
			break;
		}
		case(PlayerStance::BowAttacking):
		{
			spritesheetx = 100;
			this->SrcRect = RECT();
			this->SrcRect.top = 0 + (58 * this->SkinCol);
			this->SrcRect.bottom = this->SrcRect.top + 58;
			this->SrcRect.left = (25 * FrameID) + (this->Gender * 50) + (25 * (m_Direction % 2));
			this->SrcRect.right = this->SrcRect.left + 25;
			break;
		}
	}

}

constexpr float ep = 0.0001f;  // gap between depth of each tile on a layer
constexpr float epi = 0.00001f; // gap between each interleaved layer
///All of the equipment alignments are sourced in this table and based on the above struct.
static constexpr LayerInfo layer_info[8] = {
						//File   Stand,  Walk1,   Walk2    Walk3,   Walk4,    BluntAttack1, BluntAttack2, Spell,   Bow,    GroundSit,   ChairSit	Depth
	{ LayerType::BackHair  ,10,   6,12,  6,12,    6,12,    6,12,    6,12,		  6,12,		  10,11,       6,12,    11,11,    1,-4,		 0,-4,		ep * 2 }, // BackHair
	{ LayerType::Skin      , 8,   0,0,   -4,-1,   -4,-1,   -4,-1,   -4,-1,		  -4,0,		  -4,0,       0,-4,    -12,1,    0,18,		 0,18,		ep * 2 }, // Skin
	{ LayerType::Weapon    ,18,  32,20,  32,20,   32,20,   32,20,   32,20,		  37,19,	  37,19,	  32,20,   42,16,   0,0,		 32,20,		ep * 1 }, // Weapon
	{ LayerType::Shield    ,20,  10,-15, 10,-15,  10,-15,  10,-15,  10,-15,		  10,-15,	 10,-15,	  10,-15,   14,-15, 6,-32,		 6,-32,	ep * 4 }, // Shield
	{ LayerType::Hat       ,16,   4,8,  4,13,    4,13,    4,13,    4,13,		  4,13,		  4,13,		  4,13,    4,13,	4,13,		 4,13,		ep * 3 }, // Hat
	{ LayerType::Shoes     ,12,   8,-37, 8,-36,  8,-36,    8,-36,   8,-36,		  8,-37,	  10,-37,	  8,-37,   15,-38,   4,-39,		 4, -50,	ep * 3 }, // Shoes
	{ LayerType::Armour    ,14,   8,12,  8,13,    8,13,    8,13,    8,13,		  8,12,		  10,11,	  8,12,    16,11,   3,2,	     3, 2,		ep * 3 }, // Armor
	{ LayerType::FrontHair ,10,   6,12,  6,12,    6,12,    6,12,    6,12,		  6,12,		  10,7,		  6,12,    9,12,    1,-4,		 1,-4,		ep * 3 }, // FrontHair
};

static constexpr int ShieldIDs[] = { 9, 10 , 13, 14, 15, 17, 18 };
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

void CharacterModel::Render(int x, int y, float depth, sf::Color m_Color)
{
	int p_FrameID = this->ConvertStanceToFrameID(this->Stance, this->frame_ID);

	bool ShieldIsWing = false;
	for (int i = 0; i < size(ShieldIDs); i++)
	{
		if (ShieldIDs[i] == ShieldID)
		{
			ShieldIsWing = true;
			break;
		}
	}


	if (this->direction == 0 || this->direction == 2)
	{
		this->PaperdollTextureTargets->clear(sf::Color::Transparent);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][0].Sprite_Backhair);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][0].Sprite_Weapon);
		if (ShieldIsWing)
		{
			PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][0].Sprite_Shield);
		}
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][0].Sprite_Skin);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][0].Sprite_Boot);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][0].Sprite_Armor);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][0].SpriteFinalFontHair);
		if (p_FrameID == 5)
		{
			PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][0].Sprite_Weapon);
		}
		PaperdollTextureTargets->display();
		PaperdollSpriteTargets->setTexture(PaperdollTextureTargets->getTexture());
	}
	else
	{
		this->PaperdollTextureTargets->clear(sf::Color::Transparent);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][1].Sprite_Weapon);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][1].Sprite_Skin);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][1].Sprite_Boot);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][1].Sprite_Armor);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][1].SpriteFinalFontHair);
		PaperdollTextureTargets->draw(this->FrameEntries[p_FrameID][1].Sprite_Shield);
		PaperdollTextureTargets->display();
		PaperdollSpriteTargets->setTexture(PaperdollTextureTargets->getTexture());
	}

	int AddY = 0;
	int AddX = 0;
	if (p_FrameID == 9)
	{
		AddY = 7;
		AddX = 3;
	}
	bool FlipTexture = false;
	if (this->direction == 1 || this->direction == 2)
	{
		FlipTexture = true;
	}
	if (FlipTexture)
	{
		this->m_game->Draw(&this->PaperdollSpriteTargets, &this->PaperdollTextureTargets, x - 43 - AddX + this->xoffset - (PPdollDrawWidth / 2), y - 30 + AddY + this->yoffset, m_Color, 0, 0, -1, -1, sf::Vector2f(-1, 1), depth);
	}
	else
	{
		this->m_game->Draw(&this->PaperdollSpriteTargets,&this->PaperdollTextureTargets, x - 43 - AddX + this->xoffset, y + AddY - 30 + this->yoffset, m_Color, 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
	}

}
void CharacterModel::DrawToTexture(int _FrameID, int m_direction)
{	
	PlayerStance m_Stance = (PlayerStance)this->ConvertFrameIDToStance(_FrameID).x;
	int m_AnimID = this->ConvertFrameIDToStance(_FrameID).y;
	int depth = 1;
	int x = 40;
	int y = 30;
	this->AlignCharacter(m_Stance, m_AnimID, m_direction);
	int IndexOffSet = 0;
	if (m_Stance == PlayerStance::Standing) { IndexOffSet = 0 + ((m_direction == 1 || m_direction == 3) ? 1 : 0); }
	else if (m_Stance == PlayerStance::Walking) { IndexOffSet = 2 + ((m_direction == 1 || m_direction == 3) ? 4 : 0); }
	else if (m_Stance == PlayerStance::Spelling) { IndexOffSet = 10 + ((m_direction == 1 || m_direction == 3) ? 1 : 0); }
	else if (m_Stance == PlayerStance::BluntAttacking) { IndexOffSet = 12 + ((m_direction == 1 || m_direction == 3) ? 2 : 0); }
	else if (m_Stance == PlayerStance::ChairSitting) { IndexOffSet = 16 + ((m_direction == 1 || m_direction == 3) ? 1 : 0); }
	else if (m_Stance == PlayerStance::GroundSitting) { IndexOffSet = 18 + ((m_direction == 1 || m_direction == 3) ? 1 : 0); }
	else if (m_Stance == PlayerStance::BowAttacking) { IndexOffSet = 20 + ((m_direction == 1 || m_direction == 3) ? 1 : 0); }
	bool FlipTexture = false;
	if (m_direction == 1 || m_direction == 2)
	{
		FlipTexture = true;
	}
	sf::Vector2f Scale = sf::Vector2f(1 - (FlipTexture * 2), 1);
	bool ShieldIsWing = false;
	for (int i = 0; i < size(ShieldIDs); i++)
	{
		if (ShieldIDs[i] == ShieldID)
		{
			ShieldIsWing = true;
			break;
		}
	}

	int RenderX = 0;
	int RenderY = 0;
	float RenderDepth = 0;
	int ScaleX = x + ((18) / 2);

	for (int itemlayer = 0; itemlayer < 8; itemlayer++)
	{
		LayerInfo layerinfo = layer_info[itemlayer];
		std::pair<int, int> offsetpos = RetrieveOffset(itemlayer, m_Stance, m_AnimID);
		RenderX = x - offsetpos.first ;
		RenderY = y - offsetpos.second;
		RenderDepth = depth - layerinfo.depth;
		switch (layerinfo.Layer_Type)
		{
			case(LayerType::Skin):
			{
				RenderX = x + offsetpos.first - (_FrameID > 0 ? (this->Gender * 1) : 0);
				RenderY = y + offsetpos.second + ((this->Gender * 1));
				if (this->Gender == 1)
				{
					if (_FrameID == 6)
					{
						RenderY++;
						RenderX += 2;
					}
					if (_FrameID == 8)
					{
						RenderY--;
						RenderX += 2;
					}
					if (m_direction == 1)
					{
						if (_FrameID > 0 && _FrameID < 5)
						{
							RenderX += 1;
						}
						if (_FrameID == 8)
						{
							RenderY += 1;
						}	
					}

				}
				FrameEntries[_FrameID][m_direction].Sprite_Skin.setPosition(sf::Vector2f(RenderX, RenderY));
				FrameEntries[_FrameID][m_direction].Sprite_Skin.setTexture(*this->m_game->ResourceManager->GetResource(8, (int)m_Stance, true)->_Texture.get());
				FrameEntries[_FrameID][m_direction].Sprite_Skin.setTextureRect(sf::IntRect(SrcRect.left, SrcRect.top, SrcRect.right - SrcRect.left, SrcRect.bottom - SrcRect.top));
				break;
			}
			case(LayerType::BackHair):
			{
				float bdepth = RenderDepth;
				int TextureIndex = 1 + (this->HairStyle * 40) + (this->HairCol * 4);
				if (m_direction == 1 || m_direction == 3)
				{
					bdepth -= ep * 2;
					TextureIndex += 3;
				}
				else
				{
					if (m_Stance == PlayerStance::BluntAttacking && m_AnimID == 1)
					{
						RenderY += 4;
					}
				}

				FrameEntries[_FrameID][m_direction].Sprite_Backhair.setPosition(sf::Vector2f(RenderX , RenderY));
				FrameEntries[_FrameID][m_direction].Sprite_Backhair.setTexture(*this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, TextureIndex, true)->_Texture.get());

				if (m_direction == 1)
				{

					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.create(100, 80);
					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.clear(sf::Color::Transparent);
					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.draw(FrameEntries[_FrameID][m_direction].Sprite_Backhair);
					
					TextureIndex = 1 + 2 + (this->HatID * 10);
					layerinfo = layer_info[LayerType::Hat];
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setPosition(sf::Vector2f(RenderX , RenderY - 4));
					FrameEntries[_FrameID][m_direction].Tx_Hat = *this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, TextureIndex, false)->_Texture.get();

					sf::Image HatImg = FrameEntries[_FrameID][m_direction].Tx_Hat.copyToImage();
					HatImg.createMaskFromColor(sf::Color(8, 0, 0, 255));
					HatImg.createMaskFromColor(sf::Color(0, 0, 0, 255));
					FrameEntries[_FrameID][m_direction].Tx_Hat.update(HatImg);

					int FronthairTextureIndex = 2 + (this->HairStyle * 40) + (this->HairCol * 4);
					sf::Image HairImg = this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, FronthairTextureIndex, false)->_Texture.get()->copyToImage();
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setTexture(FrameEntries[_FrameID][m_direction].Tx_Hat);

					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.draw(FrameEntries[_FrameID][m_direction].Sprite_Hat);
					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.display();

					HatImg = FrameEntries[_FrameID][m_direction].TextureFinalFontHair.getTexture().copyToImage();
					HatImg.createMaskFromColor(sf::Color(0, 0, 0, 255));
					FrameEntries[_FrameID][m_direction].Tx_Hat.loadFromImage(HatImg);
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setTexture(FrameEntries[_FrameID][m_direction].Tx_Hat);
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setPosition(sf::Vector2f(0, 0));
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setTextureRect(sf::IntRect(0, 0, 100, 80));

					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.clear(sf::Color::Transparent);
					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.draw(FrameEntries[_FrameID][m_direction].Sprite_Hat);

					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.display();
					FrameEntries[_FrameID][m_direction].SpriteFinalFontHair.setTexture(FrameEntries[_FrameID][m_direction].TextureFinalFontHair.getTexture());
				}
				break;
			}
			case(LayerType::FrontHair):
			{
				if (m_direction == 0)
				{
					int TextureIndex = 2 + (this->HairStyle * 40) + (this->HairCol * 4);
					FrameEntries[_FrameID][m_direction].Sprite_Fronthair.setPosition(sf::Vector2f(RenderX , RenderY));
					FrameEntries[_FrameID][m_direction].Sprite_Fronthair.setTexture(*this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, TextureIndex, true)->_Texture.get());

					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.create(100, 80);
					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.clear(sf::Color::Transparent);
					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.draw(FrameEntries[_FrameID][m_direction].Sprite_Fronthair);

					TextureIndex = 1 + 1 + (this->HatID * 10);
					layerinfo = layer_info[LayerType::Hat];
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setPosition(sf::Vector2f(RenderX, RenderY - 4));
					FrameEntries[_FrameID][m_direction].Tx_Hat = *this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, TextureIndex, false)->_Texture.get();
					
					sf::Image HatImg = FrameEntries[_FrameID][m_direction].Tx_Hat.copyToImage();
					HatImg.createMaskFromColor(sf::Color(8, 0, 0, 255));
					//HatImg.createMaskFromColor(sf::Color(0, 0, 0, 255));
					FrameEntries[_FrameID][m_direction].Tx_Hat.update(HatImg);

					FrameEntries[_FrameID][m_direction].Tx_Hat.setRepeated(true);
					int FrontHairTextureIndex = 2 + (this->HairStyle * 40) + (this->HairCol * 4);
					sf::Image HairImg = this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, TextureIndex, false)->_Texture.get()->copyToImage();

					FrameEntries[_FrameID][m_direction].Sprite_Hat.setTexture(FrameEntries[_FrameID][m_direction].Tx_Hat);
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setTextureRect(sf::IntRect(0, 0, HatImg.getSize().x, HatImg.getSize().y));

					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.setRepeated(true);
					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.draw(FrameEntries[_FrameID][m_direction].Sprite_Hat);
					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.display();

					HatImg = FrameEntries[_FrameID][m_direction].TextureFinalFontHair.getTexture().copyToImage();
					HatImg.createMaskFromColor(sf::Color(0, 0, 0, 255));
					FrameEntries[_FrameID][m_direction].Tx_Hat.loadFromImage(HatImg);
					FrameEntries[_FrameID][m_direction].Tx_Hat.setRepeated(true);
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setTexture(FrameEntries[_FrameID][m_direction].Tx_Hat);
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setPosition(sf::Vector2f(0, 0));
					FrameEntries[_FrameID][m_direction].Sprite_Hat.setTextureRect(sf::IntRect(0, -1, 100, 120));

					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.clear(sf::Color::Transparent);
					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.draw(FrameEntries[_FrameID][m_direction].Sprite_Hat);

					FrameEntries[_FrameID][m_direction].TextureFinalFontHair.display();
					FrameEntries[_FrameID][m_direction].SpriteFinalFontHair.setTexture(FrameEntries[_FrameID][m_direction].TextureFinalFontHair.getTexture());
				}
				break;
			}
			case(LayerType::Weapon):
			{
				float wdepth = RenderDepth;
				int TextureIndex = 1 + IndexOffSet + m_AnimID + (this->WeaponID * 100);
				if (m_direction == 0 || m_direction == 2)
				{
					if (m_Stance == PlayerStance::BluntAttacking)
					{
						if (m_AnimID == 1)
						{
							wdepth -= ep * 3;
						}
					}
				}
				//if (m_Stance != PlayerStance::ChairSitting && m_Stance != PlayerStance::GroundSitting)
				{
					FrameEntries[_FrameID][m_direction].Sprite_Weapon.setPosition(sf::Vector2f(RenderX, RenderY));
					FrameEntries[_FrameID][m_direction].Sprite_Weapon.setTexture(*this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, TextureIndex, true)->_Texture.get());
				}
				break;
			}
			case(LayerType::Shield):
			{
				float wdepth = RenderDepth;
				int TextureIndex = 1 + IndexOffSet + m_AnimID + (this->ShieldID * 50);
				if (ShieldIsWing)
				{
					int ShieldIndex = 0;
					RenderY -= 34;
					RenderX -= 7;
					if (m_Stance == PlayerStance::BluntAttacking || m_Stance == PlayerStance::BowAttacking || m_Stance == PlayerStance::Spelling)
					{
						ShieldIndex = 2;
						if (m_AnimID == 0 && m_Stance == PlayerStance::BluntAttacking)
						{
							ShieldIndex = 0;
						}
						if ((m_Stance == PlayerStance::BluntAttacking && m_AnimID == 1) || m_Stance == PlayerStance::BowAttacking && m_AnimID == 0)
						{
							RenderX -= 3;
						}
					}
					if ( m_direction == 1)
					{
						ShieldIndex += 1;
					}

					TextureIndex = 1 + ShieldIndex + (this->ShieldID * 50);
					if (m_direction == 0)
					{
						wdepth += ep * 3;
					}
				}
				FrameEntries[_FrameID][m_direction].Sprite_Shield.setPosition(sf::Vector2f(RenderX , RenderY));
				FrameEntries[_FrameID][m_direction].Sprite_Shield.setTexture(*this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, TextureIndex, true)->_Texture.get());
				break;
			}
			case(LayerType::Shoes):
			{
				int TextureIndex = 1 + IndexOffSet + m_AnimID + (this->ShoeID * 40);
				int NewOffset = 0;
				if (m_Stance == BluntAttacking || m_Stance == PlayerStance::BowAttacking)
				{
					NewOffset = 10;
					if ((m_Stance == BluntAttacking) && m_AnimID == 0)
					{
						NewOffset = 0;
					}
					if (m_direction == 1)
					{
						NewOffset += 1;
					}
					TextureIndex = 1 + NewOffset + (this->ShoeID * 40);
				}
				if (m_Stance == PlayerStance::Spelling)
				{
					if (m_direction == 1 || m_direction == 3)
					{
						NewOffset = 1;
					}
					TextureIndex = NewOffset + 1 + (this->ShoeID * 40);
				}
				if (m_Stance == PlayerStance::ChairSitting || m_Stance == PlayerStance::GroundSitting)
				{
					if (m_direction == 1)
					{
						RenderX += 3;
						RenderY -= 6;
					}

					if (m_Stance == PlayerStance::GroundSitting)
					{
						TextureIndex -= 4;
					}
					else
					{
						TextureIndex -= 2;
					}
				}

				FrameEntries[_FrameID][m_direction].Sprite_Boot.setPosition(sf::Vector2f(RenderX, RenderY));
				FrameEntries[_FrameID][m_direction].Sprite_Boot.setTexture(*this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, TextureIndex, true)->_Texture.get());
				break;
			}
			case(LayerType::Armour):
			{
				int TextureIndex = 1 + IndexOffSet + m_AnimID + (this->ArmorID * 50);
				if (Gender == 1)
				{
					if (_FrameID == 8)
					{
						RenderX += 1;
						if (m_direction == 1)
						{
							RenderX += 1;
						}
					}
				}
				FrameEntries[_FrameID][m_direction].Sprite_Armor.setPosition(sf::Vector2f(RenderX, RenderY));
				FrameEntries[_FrameID][m_direction].Sprite_Armor.setTexture(*this->m_game->ResourceManager->GetResource(layerinfo.file - this->Gender, TextureIndex, true)->_Texture.get());
				break;
			}
		}
	}
}
void CharacterModel::PrerenderPaperdoll()
{
	for (int i = 0; i < 11; i++)
	{
		DrawToTexture(i, 0);

		DrawToTexture(i, 1);
	}
}

void CharacterModel::Release()
{
	for (int i = 0; i < 11; i++)
	{
		for (int ii = 0; ii < 2; ii++)
		{
			//this->FrameEntries[i][ii].TextureFinalFontHair.;
		}
	}
	delete this->tex;
	delete this->spr;
}
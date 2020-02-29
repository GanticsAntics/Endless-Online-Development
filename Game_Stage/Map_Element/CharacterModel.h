#pragma once
class CharacterModel
{
private:
	sf::RenderTexture* tex;
	sf::Sprite* spr;
	template <class T, std::size_t N>
	constexpr std::size_t size(const T(&array)[N]) noexcept
	{
		return N;
	}
	
	enum AnimationFrameIDs
	{
		AF_Standing = 0,
		AF_Walk_1,
		AF_Walk_2,
		AF_Walk_3,
		AF_Walk_4,
		AF_BAttack_1,
		AF_BAttack_2,
		AF_Spell,
		AF_Bow,
		AF_GSit,
		AF_CSit
	};
	struct AnimationFrame
	{
		AnimationFrameIDs _FrameID;
		sf::Sprite Sprite_Skin;
		sf::Sprite Sprite_Boot;
		sf::Sprite Sprite_Armor;
		sf::Sprite Sprite_Shield;
		sf::Sprite Sprite_Weapon;
		sf::Texture Tx_Hat;
		sf::Sprite Sprite_Hat;

		sf::Sprite Sprite_Backhair;
		sf::Sprite Sprite_Fronthair;
		sf::RenderTexture TextureFinalFontHair;
		sf::Sprite SpriteFinalFontHair;
	};
	AnimationFrame FrameEntries[11][2];

	std::shared_ptr<sf::RenderTexture> PaperdollTextureTargets;
	std::shared_ptr<sf::Sprite>  PaperdollSpriteTargets;
	void DrawToTexture(int _FrameID, int direction);
	void PrerenderPaperdoll();

	int ConvertStanceToFrameID(int _stance, int FrameIndex)
	{
		if (_stance == 1)
		{
			return 0;
		}
		else if (_stance == 2)
		{
			return 1 + FrameIndex;
		}
		else if (_stance == 3)
		{
			return 5 + FrameIndex;
		}
		else if (_stance == 4)
		{
			return 7;
		}
		else if (_stance == 5)
		{
			return 10;
		}
		else if (_stance == 6)
		{
			return 9;
		}
		else if (_stance == 7)
		{
			return 8;
		}
	}

	sf::Vector2i ConvertFrameIDToStance(int FrameID)
	{
		int m_Stance = 0;
		int m_AnimID = 0;
		if (FrameID == 0)
		{
			m_Stance = 1;
			m_AnimID = 0;
		}
		else if (FrameID <= 4)
		{
			m_Stance = 2;
			m_AnimID = FrameID - 1;
		}
		else if (FrameID <= 6)
		{
			m_Stance = 3;
			m_AnimID = FrameID - 5;
		}
		else if (FrameID == 7)
		{
			m_Stance = 4;
			m_AnimID = 0;
		}
		else if (FrameID == 8)
		{
			m_Stance = 7;
			m_AnimID = 0;
		}
		else if (FrameID == 9)
		{
			m_Stance = 6;
			m_AnimID = 0;
		}
		else if (FrameID == 10)
		{
			m_Stance = 5;
			m_AnimID = 0;
		}
		return sf::Vector2i(m_Stance, m_AnimID);
	}

public:
	void InitializeModel(Game* m_game);
	Game* m_game;
	int ID;
	int Game_ID;
	int admin;
	int yoffset = 0;
	int xoffset = 0;
	std::string name;
	unsigned char  frame_ID;
	enum PlayerStance
	{
		Standing = 1,
		Walking = 2,
		Spelling = 4,
		BluntAttacking = 3,
		ChairSitting = 5,
		GroundSitting = 6,
		BowAttacking = 7
	};
	PlayerStance Stance;
	unsigned char  level;
	unsigned char  Gender;
	unsigned char  HairCol;
	unsigned char  HairStyle;
	unsigned char  SkinCol;
	unsigned char  direction;
	
	unsigned char  ArmorID;
	unsigned char  WeaponID;
	unsigned char  ShoeID;
	unsigned char  HatID;
	unsigned char  ShieldID;
	void UpdateAppearence() { this->PrerenderPaperdoll(); }
	RECT SrcRect;
	void SetCharacter(unsigned char  _Gender,unsigned char  _HairStyle,unsigned char  _HairCol,unsigned char  _SkinCol,unsigned char  _direction, int _armorid = -1, int _weaponid = -1, int _shoeid = -1, int _hatid = -1, int _shieldid = -1);
	void AlignCharacter(PlayerStance m_stance, int FrameID, int m_Direction);
	void Render(int x, int y, float depth, sf::Color _Color = sf::Color::White);
	//void Render(int FrameID, int x, int y, float depth, sf::Color _Color = sf::Color::White);
	void Release();
};

#ifndef CharacterModel_h
#define CharacterModel_h
class CharacterModel
{

public:
	int ID;
	int Game_ID;
	int admin;
	int yoffset = 0;
	int xoffset = 0;
	std::string name;
	byte frame_ID;
	enum PlayerStance
	{
		Standing = 0,
		Walking,
		Spelling,
		BluntAttacking,
		ChairSitting,
		GroundSitting,
		BowAttacking
	};
	PlayerStance Stance;
	byte level;
	byte Gender;
	byte HairCol;
	byte HairStyle;
	byte SkinCol;
	byte direction;
	
	byte ArmorID;
	byte WeaponID;
	byte ShoeID;
	byte HatID;
	byte ShieldID;

	RECT SrcRect;
	void Initialize(LPVOID* m_game);
	void SetCharacter(byte _Gender, byte _HairStyle, byte _HairCol, byte _SkinCol, byte _direction);
	void AlignCharacter();
	void Render(ID3DXSprite* _Sprite, int x, int y, float depth, D3DCOLOR _Color = D3DCOLOR_ARGB(255,255,255,255));
};
#endif
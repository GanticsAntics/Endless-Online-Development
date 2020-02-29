#pragma once

class Map_NPC
{
	int FindWalkDirection(int dest_x, int dest_y);
	Game* m_Game;
public:
	Map_NPC();
	int Index;
	int ID;
	int x, y, direction;
	int FrameID = 0;
	int FrameCounter = 0;
	int HP;
	int MaxHP;
	int destination_x = -1;
	int destination_y = -1;
	int moveFPS = 0;
	int yoffset = 0;
	int xoffset = 0;
	int WalkCounter = 0;

	bool isattacked = false;
	int time = 0;

	int Deathcounter = 0;
	std::vector<unsigned char> Damage;

	void NPCKill();
	enum NPC_Stance
	{
		Standing,
		Walking,
		Attacking,
		Dead
	};
	//sf::Color::White Color;
	NPC_Stance Stance;
	void Initialize(LPVOID* m_game);
	void SetStance(NPC_Stance m_Stance);
	void MoveNPC(int FPS, int DestX,int DestY);
	void DealDamage(short HpLeft, int damage);
	void Update(int FPS);
	void Render(sf::Sprite* _Sprite, int x, int y, float depth, sf::Color m_color = sf::Color::White );
	~Map_NPC();
};


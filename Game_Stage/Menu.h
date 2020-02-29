#pragma once
#include "..\World.h"
#include "Map_Element/CharacterModel.h"
#include "..\Packet_Handler\Send\SLogin.h"
#include "..\Packet_Handler\Send\SCharacter.h"
#include "..\Packet_Handler\Send\SAccount.h"
#include "..\Packet_Handler\Send\SWelcome.h"
class Menu
{
	Game* m_game;
public:

	
	Button* BT_CC_Login1;
	Button* BT_CC_Delete1;
	
	Button* BT_CC_Login2;
	Button* BT_CC_Delete2;
	
	Button* BT_CC_Login3;
	Button* BT_CC_Delete3;

	Button* BT_CreateAccount;
	Button* BT_PlayGame;
	Button* BT_ViewCredits;
	Button* BT_ExitGame;

	Button* BT_CreateCharOK;
	Button* BT_CreateCharCancel;

	Button* BT_ChangePassOK;
	Button* BT_ChangePassCancel;
	Textbox* TB_MyAccNme;
	Textbox* TB_MyPass;
	Textbox* TB_MyNewPass1;
	Textbox* TB_MyNewPass2;

	Button* BT_LGPlayGame;
	Button* BT_LGCancel;
	Textbox* TB_AccNme;
	Textbox* TB_PassWrd;
	Textbox* TB_CreateChar;

	Button* BT_CAAccNme;
	Textbox* TB_CAAccNme;
	Button* BT_CAPassWrdOne;
	Textbox* TB_CAPassWrdOne;
	Button* BT_CAPassWrdTwo;
	Textbox* TB_CAPassWrdTwo;
	Button* BT_CAName;
	Textbox* TB_CAName;
	Button* BT_CACountry;
	Textbox* TB_CACountry;
	Button* BT_CAEmail;
	Textbox* TB_CAEmail;
	Button* BT_CACreate;
	Button* BT_CACancel;

	Button* BT_LGCreateChar;
	Button* BT_LGChangePass;

	Button* BT_CC_Gender;
	Button* BT_CC_HairMod;
	Button* BT_CC_HairCol;
	Button* BT_CC_SkinCol;

	Button* BT_CCP_Gender;
	Button* BT_CCP_HairMod;
	Button* BT_CCP_HairCol;
	Button* BT_CCP_SkinCol;

	Button* BT_CS_Adminone;
	Button* BT_CS_Admintwo;
	Button* BT_CS_Adminthree;

	CharacterModel* CCModel;

	CharacterModel CSModels[3];

	CharacterModel DebugModel;

	int SelectID;
	int BgID;
	int FgID;
	int LastDeleteRequest;
	static int SrvrCreateID;
	static int SrvrDeleteID;
	static int SrvrCharID;
	int LoginFgID;
	bool deletetrue;
	World* world;
	sf::Sprite* Sprite;
	sf::Font* LoginFont;
	
	Resource_Manager::TextureData LoginBoxTex;
	Resource_Manager::TextureData BgTex;
	Resource_Manager::TextureData FgTex;
	Resource_Manager::TextureData CharacterBox;
	Resource_Manager::TextureData LoginFgTex;
	Resource_Manager::TextureData CreateCharTex;
	Resource_Manager::TextureData ChangePassTex;

	void Initialize(World* _World, sf::RenderWindow*m_Device, Game* m_game);
	void ChangePass();
	void Login();
	void TabPressed();
	void Render();
	void Update();
	void CreateAccount();
	void Release();
	void randomizeppdoll();
};
#include "..\stdafx.h"
#include "..\Game.h"

IDirect3DDevice9* Device;

Game* game;
IDirect3DTexture9* TX_TxtBox;
IDirect3DTexture9* TX_CATxtBox;
std::shared_ptr<IDirect3DTexture9> MenuButtonTexture;
std::shared_ptr<IDirect3DTexture9> LoginButtonTexture;
std::shared_ptr<IDirect3DTexture9> LoginModificationTexture;
std::shared_ptr<IDirect3DTexture9> CharacterModificationTexture;
std::shared_ptr<IDirect3DTexture9> AccountCreateTexture;
std::string WCharToCharStr(std::basic_string<wchar_t> str);
int Menu::SrvrCharID = 0;
int Menu::SrvrDeleteID = 0;
int Menu::SrvrCreateID = 0;
void Menu::Initialize(World* _world, IDirect3DDevice9Ptr m_Device, LPVOID* m_game)
{
	world = _world;
	BgID = 30 + (std::rand() % 6);
	FgID = 41 + (std::rand() % 4);
	LoginFgID = 61 + (std::rand() % 8);
	game = (Game*)m_game;
	Device = m_Device;
	D3DXCreateSprite(Device,&this->Sprite);
	this->BgTex = game->ResourceManager->CreateTexture(1,BgID,false);
	this->FgTex = game->ResourceManager->CreateTexture(1,FgID,true);
	AccountCreateTexture = game->ResourceManager->CreateTexture(1,12,true).Texture;
	MenuButtonTexture = game->ResourceManager->CreateTexture(1,13,true).Texture;
	LoginModificationTexture = game->ResourceManager->CreateTexture(1,14,true).Texture;
	LoginButtonTexture = game->ResourceManager->CreateTexture(1,15,true).Texture;
	CharacterModificationTexture = game->ResourceManager->CreateTexture(1,22,false).Texture;
	this->LoginBoxTex = game->ResourceManager->CreateTexture(1,2,false);
	this->CharacterBox = game->ResourceManager->CreateTexture(1,11,false);
	this->LoginFgTex = game->ResourceManager->CreateTexture(1,LoginFgID,true);
	this->CreateCharTex = game->ResourceManager->CreateTexture(1,20,false);
	this->ChangePassTex = game->ResourceManager->CreateTexture(1,21,false);
	

	CBitmapEx Box;
	Box.Create(141, 20);
	for (int i = 0; i < Box.GetWidth(); i++)
    {
      for (int ii = 0; ii <  Box.GetHeight(); ii++)
      {
          Box.SetPixel(i , ii, _RGB(165, 130, 105));
      }
    }
    for (int i = 0; i < Box.GetWidth(); i++ )
       {
            Box.SetPixel(i, 1, _RGB(125, 85, 33));
            Box.SetPixel(i, 19, _RGB(0,0,0));
            Box.SetPixel(i, 0, _RGB(0,0,0));
       }
   for (int i = 0; i <  Box.GetHeight(); i++)
	   {  
             Box.SetPixel(1, i, _RGB(125, 85, 33));
             Box.SetPixel(0, i, _RGB(0,0,0));
             Box.SetPixel(140, i, _RGB(0,0,0));
       }

    Box.SetPixel(0, 0, _RGB(123, 84, 24));
    Box.SetPixel(0,  Box.GetHeight() - 1, _RGB(123, 84, 24));
    Box.SetPixel(Box.GetWidth() - 1, 0, _RGB(123, 84, 24));
    Box.SetPixel(Box.GetWidth() - 1, 19,_RGB(123, 84, 24));
	
	DWORD dwBufferSize = Box.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	LPBYTE buffer;
	buffer = (LPBYTE) malloc(dwBufferSize);
	Box.Save(buffer);
	LPDIRECT3DTEXTURE9 txtbx = NULL;
	D3DXIMAGE_INFO info = D3DXIMAGE_INFO();
	HRESULT Hr = D3DXCreateTextureFromFileInMemoryEx(Device,buffer,dwBufferSize,D3DX_DEFAULT_NONPOW2 ,D3DX_DEFAULT_NONPOW2,1,D3DUSAGE_DYNAMIC ,D3DFMT_A8R8G8B8,
																 D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0,0,0,0) | D3DCOLOR_ARGB(0,222,0,0),&info,NULL,&txtbx);
	if(txtbx)
	{
	TX_TxtBox = txtbx;
	}

	CBitmapEx CABox;
	CABox.Create(242, 20);
	for (int i = 0; i < CABox.GetWidth(); i++)
    {
      for (int ii = 0; ii <  CABox.GetHeight(); ii++)
      {
          CABox.SetPixel(i , ii, _RGB(165, 130, 105));
      }
    }
    for (int i = 0; i < CABox.GetWidth(); i++ )
       {
            CABox.SetPixel(i, 1, _RGB(125, 85, 33));
            CABox.SetPixel(i, 19, _RGB(0,0,0));
            CABox.SetPixel(i, 0, _RGB(0,0,0));
       }
   for (int i = 0; i <  CABox.GetHeight(); i++)
	   {  
             CABox.SetPixel(1, i, _RGB(125, 85, 33));
             CABox.SetPixel(0, i, _RGB(0,0,0));
             CABox.SetPixel(CABox.GetWidth(), i, _RGB(0,0,0));
       }

    CABox.SetPixel(0, 0, _RGB(123, 84, 24));
    CABox.SetPixel(0,  CABox.GetHeight() - 1, _RGB(123, 84, 24));
    CABox.SetPixel(CABox.GetWidth() - 1, 0, _RGB(123, 84, 24));
    CABox.SetPixel(CABox.GetWidth() - 1, 19,_RGB(123, 84, 24));
	
	DWORD cadwBufferSize = CABox.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	LPBYTE cabuffer;
	cabuffer = (LPBYTE) malloc(cadwBufferSize);
	CABox.Save(cabuffer);
	LPDIRECT3DTEXTURE9 catxtbx = NULL;
	D3DXIMAGE_INFO cainfo = D3DXIMAGE_INFO();
	HRESULT caHr = D3DXCreateTextureFromFileInMemoryEx(Device,cabuffer,cadwBufferSize,D3DX_DEFAULT_NONPOW2 ,D3DX_DEFAULT_NONPOW2,1,D3DUSAGE_DYNAMIC ,D3DFMT_A8R8G8B8,
																 D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0,0,0,0) | D3DCOLOR_ARGB(0,222,0,0),&cainfo,NULL,&catxtbx);
	if(catxtbx)
	{
	TX_CATxtBox = catxtbx;
	}


	D3DXVECTOR2 Pos;
	Pos.x = 380;
	Pos.y = 313;

	D3DXVECTOR2 Size;
	Size.x = 140;
	Size.y = 30;

	int FontSize = 14;
	D3DXCreateFont(Device,-11, 0, FW_THIN, 0, FALSE, DEFAULT_CHARSET, OUT_SCREEN_OUTLINE_PRECIS, NONANTIALIASED_QUALITY, FIXED_PITCH | FF_ROMAN, TEXT("MS Sans Serif"), &LoginFont );
	Textbox a = Textbox(Pos, Size, D3DCOLOR_ARGB(255,0,0,0), this->LoginFont, game->PLogin, 0);
	a.MaxLen = 16;
	this->TB_AccNme = world->RegisterTextBox(a);
	this->TB_AccNme->focused = true;
	Pos.x = 360;
	Pos.y = 187;
	Size.x = 140;
	Size.y = 30;
	D3DXCreateFont(Device,-11, 0, FW_THIN, 0, FALSE, DEFAULT_CHARSET, OUT_SCREEN_OUTLINE_PRECIS, NONANTIALIASED_QUALITY, FIXED_PITCH | FF_ROMAN, TEXT("MS Sans Serif"), &LoginFont );
	Textbox h = Textbox(Pos, Size,  D3DCOLOR_ARGB(185, 240, 240, 199), this->LoginFont, game->PCharacterChoose, 2);
	h.MaxLen = 16;
	this->TB_MyAccNme = world->RegisterTextBox(h);
	Pos.x = 360;
	Pos.y = 217;
	Size.x = 140;
	Size.y = 30;
	D3DXCreateFont(Device,-11, 0, FW_THIN, 0, FALSE, DEFAULT_CHARSET, OUT_SCREEN_OUTLINE_PRECIS, NONANTIALIASED_QUALITY, FIXED_PITCH | FF_ROMAN, TEXT("MS Sans Serif"), &LoginFont );
	Textbox f = Textbox(Pos, Size,  D3DCOLOR_ARGB(185, 240, 240, 199), this->LoginFont, game->PCharacterChoose, 2);
	f.hashkey = '*';
	f.MaxLen = 12;
	this->TB_MyPass = world->RegisterTextBox(f);
	Pos.x = 360;
	Pos.y = 247;
	Size.x = 140;
	Size.y = 30;
	D3DXCreateFont(Device,-11, 0, FW_THIN, 0, FALSE, DEFAULT_CHARSET, OUT_SCREEN_OUTLINE_PRECIS, NONANTIALIASED_QUALITY, FIXED_PITCH | FF_ROMAN, TEXT("MS Sans Serif"), &LoginFont );
	Textbox r = Textbox(Pos, Size,  D3DCOLOR_ARGB(185, 240, 240, 199), this->LoginFont, game->PCharacterChoose, 2);
	r.hashkey = '*';
	r.MaxLen = 12;
	this->TB_MyNewPass1 = world->RegisterTextBox(r);
	Pos.x = 360;
	Pos.y = 277;
	Size.x = 140;
	Size.y = 30;
	D3DXCreateFont(Device,-11, 0, FW_THIN, 0, FALSE, DEFAULT_CHARSET, OUT_SCREEN_OUTLINE_PRECIS, NONANTIALIASED_QUALITY, FIXED_PITCH | FF_ROMAN, TEXT("MS Sans Serif"), &LoginFont );
	Textbox w = Textbox(Pos, Size,  D3DCOLOR_ARGB(185, 240, 240, 199), this->LoginFont, game->PCharacterChoose, 2);
	w.hashkey = '*';
	w.MaxLen = 12;
	this->TB_MyNewPass2 = world->RegisterTextBox(w);
	Pos.x = 240;
	Pos.y = 184;
	Size.x = 140;
	Size.y = 30;
	D3DXCreateFont(Device,-11, 0, FW_THIN, 0, FALSE, DEFAULT_CHARSET, OUT_SCREEN_OUTLINE_PRECIS, NONANTIALIASED_QUALITY, FIXED_PITCH | FF_ROMAN, TEXT("MS Sans Serif"), &LoginFont );
	Textbox d = Textbox(Pos, Size,  D3DCOLOR_ARGB(185, 240, 240, 199), this->LoginFont, game->PCharacterChoose, 1);
	d.MaxLen = 11;
	d.SetKeyMask(Textbox::KeyType::Letter);
	this->TB_CreateChar = world->RegisterTextBox(d);

	Pos.x = 380;
	Pos.y = 348;
	Size.x = 140;
	Size.y = 30;
	D3DXCreateFont(Device,18, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"), &LoginFont );
	Textbox p = Textbox(Pos, Size, D3DCOLOR_ARGB(255,0,0,0), this->LoginFont, game->PLogin, 0);
	p.hashkey = '*';
	p.MaxLen = 12;
	this->TB_PassWrd = world->RegisterTextBox(p);

	Pos.x = 340;
	Pos.y = 80;
	Size.x = 240;
	Size.y = 30;
	D3DXCreateFont(Device,18, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"), &LoginFont );
	Textbox CATBAN = Textbox(Pos, Size, D3DCOLOR_ARGB(255,0,0,0), this->LoginFont, game->PCreateAccount, 0);
	CATBAN.MaxLen = 16;
	this->TB_CAAccNme = world->RegisterTextBox(CATBAN);

	Pos.x = 340;
	Pos.y = 130;
	Size.x = 240;
	Size.y = 30;
	D3DXCreateFont(Device,18, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"), &LoginFont );
	Textbox CAPass1 = Textbox(Pos, Size, D3DCOLOR_ARGB(255,0,0,0), this->LoginFont, game->PCreateAccount, 0);
	CAPass1.MaxLen = 12;
	CAPass1.hashkey = '*';
	this->TB_CAPassWrdOne = world->RegisterTextBox(CAPass1);

	Pos.x = 340;
	Pos.y = 180;
	Size.x = 240;
	Size.y = 30;
	D3DXCreateFont(Device,18, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"), &LoginFont );
	Textbox CAPass2 = Textbox(Pos, Size, D3DCOLOR_ARGB(255,0,0,0), this->LoginFont, game->PCreateAccount, 0);
	CAPass2.MaxLen = 12;
	CAPass2.hashkey = '*';
	this->TB_CAPassWrdTwo = world->RegisterTextBox(CAPass2);

	Pos.x = 340;
	Pos.y = 270;
	Size.x = 240;
	Size.y = 30;
	D3DXCreateFont(Device,18, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"), &LoginFont );
	Textbox CAName = Textbox(Pos, Size, D3DCOLOR_ARGB(255,0,0,0), this->LoginFont, game->PCreateAccount, 0);
	CAName.MaxLen = 64;
	CAName.SetKeyMask(Textbox::KeyType::None);
	this->TB_CAName = world->RegisterTextBox(CAName);

	Pos.x = 340;
	Pos.y = 320;
	Size.x = 240;
	Size.y = 30;
	D3DXCreateFont(Device,18, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"), &LoginFont );
	Textbox CACountry = Textbox(Pos, Size, D3DCOLOR_ARGB(255,0,0,0), this->LoginFont, game->PCreateAccount, 0);
	CACountry.MaxLen = 64;
	CACountry.SetKeyMask(Textbox::KeyType::None);
	this->TB_CACountry = world->RegisterTextBox(CACountry);

	Pos.x = 340;
	Pos.y = 370;
	Size.x = 240;
	Size.y = 30;
	D3DXCreateFont(Device,18, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Sans Serif"), &LoginFont );
	Textbox CAEmail = Textbox(Pos, Size, D3DCOLOR_ARGB(255,0,0,0), this->LoginFont, game->PCreateAccount, 0);
	CAEmail.MaxLen = 64;
	CAEmail.SetKeyMask(Textbox::KeyType::None);
	this->TB_CAEmail = world->RegisterTextBox(CAEmail);


	world->SetFocusedTextbox(this->TB_AccNme);
	this->LastDeleteRequest	= -1;
	this->BT_CreateAccount = new Button(game,30,280,0,0,180,40,false, MenuButtonTexture);
	this->BT_PlayGame = new Button(game, 30,320,0,40,180,40,false, MenuButtonTexture);
	this->BT_ViewCredits = new Button(game, 30,360,0,80,180,40,false, MenuButtonTexture);
	this->BT_ExitGame = new Button(game, 30,400,0,120,180,40,false, MenuButtonTexture);

	this->BT_LGPlayGame = new Button(game, 344,385,0,0,91,29,false, LoginButtonTexture);
	this->BT_LGCancel = new Button(game, 437,385,0,29,91,29,false, LoginButtonTexture);
	
	this->BT_LGCreateChar = new Button(game, 344,415,0,0,120,39,false, LoginModificationTexture);
	this->BT_LGChangePass = new Button(game, 344 + 122,415,0,120,120,39,false, LoginModificationTexture);

	this->BT_CreateCharOK = new Button(game, 314,323,0,116,91,28,false, LoginButtonTexture);
	this->BT_CreateCharCancel = new Button(game, 407,323,0,29,91,28,false, LoginButtonTexture);

	this->BT_ChangePassOK = new Button(game, 314,323,0,116,91,28,false, LoginButtonTexture);
	this->BT_ChangePassCancel = new Button(game, 407,323,0,29,91,28,false, LoginButtonTexture);

		
	this->BT_CC_Login1 = new Button(game, 497,94,0,58,91,28,false, LoginButtonTexture);
	this->BT_CC_Delete1 = new Button(game, 497,124,0,87,91,28,false, LoginButtonTexture);

	this->BT_CC_Login2 = new Button(game, 497,219,0,58,91,28,false, LoginButtonTexture);
	this->BT_CC_Delete2 = new Button(game, 497,249,0,87,91,28,false, LoginButtonTexture);

	this->BT_CC_Login3 = new Button(game, 497,344,0,58,91,28,false, LoginButtonTexture);
	this->BT_CC_Delete3 = new Button(game, 497,374,0,87,91,28,false, LoginButtonTexture);

	this->BT_CC_Gender = new Button(game, 352,213,184,38,21,18,false, CharacterModificationTexture);
	this->BT_CC_HairCol = new Button(game, 352,267,184,38,21,18,false, CharacterModificationTexture);

	this->BT_CS_Adminone = new Button(game, 367,50,233,39,18,17,false, CharacterModificationTexture);
	this->BT_CS_Admintwo = new Button(game, 367,175,233,39,18,17,false, CharacterModificationTexture);
	this->BT_CS_Adminthree = new Button(game, 367,300,233,39,18,17,false, CharacterModificationTexture);

	this->BT_CC_HairMod = new Button(game, 352,240,184,38,21,18,false, CharacterModificationTexture);
	this->BT_CC_SkinCol = new Button(game, 352,294,184,38,21,18,false, CharacterModificationTexture);
	
	this->BT_CCP_Gender = new Button(game, 327,212,0,38,23,19,false, CharacterModificationTexture);
	this->BT_CCP_HairCol = new Button(game, 327,266,0,0,23,19,false, CharacterModificationTexture);
	this->BT_CCP_HairMod = new Button(game, 327,239,0,19,23,19,false, CharacterModificationTexture);
	this->BT_CCP_SkinCol = new Button(game, 327,293,46,38,23,19,false, CharacterModificationTexture);

	this->BT_CAAccNme = new Button(game, this->TB_CAAccNme->position.x, this->TB_CAAccNme->position.y - 16, 0, 0, 149, 14,false, AccountCreateTexture);
	this->BT_CAPassWrdOne = new Button(game, this->TB_CAPassWrdOne->position.x, this->TB_CAPassWrdOne->position.y - 16, 0, 14, 149, 14,false, AccountCreateTexture);
	this->BT_CAPassWrdTwo = new Button(game, this->TB_CAPassWrdTwo->position.x, this->TB_CAPassWrdTwo->position.y - 18, 0, 28, 149, 16,false, AccountCreateTexture);
	this->BT_CAName = new Button(game, this->TB_CAName->position.x, this->TB_CAName->position.y - 15, 0, 44, 149, 13,false, AccountCreateTexture);
	this->BT_CACountry = new Button(game, this->TB_CACountry->position.x, this->TB_CACountry->position.y - 18, 0, 59, 149, 16,false, AccountCreateTexture);
	this->BT_CAEmail = new Button(game, this->TB_CAEmail->position.x, this->TB_CAEmail->position.y - 16, 0, 76, 149, 14,false, AccountCreateTexture);
	this->BT_CACreate = new Button(game, 340, 421, 0, 0, 120, 39,false, LoginModificationTexture);
	this->BT_CACancel = new Button(game, 340 + 119 + 5, 421, 0, 40, 120, 39,false, LoginModificationTexture);

	this->CCModel = new CharacterModel();
	this->CCModel->Initialize((LPVOID*)game);
	for(int i = 0; i < 3; i++)
	{
		this->CSModels[i] = CharacterModel();
		this->CSModels[i].Initialize((LPVOID*)game);
	}
	this->deletetrue = false;
	this->LastDeleteRequest = -1;
};

void Menu::TabPressed()
{
	if(game->Stage == Game::PLogin)
	{
		if(this->TB_AccNme->focused)
		{
			world->SetFocusedTextbox(this->TB_AccNme);
			this->TB_AccNme->focused = false;
			this->TB_PassWrd->focused = true;
		}
		else
		{
			world->SetFocusedTextbox(this->TB_PassWrd);
			this->TB_AccNme->focused = true;
			this->TB_PassWrd->focused = false;
		}
	}
	else if(game->Stage == Game::PCharacterChoose && game->SubStage == 2)
	{
		if(this->TB_MyAccNme->focused)
		{
			world->SetFocusedTextbox(this->TB_MyPass);
			this->TB_MyAccNme->focused = false;
			this->TB_MyPass->focused = true;
		}
		else if(this->TB_MyPass->focused)
		{
			world->SetFocusedTextbox(this->TB_MyNewPass1);
			this->TB_MyPass->focused = false;
			this->TB_MyNewPass1->focused = true;
		}
		else if(this->TB_MyNewPass1->focused)
		{
			world->SetFocusedTextbox(this->TB_MyNewPass2);
			this->TB_MyNewPass1->focused = false;
			this->TB_MyNewPass2->focused = true;
		}
		else if(this->TB_MyNewPass2->focused)
		{
			world->SetFocusedTextbox(this->TB_MyAccNme);
			this->TB_MyNewPass2->focused = false;
			this->TB_MyAccNme->focused = true;
		}
	} 
	else if(game->Stage == Game::PCreateAccount)
	{
		if(this->TB_CAAccNme->focused)
		{
			world->SetFocusedTextbox(this->TB_CAPassWrdOne);
			this->TB_CAAccNme->focused = false;
			this->TB_CAPassWrdOne->focused = true;
			this->TB_CAPassWrdTwo->focused = false;
			this->TB_CAName->focused = false;
			this->TB_CACountry->focused = false;
			this->TB_CAEmail->focused = false;
		} 
		else if(this->TB_CAPassWrdOne->focused)
		{
			world->SetFocusedTextbox(this->TB_CAPassWrdTwo);
			this->TB_CAAccNme->focused = false;
			this->TB_CAPassWrdOne->focused = false;
			this->TB_CAPassWrdTwo->focused = true;
			this->TB_CAName->focused = false;
			this->TB_CACountry->focused = false;
			this->TB_CAEmail->focused = false;
		}
		else if(this->TB_CAPassWrdTwo->focused)
		{
			world->SetFocusedTextbox(this->TB_CAName);
			this->TB_CAAccNme->focused = false;
			this->TB_CAPassWrdOne->focused = false;
			this->TB_CAPassWrdTwo->focused = false;
			this->TB_CAName->focused = true;
			this->TB_CACountry->focused = false;
			this->TB_CAEmail->focused = false;
		}
		else if(this->TB_CAName->focused)
		{
			world->SetFocusedTextbox(this->TB_CACountry);
			this->TB_CAAccNme->focused = false;
			this->TB_CAPassWrdOne->focused = false;
			this->TB_CAPassWrdTwo->focused = false;
			this->TB_CAName->focused = false;
			this->TB_CACountry->focused = true;
			this->TB_CAEmail->focused = false;
		}
		else if(this->TB_CACountry->focused)
		{
			world->SetFocusedTextbox(this->TB_CAEmail);
			this->TB_CAAccNme->focused = false;
			this->TB_CAPassWrdOne->focused = false;
			this->TB_CAPassWrdTwo->focused = false;
			this->TB_CAName->focused = false;
			this->TB_CACountry->focused = false;
			this->TB_CAEmail->focused = true;
		}
		else if(this->TB_CAEmail->focused)
		{
			world->SetFocusedTextbox(this->TB_CAAccNme);
			this->TB_CAAccNme->focused = true;
			this->TB_CAPassWrdOne->focused = false;
			this->TB_CAPassWrdTwo->focused = false;
			this->TB_CAName->focused = false;
			this->TB_CACountry->focused = false;
			this->TB_CAEmail->focused = false;
		}
	}
}

void Menu::Update()
{
	if(LastDeleteRequest > -1 && game->MsgID == 1)
	{
		SCharacter::DeletePlayer(game->world->connection->ClientStream,LastDeleteRequest,(LPVOID*)this);
		LastDeleteRequest = -1;
		game->MsgID = 0;
	}

	if(game->Stage == 0 || game->Stage == 1||game->Stage == 3)
	{
			this->BT_CreateAccount->Update(game->MouseX, game->MouseY, game->MousePressed);
			this->BT_PlayGame->Update(game->MouseX, game->MouseY, game->MousePressed);
			this->BT_ViewCredits->Update(game->MouseX, game->MouseY, game->MousePressed);
			this->BT_ExitGame->Update(game->MouseX, game->MouseY, game->MousePressed);

			if(this->BT_CreateAccount->MouseClickedOnElement())
			{
				world->SetFocusedTextbox(this->TB_CAAccNme);
				this->TB_CAAccNme->Reset();
				this->TB_CAPassWrdOne->Reset();
				this->TB_CAPassWrdTwo->Reset();
				this->TB_CAName->Reset();
				this->TB_CACountry->Reset();
				this->TB_CAEmail->Reset();
				if(!World::Connected)
				{
					this->SelectID = 2;
					game->world->RawPacketCount = 0;
					this->world->CreateConnection();
				}
				else
				{
					this->SelectID = 0;
					game->Stage = game->PCreateAccount;
				}
				this->BT_CreateAccount->Deactivate();
			}
			else if(this->BT_PlayGame->MouseClickedOnElement())
			{
			world->SetFocusedTextbox(this->TB_PassWrd);
			this->TB_AccNme->focused = true;
			this->TB_PassWrd->focused = false;
			world->MassTextBoxReset();
			
			if(!World::Connected)
			{
			this->SelectID = 1;
			this->world->CreateConnection();
			}
			else
			{
				this->SelectID = 0;
				game->Stage = game->PLogin;
			}
			this->BT_PlayGame->Deactivate();
			}
			else if(this->BT_ViewCredits->MouseClickedOnElement())
			{
				game->Stage = game->PViewCredits;
				this->BT_ViewCredits->Deactivate();
			}
			else if(this->BT_ExitGame->MouseClickedOnElement())
			{
				PostQuitMessage(0);
			}
	}

	switch(game->Stage)
	{
	
	case(game->PMenu):
		{
			game->SubStage = 0;
			break;
		};
	case(game->PLogin):
		{
			if(world->GetFocusedTextbox() != this->TB_AccNme && world->GetFocusedTextbox() != this->TB_PassWrd)
			{
				world->SetFocusedTextbox(this->TB_AccNme);
			}
			this->BT_LGPlayGame->Update(game->MouseX, game->MouseY, game->MousePressed);
			if(BT_LGPlayGame->MouseClickedOnElement() && game->MousePressed)
			{
				Login();
			}
			this->BT_LGCancel->Update(game->MouseX, game->MouseY, game->MousePressed);
			if(this->TB_AccNme->CheckCollision(game->MouseX,game->MouseY))
			{
				if(game->MousePressed)
				{
					world->SetFocusedTextbox(this->TB_AccNme);
					this->TB_AccNme->focused = true;
					this->TB_PassWrd->focused = false;
				}
			}
			else if(this->TB_PassWrd->CheckCollision(game->MouseX,game->MouseY))
			{
				if(game->MousePressed)
				{
				    world->SetFocusedTextbox(this->TB_PassWrd);
					this->TB_AccNme->focused = false;
					this->TB_PassWrd->focused = true;
				}
			}
			if(this->BT_LGCancel->MouseClickedOnElement())
			{
				world->DropConnection();
				this->BT_LGCancel->Deactivate();
			}
			break;
		};
		case(game->PViewCredits):
		{
			break;
		};
		case(game->PCreateAccount):
		{
			if(world->GetFocusedTextbox()->Phase != game->PCreateAccount)
			{ world->SetFocusedTextbox(this->TB_CAAccNme); }
			this->BT_CACreate->Update(game->MouseX,game->MouseY,game->MousePressed);
			this->BT_CACancel->Update(game->MouseX,game->MouseY,game->MousePressed);
			if(BT_CACancel->MouseClickedOnElement())
			{
				world->DropConnection();
				BT_CACancel->Deactivate();
			}
			if(BT_CACreate->MouseClickedOnElement())
			{
				CreateAccount();
				BT_CACreate->Deactivate();
			}
			if(this->TB_CAAccNme->CheckCollision(game->MouseX,game->MouseY))
			{
				if(game->MousePressed)
				{
					world->SetFocusedTextbox(this->TB_CAAccNme);
					this->TB_CAAccNme->focused = true;
					this->TB_CAPassWrdOne->focused = false;
					this->TB_CAPassWrdTwo->focused = false;
					this->TB_CAName->focused = false;
					this->TB_CACountry->focused = false;
					this->TB_CAEmail->focused = false;
				}
			}
			else if(this->TB_CAPassWrdOne->CheckCollision(game->MouseX,game->MouseY))
			{
				if(game->MousePressed)
				{
					world->SetFocusedTextbox(this->TB_CAPassWrdOne);
					this->TB_CAAccNme->focused = false;
					this->TB_CAPassWrdOne->focused = true;
					this->TB_CAPassWrdTwo->focused = false;
					this->TB_CAName->focused = false;
					this->TB_CACountry->focused = false;
					this->TB_CAEmail->focused = false;
				}
			}
			else if(this->TB_CAPassWrdTwo->CheckCollision(game->MouseX,game->MouseY))
			{
				if(game->MousePressed)
				{
					world->SetFocusedTextbox(this->TB_CAPassWrdTwo);
					this->TB_CAAccNme->focused = false;
					this->TB_CAPassWrdOne->focused = false;
					this->TB_CAPassWrdTwo->focused = true;
					this->TB_CAName->focused = false;
					this->TB_CACountry->focused = false;
					this->TB_CAEmail->focused = false;
				}
			}
			else if(this->TB_CAName->CheckCollision(game->MouseX,game->MouseY))
			{
				if(game->MousePressed)
				{
					world->SetFocusedTextbox(this->TB_CAName);
					this->TB_CAAccNme->focused = false;
					this->TB_CAPassWrdOne->focused = false;
					this->TB_CAPassWrdTwo->focused = false;
					this->TB_CAName->focused = true;
					this->TB_CACountry->focused = false;
					this->TB_CAEmail->focused = false;
				}
			}
			else if(this->TB_CACountry->CheckCollision(game->MouseX,game->MouseY))
			{
				if(game->MousePressed)
				{
					world->SetFocusedTextbox(this->TB_CACountry);
					this->TB_CAAccNme->focused = false;
					this->TB_CAPassWrdOne->focused = false;
					this->TB_CAPassWrdTwo->focused = false;
					this->TB_CAName->focused = false;
					this->TB_CACountry->focused = true;
					this->TB_CAEmail->focused = false;
				}
			}
			else if(this->TB_CAEmail->CheckCollision(game->MouseX,game->MouseY))
			{
				if(game->MousePressed)
				{
					world->SetFocusedTextbox(this->TB_CAEmail);
					this->TB_CAAccNme->focused = false;
					this->TB_CAPassWrdOne->focused = false;
					this->TB_CAPassWrdTwo->focused = false;
					this->TB_CAName->focused = false;
					this->TB_CACountry->focused = false;
					this->TB_CAEmail->focused = true;
				}
			}
			break;
		};
		case(game->PCharacterChoose):
		{
			switch(game->SubStage)
			{
			case(0):
				{
					this->BT_LGChangePass->Update(game->MouseX, game->MouseY, game->MousePressed);
					this->BT_LGCreateChar->Update(game->MouseX, game->MouseY, game->MousePressed);
					BT_CC_Login1->Update(game->MouseX, game->MouseY, game->MousePressed);
					BT_CC_Delete1->Update(game->MouseX, game->MouseY, game->MousePressed);
					if (BT_CC_Login1->MouseClickedOnElement() && CSModels[0].name != "")
					{
						//game->SetStage(Game::GameStage::PInGame);
						World::WorldCharacterID = CSModels[0].Game_ID;
						SWelcome::LoginCharacter(world->connection->ClientStream, CSModels[0].Game_ID, (VOID*)game);
						BT_CC_Login1->Deactivate();
					}
					else if(BT_CC_Delete1->MouseClickedOnElement())
					{
						if(this->LastDeleteRequest !=0)
						{
							if(CSModels[0].name != "")
							{
								this->LastDeleteRequest = 0;
								World::ThrowMessage("Delete character","Character '" + CSModels[0].name + "' is going to be \ndeleted. Delete again to confirm.");
							}
						}
						else
						{
							SCharacter::RequestDeletePlayer(world->connection->ClientStream,0,(LPVOID*)game);
							World::ThrowMessage("Delete character","Character '" + CSModels[0].name + "' is going to be \ndeleted. Are you sure?", true);
						}
						BT_CC_Delete1->Deactivate();
					}
					BT_CC_Login2->Update(game->MouseX, game->MouseY, game->MousePressed);
					BT_CC_Delete2->Update(game->MouseX, game->MouseY, game->MousePressed);
					if (BT_CC_Login2->MouseClickedOnElement() && CSModels[1].name != "")
					{
						//game->SetStage(Game::GameStage::PInGame);
						World::WorldCharacterID = CSModels[1].Game_ID;
						SWelcome::LoginCharacter(world->connection->ClientStream, CSModels[1].Game_ID, (VOID*)game);
						BT_CC_Login2->Deactivate();
					}
					else if(BT_CC_Delete2->MouseClickedOnElement())
					{
						if(this->LastDeleteRequest !=1)
						{					
							if(CSModels[1].name != "")
							{
								this->LastDeleteRequest = 1;
								World::ThrowMessage("Delete character","Character '" + CSModels[1].name + "' is going to be \ndeleted. Delete again to confirm.");
							}
						}
						else
						{
							SCharacter::RequestDeletePlayer(world->connection->ClientStream,1,(LPVOID*)game);
							World::ThrowMessage("Delete character","Character '" + CSModels[1].name + "' is going to be \ndeleted. Are you sure?", true);
						}
						BT_CC_Delete2->Deactivate();
					}
					BT_CC_Login3->Update(game->MouseX, game->MouseY, game->MousePressed);
					BT_CC_Delete3->Update(game->MouseX, game->MouseY, game->MousePressed);
					if (BT_CC_Login3->MouseClickedOnElement() && CSModels[2].name != "")
					{
						//game->SetStage(Game::GameStage::PInGame);
						World::WorldCharacterID = CSModels[2].Game_ID;
						SWelcome::LoginCharacter(world->connection->ClientStream, CSModels[2].Game_ID, (VOID*)game);
						BT_CC_Login3->Deactivate();
					}
					else if(BT_CC_Delete3->MouseClickedOnElement())
					{
						if(this->LastDeleteRequest !=2)
						{
							if(CSModels[2].name != "")
							{
								this->LastDeleteRequest = 2;
								World::ThrowMessage("Delete character","Character '" + CSModels[2].name + "' is going to be \ndeleted. Delete again to confirm.");
							}
						}
						else
						{
							SCharacter::RequestDeletePlayer(world->connection->ClientStream,2,(LPVOID*)game);
							World::ThrowMessage("Delete character","Character '" + CSModels[2].name + "' is going to be \ndeleted. Are you sure?", true);
						}
						BT_CC_Delete3->Deactivate();
					}
					this->TB_AccNme->focused = false;
					this->TB_PassWrd->focused = false;
					this->TB_CreateChar->focused = true;
					if(this->BT_LGCreateChar->MouseClickedOnElement())
					{
						SCharacter::RequestCreatePlayer(this->world->connection->ClientStream, (LPVOID*) game);
						if(game->AccountCharacterSize < 3)
						{
							world->MassTextBoxReset();
							this->CCModel->SetCharacter(0,0,0,0,0);
							this->BT_CCP_Gender->SetFrameID(0);
							this->BT_CCP_HairCol->SetFrameID(0);
							this->BT_CCP_HairMod->SetFrameID(0);
							this->BT_CCP_SkinCol->SetFrameID(0);
							world->SetFocusedTextbox(this->TB_CreateChar);

							this->BT_LGCreateChar->Deactivate();
							this->BT_LGCreateChar->Update(0, 0, game->MousePressed);
						}
						else
						{
							//World::ThrowMessage("Request denied","You can only have 3 characters. Please \ndelete a character and try again");
						}
						this->BT_LGCreateChar->Deactivate();
					}
					if(this->BT_LGChangePass->MouseClickedOnElement())
					{
						world->MassTextBoxReset();
						world->SetFocusedTextbox(this->TB_MyAccNme);


						game->SubStage = 2;
						this->BT_LGChangePass->Deactivate();
						this->BT_LGChangePass->SetFrameID(0);  
						//this->BT_LGChangePass->Update(0, 0, game->MousePressed);
					}
					break;
				}
			case(1):
				{
					world->SetFocusedTextbox(this->TB_CreateChar);
					this->BT_CreateCharCancel->Update(game->MouseX, game->MouseY, game->MousePressed);
					this->BT_CreateCharOK->Update(game->MouseX, game->MouseY, game->MousePressed);
					this->BT_CC_Gender->Update(game->MouseX, game->MouseY, game->MousePressed);
					this->BT_CC_HairCol->Update(game->MouseX, game->MouseY, game->MousePressed);
					this->BT_CC_HairMod->Update(game->MouseX, game->MouseY, game->MousePressed);
					this->BT_CC_SkinCol->Update(game->MouseX, game->MouseY, game->MousePressed);
					if(this->BT_CreateCharCancel->MouseClickedOnElement())
					{
						game->SubStage = 0;
						this->BT_CreateCharCancel->Deactivate();
					}
					if(this->BT_CreateCharOK->MouseClickedOnElement())
					{
						char ch[260];
						char DefChar = ' ';
						WideCharToMultiByte(CP_ACP,0, this->TB_CreateChar->text.c_str(),-1, ch,260,&DefChar, NULL);
						std::string Accname(ch);
						CCModel->name = ch;
						SCharacter::CreatePlayer(this->world->connection->ClientStream, (LPVOID*) game);
						this->BT_CreateCharOK->Deactivate();
					}

					if(this->BT_CC_Gender->MouseClickedOnElement())
					{
						if(this->BT_CCP_Gender->GetFrameID() == 0)
						{ 
							this->CCModel->SetCharacter(1,this->CCModel->HairStyle,this->CCModel->HairCol,this->CCModel->SkinCol,this->CCModel->direction);
							this->BT_CCP_Gender->SetFrameID(1); 
						}
						else 
						{ 
							this->CCModel->SetCharacter(0,this->CCModel->HairStyle,this->CCModel->HairCol,this->CCModel->SkinCol,this->CCModel->direction);
							this->BT_CCP_Gender->SetFrameID(0);
						}
						this->BT_CC_Gender->Deactivate();
					}	
					else if(this->BT_CC_HairCol->MouseClickedOnElement())
					{
						if(this->BT_CCP_HairCol->GetFrameID() < 9)
						{
							this->CCModel->SetCharacter(this->CCModel->Gender,this->CCModel->HairStyle,this->CCModel->HairCol + 1,this->CCModel->SkinCol,this->CCModel->direction);
							this->BT_CCP_HairCol->SetFrameID(this->BT_CCP_HairCol->GetFrameID() + 1);
						}
						else 
						{ 
							this->CCModel->SetCharacter(this->CCModel->Gender,this->CCModel->HairStyle,0,this->CCModel->SkinCol,this->CCModel->direction);
							this->BT_CCP_HairCol->SetFrameID(0);
						}

						this->BT_CC_HairCol->Deactivate();
					}
					else if(this->BT_CC_HairMod->MouseClickedOnElement())
					{
						if(this->BT_CCP_HairMod->GetFrameID() < 19)
						{
							this->CCModel->SetCharacter(this->CCModel->Gender,this->CCModel->HairStyle + 1,this->CCModel->HairCol,this->CCModel->SkinCol,this->CCModel->direction);
							this->BT_CCP_HairMod->SetFrameID(this->BT_CCP_HairMod->GetFrameID() + 1);
						}
						else 
						{
							this->CCModel->SetCharacter(this->CCModel->Gender,0,this->CCModel->HairCol,this->CCModel->SkinCol,this->CCModel->direction);
							this->BT_CCP_HairMod->SetFrameID(0);
						}
						this->BT_CC_HairMod->Deactivate();
					}
					else if(this->BT_CC_SkinCol->MouseClickedOnElement())
					{
						if(this->BT_CCP_SkinCol->GetFrameID() < 5)
						{
							this->CCModel->SetCharacter(this->CCModel->Gender,this->CCModel->HairStyle,this->CCModel->HairCol,this->CCModel->SkinCol+1,this->CCModel->direction);
							this->BT_CCP_SkinCol->SetFrameID(this->BT_CCP_SkinCol->GetFrameID() + 1);
						}
						else 
						{ 
							this->CCModel->SetCharacter(this->CCModel->Gender,this->CCModel->HairStyle,this->CCModel->HairCol,0,this->CCModel->direction);
							this->BT_CCP_SkinCol->SetFrameID(0);
						}
						this->BT_CC_SkinCol->Deactivate();
					}
					break;
				}
				case(2):
				{
					this->BT_ChangePassCancel->Update(game->MouseX, game->MouseY, game->MousePressed);
					this->BT_ChangePassOK->Update(game->MouseX, game->MouseY, game->MousePressed);
					if(this->BT_ChangePassCancel->MouseClickedOnElement())
					{
						game->SubStage = 0;
						this->BT_ChangePassCancel->Deactivate();
					}
					if(this->BT_ChangePassOK->MouseClickedOnElement())
					{
						this->ChangePass();
						this->BT_ChangePassOK->Deactivate();
					}
					if(this->TB_MyAccNme->CheckCollision(game->MouseX,game->MouseY))
					{
						if(game->MousePressed)
						{
							world->SetFocusedTextbox(this->TB_MyAccNme);
							this->TB_MyAccNme->focused = true;
							this->TB_MyPass->focused = false;
							this->TB_MyNewPass1->focused = false;
							this->TB_MyNewPass2->focused = false;
						}
					}
					else if(this->TB_MyPass->CheckCollision(game->MouseX,game->MouseY))
					{
						if(game->MousePressed)
						{
							world->SetFocusedTextbox(this->TB_MyPass);
							this->TB_MyAccNme->focused = false;
							this->TB_MyPass->focused = true;
							this->TB_MyNewPass1->focused = false;
							this->TB_MyNewPass2->focused = false;
						}
					}
					else if(this->TB_MyNewPass1->CheckCollision(game->MouseX,game->MouseY))
					{
						if(game->MousePressed)
						{
							world->SetFocusedTextbox(this->TB_MyNewPass1);
							this->TB_MyAccNme->focused = false;
							this->TB_MyPass->focused = false;
							this->TB_MyNewPass1->focused = true;
							this->TB_MyNewPass2->focused = false;
						}
					}
					else if(this->TB_MyNewPass2->CheckCollision(game->MouseX,game->MouseY))
					{
						if(game->MousePressed)
						{
							world->SetFocusedTextbox(this->TB_MyNewPass2);
							this->TB_MyAccNme->focused = false;
							this->TB_MyPass->focused = false;
							this->TB_MyNewPass1->focused = false;
							this->TB_MyNewPass2->focused = true;
						}
					}


					break;
				}
			}
			break;
		};
	};
};

void Menu::Render()
{
	    this->Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
		game->Draw(this->Sprite,this->BgTex.Texture,1,1,D3DCOLOR_ARGB(255,255,255,255) );

		switch(game->Stage)
		{
			case(game->PMenu):
				{
					game->Draw(this->Sprite,this->FgTex.Texture,230, 480 - game->ResourceManager->GetImageInfo(1,FgID, true).Height - 10,D3DCOLOR_ARGB(255,255,255,255) );
									
					this->BT_CreateAccount->Draw(this->Sprite);
					this->BT_PlayGame->Draw(this->Sprite);
					this->BT_ViewCredits->Draw(this->Sprite);
					this->BT_ExitGame->Draw(this->Sprite);
					break;
				}
			case(game->PLogin):
				{
					game->Draw(this->Sprite,this->FgTex.Texture,230, 480 - game->ResourceManager->GetImageInfo(1,FgID, true).Height - 10,D3DCOLOR_ARGB(255,255,255,255) );		
					game->Draw(this->Sprite,this->LoginBoxTex.Texture,240, 280,D3DCOLOR_ARGB(255,255,255,255) );
					game->Draw(this->Sprite,TX_TxtBox,this->TB_AccNme->position.x - 5,this->TB_AccNme->position.y + 1,D3DCOLOR_ARGB(255,255,255,255));
					game->Draw(this->Sprite,TX_TxtBox,this->TB_PassWrd->position.x - 5,this->TB_PassWrd->position.y,D3DCOLOR_ARGB(255,255,255,255));
					this->BT_CreateAccount->Draw(this->Sprite);
					this->BT_PlayGame->Draw(this->Sprite);
					this->BT_ViewCredits->Draw(this->Sprite);
					this->BT_ExitGame->Draw(this->Sprite);

					this->BT_LGPlayGame->Draw(this->Sprite);
					this->BT_LGCancel->Draw(this->Sprite);

					break;
				}
			case(game->PViewCredits):
				{
					this->BT_CreateAccount->Draw(this->Sprite);
					this->BT_PlayGame->Draw(this->Sprite);
					this->BT_ViewCredits->Draw(this->Sprite);
					this->BT_ExitGame->Draw(this->Sprite);
					break;
				}
			case(game->PCreateAccount):
				{
					game->Draw(this->Sprite,this->LoginFgTex.Texture,30, 480 - game->ResourceManager->GetImageInfo(1,LoginFgID, true).Height - 10,D3DCOLOR_ARGB(255,255,255,255) );
					game->Draw(this->Sprite,TX_CATxtBox,this->TB_CAAccNme->position.x - 5,this->TB_CAAccNme->position.y + 1,D3DCOLOR_ARGB(255,255,255,255));
					game->Draw(this->Sprite,TX_CATxtBox,this->TB_CAPassWrdOne->position.x - 5,this->TB_CAPassWrdOne->position.y + 1,D3DCOLOR_ARGB(255,255,255,255));
					game->Draw(this->Sprite,TX_CATxtBox,this->TB_CAPassWrdTwo->position.x - 5,this->TB_CAPassWrdTwo->position.y + 1,D3DCOLOR_ARGB(255,255,255,255));
					game->Draw(this->Sprite,TX_CATxtBox,this->TB_CAName->position.x - 5,this->TB_CAName->position.y + 1,D3DCOLOR_ARGB(255,255,255,255));
					game->Draw(this->Sprite,TX_CATxtBox,this->TB_CACountry->position.x - 5,this->TB_CACountry->position.y + 1,D3DCOLOR_ARGB(255,255,255,255));
					game->Draw(this->Sprite,TX_CATxtBox,this->TB_CAEmail->position.x - 5,this->TB_CAEmail->position.y + 1,D3DCOLOR_ARGB(255,255,255,255));
					this->BT_CAAccNme->Draw(Sprite);
					this->BT_CAPassWrdOne->Draw(Sprite);
					this->BT_CAPassWrdTwo->Draw(Sprite);
					this->BT_CAName->Draw(Sprite);
					this->BT_CACountry->Draw(Sprite);
					this->BT_CAEmail->Draw(Sprite);
					this->BT_CACreate->Draw(Sprite);
					this->BT_CACancel->Draw(Sprite);

					this->TB_CAAccNme->Render(Sprite);
					this->TB_CAPassWrdOne->Render(Sprite);
					this->TB_CAPassWrdTwo->Render(Sprite);
					this->TB_CAName->Render(Sprite);
					this->TB_CACountry->Render(Sprite);
					this->TB_CAEmail->Render(Sprite);

					break;
				}
			case(game->PCharacterChoose):
				{
					game->Draw(this->Sprite,this->LoginFgTex.Texture,30, 480 - game->ResourceManager->GetImageInfo(1,LoginFgID, true).Height - 10,D3DCOLOR_ARGB(255,255,255,255) );
					game->Draw(this->Sprite,this->CharacterBox.Texture, 338, 40, D3DCOLOR_ARGB(255,255,255,255) );
					game->Draw(this->Sprite,this->CharacterBox.Texture, 338, 165, D3DCOLOR_ARGB(255,255,255,255) );
					game->Draw(this->Sprite,this->CharacterBox.Texture, 338, 289, D3DCOLOR_ARGB(255,255,255,255) );
					
					BT_CC_Login1->Draw(this->Sprite);
					BT_CC_Delete1->Draw(this->Sprite);
					BT_CC_Login2->Draw(this->Sprite);
					BT_CC_Delete2->Draw(this->Sprite);
					BT_CC_Login3->Draw(this->Sprite);
					BT_CC_Delete3->Draw(this->Sprite);
					for(int i =0; i < game->AccountCharacterSize;i++)
					{
						this->CSModels[i].Render(Sprite,400,80+(i*125), 0.1f);
					}			
					if(this->CSModels[0].admin >0)
					{
						BT_CS_Adminone->Draw(this->Sprite);
					}
					if(this->CSModels[1].admin >0)
					{
						BT_CS_Admintwo->Draw(this->Sprite);
					}
					if(this->CSModels[2].admin >0)
					{
						BT_CS_Adminthree->Draw(this->Sprite);
					}
					for(int i = 0; i < game->AccountCharacterSize;i++)
					{
						RECT rct;
						rct.left= 445;
						rct.right= rct.left + 200;
						rct.top= 67 + (i*125);
						rct.bottom= rct.top + 30;
						LoginFont->DrawTextA(this->Sprite,CSModels[i].name.c_str(),-1,&rct, DT_CENTER, D3DCOLOR_ARGB(185, 240, 240, 199));

						rct.left= 320;
						rct.right= rct.left + 108;
						rct.top= 135 + (i*125);
						rct.bottom= rct.top + 30;
						std::basic_string<char> str = "";
						char* st = new char[8];
						_itoa((BYTE)CSModels[i].level, st, 10);
						str += st;
						LoginFont->DrawTextA(this->Sprite,str.c_str(),-1,&rct, DT_CENTER,  D3DCOLOR_ARGB(185, 240, 240, 199));
					}
					
					switch(game->SubStage)
					{
					case(0):
						 {
							break;
						 }
					case(1):
						 {
							game->Draw(this->Sprite,this->CreateCharTex.Texture, 158, 129, 0.05f, D3DCOLOR_ARGB(255,255,255,255) );
							this->BT_CreateCharCancel->Draw(this->Sprite);
							this->BT_CreateCharOK->Draw(this->Sprite);
							this->BT_CC_Gender->Draw(this->Sprite);
							this->BT_CC_HairCol->Draw(this->Sprite);
							this->BT_CC_HairMod->Draw(this->Sprite);
							this->BT_CC_SkinCol->Draw(this->Sprite);

							this->BT_CCP_Gender->Draw(this->Sprite);
							this->BT_CCP_HairCol->Draw(this->Sprite);
							this->BT_CCP_HairMod->Draw(this->Sprite);
							this->BT_CCP_SkinCol->Draw(this->Sprite);

							this->CCModel->Render(Sprite,430,225,0.03f);
							break;
						 }
					case(2):
						{
							game->Draw(this->Sprite,this->ChangePassTex.Texture, 158, 129, D3DCOLOR_ARGB(255,255,255,255) );
							this->BT_ChangePassCancel->Draw(this->Sprite);
							this->BT_ChangePassOK->Draw(this->Sprite);
						}
					}


					this->BT_LGCreateChar->Draw(this->Sprite);
					this->BT_LGChangePass->Draw(this->Sprite);
					break;
				}
		}
	
		this->world->RenderTextBoxes(this->Sprite,game->Stage, game->SubStage);
		this->Sprite->End();
};

void Menu::Release()
{
	this->BgTex.Texture.reset();
}

void Menu::Login()
{
	if (this->TB_AccNme->text == L"" || this->TB_PassWrd->text == L"")
       { }
       else
		{
			char ch[260];
			char DefChar = ' ';
			WideCharToMultiByte(CP_ACP,0, this->TB_AccNme->text.c_str(),-1, ch,260,&DefChar, NULL);
			std::string Accname(ch);
			ch[260];
			DefChar = ' ';
			WideCharToMultiByte(CP_ACP,0, this->TB_PassWrd->text.c_str(),-1, ch,260,&DefChar, NULL);
			std::string Pssword(ch);
			SLogin::SendLoginRequest(game,world->connection->ClientStream, Accname, Pssword);
			this->BT_LGPlayGame->Deactivate();
		}
}

void Menu::CreateAccount()
{
	if(this->TB_CAAccNme->text.length() == 0 ||this->TB_CAPassWrdOne->text.length() == 0  || this->TB_CAPassWrdTwo->text.length() == 0  || this->TB_CAName->text.length() == 0  || this->TB_CACountry->text.length() == 0 || this->TB_CAEmail->text.length() == 0 )
	{
		World::ThrowMessage("Wrong Input", "Some of the fields are still empty. Fill in all\nthe fields and try again.");
		return;
	}
	if(this->TB_CAPassWrdOne->text != this->TB_CAPassWrdTwo->text)
	{
		World::ThrowMessage("Wrong password", "The two passwords you provided are not\nthe same, please try again.");
		return;
	}
	bool Chafound = false;
	bool Dotfound = false;
	for(int i = 0; i < this->TB_CAEmail->text.length();i++)
	{
		if(!Chafound)
		{
			if(this->TB_CAEmail->text[i] == '@')
			{
				Chafound = true;
				continue;
			}
		}
		else
		{
			if(this->TB_CAEmail->text[i] == '.')
			{
				Dotfound = true;
				break;
			}
		}
	}
	//if(!Chafound || !Dotfound)
	{
		//World::ThrowMessage("Wrong input", "Enter a valid email address.");
		//return;
	}
	SAccount::RequestAccountCreate(world->connection->ClientStream,WCharToCharStr(this->TB_CAAccNme->text),game);
	//SAccount::RequestAccountCreate(world->connection->ClientStream,WCharToCharStr(this->TB_CAAccNme->text),WCharToCharStr(this->TB_CAPassWrdOne->text),WCharToCharStr(this->TB_CAPassWrdTwo->text),WCharToCharStr(this->TB_CAName->text),WCharToCharStr(this->TB_CACountry->text),WCharToCharStr(this->TB_CAEmail->text),game);

}

void Menu::ChangePass()
{
	if(this->TB_MyNewPass1->text != this->TB_MyNewPass2->text)
	{ 
		World::ThrowMessage("Wrong password","The two passwords you provided are not \nthe same, please try again.");
		this->TB_MyNewPass1->Reset();
		this->TB_MyNewPass2->Reset();
		this->world->SetFocusedTextbox(TB_MyNewPass1);
	}
	else
	{
		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP,0, this->TB_MyAccNme->text.c_str(),-1, ch,260,&DefChar, NULL);
		std::string Accname(ch);
		ch[260];
	    DefChar = ' ';
		WideCharToMultiByte(CP_ACP,0, this->TB_MyPass->text.c_str(),-1, ch,260,&DefChar, NULL);
		std::string OldPass(ch);
		ch[260];
	    DefChar = ' ';
		WideCharToMultiByte(CP_ACP,0, this->TB_MyNewPass1->text.c_str(),-1, ch,260,&DefChar, NULL);
		std::string NewPass(ch);
	    SAccount::ChangePass(world->connection->ClientStream, Accname, OldPass, NewPass, game);
	}
}

std::string WCharToCharStr(std::basic_string<wchar_t> str)
{
		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP,0, str.c_str(),-1, ch,260,&DefChar, NULL);
		std::string ret(ch);
		return ret;
}
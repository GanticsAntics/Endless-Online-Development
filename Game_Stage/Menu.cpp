#include "..\stdafx.h"
#include "..\game.h"

sf::RenderWindow* Device;

sf::Texture* TX_TxtBox;
sf::Texture* TX_CATxtBox;
std::shared_ptr<sf::Texture> MenuButtonTexture;
std::shared_ptr<sf::Texture> LoginButtonTexture;
std::shared_ptr<sf::Texture> LoginModificationTexture;
std::shared_ptr<sf::Texture> CharacterModificationTexture;
std::shared_ptr<sf::Texture> AccountCreateTexture;

int Menu::SrvrCharID = 0;
int Menu::SrvrDeleteID = 0;
int Menu::SrvrCreateID = 0;
sf::Sprite* testsprite;
Resource_Manager::TextureData* Txbox_Texture;
void Menu::Initialize(World* _world, sf::RenderWindow*m_Device, Game* m_game)
{
	testsprite = new sf::Sprite();
	Sprite = new sf::Sprite();
	world = _world;
	BgID = 30 + (std::rand() % 6);
	FgID = 41 + (std::rand() % 4);
	LoginFgID = 61 + (std::rand() % 8);
	this->m_game = m_game;
	Device = m_Device;
	

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

	Txbox_Texture = new Resource_Manager::TextureData();
	sf::Texture* txboxtex = new sf::Texture();
	Txbox_Texture->_height = Box.GetHeight();
	Txbox_Texture->_width = Box.GetWidth();
	txboxtex->loadFromMemory(buffer, dwBufferSize);
	Txbox_Texture->_Texture = std::shared_ptr<sf::Texture>(txboxtex);
	Txbox_Texture->_Texture->setSmooth(true);
	sf::Sprite* spr = new sf::Sprite();
	spr->setTexture(*Txbox_Texture->_Texture);
	Txbox_Texture->_Sprite = std::shared_ptr<sf::Sprite>(spr);

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
	
	sf::Vector2f Pos;
	Pos.x = 380;
	Pos.y = 313;

	sf::Vector2f Size;
	Size.x = 140;
	Size.y = 30;

	int FontSize = 14;
	Textbox a = Textbox(this->m_game, Pos, Size, sf::Color::Color(0,0,0), this->LoginFont, this->m_game->PLogin, 0);
	a.MaxLen = 16;
	this->TB_AccNme = world->RegisterTextBox(a);
	this->TB_AccNme->focused = true;
	Pos.x = 360;
	Pos.y = 187;
	Size.x = 140;
	Size.y = 30;
	Textbox h = Textbox(this->m_game, Pos, Size,  sf::Color::Color(220, 200, 180, 255), this->LoginFont, this->m_game->PCharacterChoose, 2);
	h.MaxLen = 16;
	this->TB_MyAccNme = world->RegisterTextBox(h);
	Pos.x = 360;
	Pos.y = 217;
	Size.x = 140;
	Size.y = 30;
	Textbox f = Textbox(this->m_game, Pos, Size,  sf::Color::Color(220, 200, 180, 255), this->LoginFont, this->m_game->PCharacterChoose, 2);
	f.hashkey = '*';
	f.MaxLen = 12;
	this->TB_MyPass = world->RegisterTextBox(f);
	Pos.x = 360;
	Pos.y = 247;
	Size.x = 140;
	Size.y = 30;
	Textbox r = Textbox(this->m_game, Pos, Size,  sf::Color::Color(220, 200, 180, 255), this->LoginFont, this->m_game->PCharacterChoose, 2);
	r.hashkey = '*';
	r.MaxLen = 12;
	this->TB_MyNewPass1 = world->RegisterTextBox(r);
	Pos.x = 360;
	Pos.y = 277;
	Size.x = 140;
	Size.y = 30;
	Textbox w = Textbox(this->m_game, Pos, Size,  sf::Color::Color(220, 200, 180, 255), this->LoginFont, this->m_game->PCharacterChoose, 2);
	w.hashkey = '*';
	w.MaxLen = 12;
	this->TB_MyNewPass2 = world->RegisterTextBox(w);
	Pos.x = 240;
	Pos.y = 184;
	Size.x = 140;
	Size.y = 30;
	Textbox d = Textbox(this->m_game, Pos, Size,  sf::Color::Color(220, 200, 180, 255), this->LoginFont, this->m_game->PCharacterChoose, 1);
	d.MaxLen = 11;
	d.SetKeyMask(Textbox::KeyType::None);
	this->TB_CreateChar = world->RegisterTextBox(d);

	Pos.x = 380;
	Pos.y = 348;
	Size.x = 140;
	Size.y = 30;
	Textbox p = Textbox(this->m_game, Pos, Size, sf::Color::Color(0,0,0), this->LoginFont, this->m_game->PLogin, 0);
	p.hashkey = '*';
	p.MaxLen = 12;
	this->TB_PassWrd = world->RegisterTextBox(p);

	Pos.x = 340;
	Pos.y = 80;
	Size.x = 240;
	Size.y = 30;
	Textbox CATBAN = Textbox(this->m_game, Pos, Size, sf::Color::Color(0,0,0), this->LoginFont, this->m_game->PCreateAccount, 0);
	CATBAN.MaxLen = 16;
	this->TB_CAAccNme = world->RegisterTextBox(CATBAN);

	Pos.x = 340;
	Pos.y = 130;
	Size.x = 240;
	Size.y = 30;
	Textbox CAPass1 = Textbox(this->m_game, Pos, Size, sf::Color::Color(0,0,0), this->LoginFont, this->m_game->PCreateAccount, 0);
	CAPass1.MaxLen = 12;
	CAPass1.hashkey = '*';
	this->TB_CAPassWrdOne = world->RegisterTextBox(CAPass1);

	Pos.x = 340;
	Pos.y = 180;
	Size.x = 240;
	Size.y = 30;
	Textbox CAPass2 = Textbox(this->m_game, Pos, Size, sf::Color::Color(0,0,0), this->LoginFont, this->m_game->PCreateAccount, 0);
	CAPass2.MaxLen = 12;
	CAPass2.hashkey = '*';
	this->TB_CAPassWrdTwo = world->RegisterTextBox(CAPass2);

	Pos.x = 340;
	Pos.y = 270;
	Size.x = 240;
	Size.y = 30;
	Textbox CAName = Textbox(this->m_game, Pos, Size, sf::Color::Color(0,0,0), this->LoginFont, this->m_game->PCreateAccount, 0);
	CAName.MaxLen = 64;
	CAName.SetKeyMask(Textbox::KeyType::None);
	this->TB_CAName = world->RegisterTextBox(CAName);

	Pos.x = 340;
	Pos.y = 320;
	Size.x = 240;
	Size.y = 30;
	Textbox CACountry = Textbox(this->m_game, Pos, Size, sf::Color::Color(0,0,0), this->LoginFont, this->m_game->PCreateAccount, 0);
	CACountry.MaxLen = 64;
	CACountry.SetKeyMask(Textbox::KeyType::None);
	this->TB_CACountry = world->RegisterTextBox(CACountry);

	Pos.x = 340;
	Pos.y = 370;
	Size.x = 240;
	Size.y = 30;
	Textbox CAEmail = Textbox(this->m_game, Pos, Size, sf::Color::Color(0,0,0), this->LoginFont, this->m_game->PCreateAccount, 0);
	CAEmail.MaxLen = 64;
	CAEmail.SetKeyMask(Textbox::KeyType::None);
	this->TB_CAEmail = world->RegisterTextBox(CAEmail);

	
	world->SetFocusedTextbox(this->TB_AccNme);
	this->LastDeleteRequest	= -1;
	this->BT_CreateAccount = new Button(this->m_game,30,280,0,0,180,40,false, this->m_game->ResourceManager->GetResource(1, 13, true));
	this->BT_PlayGame = new Button(this->m_game, 30,320,0,40,180,40,false, this->m_game->ResourceManager->GetResource(1, 13, true));
	this->BT_ViewCredits = new Button(this->m_game, 30,360,0,80,180,40,false, this->m_game->ResourceManager->GetResource(1, 13, true));
	this->BT_ExitGame = new Button(this->m_game, 30,400,0,120,180,40,false, this->m_game->ResourceManager->GetResource(1, 13, true));

	this->BT_LGPlayGame = new Button(this->m_game, 344,385,0,0,91,29,false, this->m_game->ResourceManager->GetResource(1, 15, true));
	this->BT_LGCancel = new Button(this->m_game, 437,385,0,29,91,29,false, this->m_game->ResourceManager->GetResource(1, 15, true));
	
	this->BT_LGCreateChar = new Button(this->m_game, 344,415,0,0,120,39,false, this->m_game->ResourceManager->GetResource(1, 14, true));
	this->BT_LGChangePass = new Button(this->m_game, 344 + 122,415,0,120,120,39,false, this->m_game->ResourceManager->GetResource(1, 14, true));

	this->BT_CreateCharOK = new Button(this->m_game, 315,324,0,116,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));
	this->BT_CreateCharCancel = new Button(this->m_game, 408,324,0,29,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));

	this->BT_ChangePassOK = new Button(this->m_game, 315,324,0,116,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));
	this->BT_ChangePassCancel = new Button(this->m_game, 408,324,0,29,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));

		
	this->BT_CC_Login1 = new Button(this->m_game, 497,94,0,58,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));
	this->BT_CC_Delete1 = new Button(this->m_game, 497,124,0,87,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));

	this->BT_CC_Login2 = new Button(this->m_game, 497,219,0,58,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));
	this->BT_CC_Delete2 = new Button(this->m_game, 497,249,0,87,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));

	this->BT_CC_Login3 = new Button(this->m_game, 497,344,0,58,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));
	this->BT_CC_Delete3 = new Button(this->m_game, 497,374,0,87,91,28,false, this->m_game->ResourceManager->GetResource(1, 15, true));

	this->BT_CC_Gender = new Button(this->m_game, 352,213,184,38,21,18,false, this->m_game->ResourceManager->GetResource(1, 22, false));
	this->BT_CC_HairCol = new Button(this->m_game, 352,267,184,38,21,18,false, this->m_game->ResourceManager->GetResource(1, 22, false));

	this->BT_CS_Adminone = new Button(this->m_game, 367,50,233,39,18,17,false, this->m_game->ResourceManager->GetResource(1, 22, false));
	this->BT_CS_Admintwo = new Button(this->m_game, 367,175,233,39,18,17,false, this->m_game->ResourceManager->GetResource(1, 22, false));
	this->BT_CS_Adminthree = new Button(this->m_game, 367,300,233,39,18,17,false, this->m_game->ResourceManager->GetResource(1, 22, false));

	this->BT_CC_HairMod = new Button(this->m_game, 352,240,184,38,21,18,false, this->m_game->ResourceManager->GetResource(1, 22, false));
	this->BT_CC_SkinCol = new Button(this->m_game, 352,294,184,38,21,18,false, this->m_game->ResourceManager->GetResource(1, 22, false));
	
	this->BT_CCP_Gender = new Button(this->m_game, 327,212,0,38,23,19,false, this->m_game->ResourceManager->GetResource(1, 22, false));
	this->BT_CCP_HairCol = new Button(this->m_game, 327,266,0,0,23,19,false, this->m_game->ResourceManager->GetResource(1, 22, false));
	this->BT_CCP_HairMod = new Button(this->m_game, 327,239,0,19,23,19,false, this->m_game->ResourceManager->GetResource(1, 22, false));
	this->BT_CCP_SkinCol = new Button(this->m_game, 327,293,46,38,23,19,false, this->m_game->ResourceManager->GetResource(1, 22, false));

	this->BT_CAAccNme = new Button(this->m_game, this->TB_CAAccNme->position.x, this->TB_CAAccNme->position.y - 16, 0,0, 149, 14,false, this->m_game->ResourceManager->GetResource(1, 12, true));
	this->BT_CAPassWrdOne = new Button(this->m_game, this->TB_CAPassWrdOne->position.x, this->TB_CAPassWrdOne->position.y - 16, 0, 14, 149, 14,false, this->m_game->ResourceManager->GetResource(1, 12, true));
	this->BT_CAPassWrdTwo = new Button(this->m_game, this->TB_CAPassWrdTwo->position.x, this->TB_CAPassWrdTwo->position.y - 18, 0, 28, 149, 16,false, this->m_game->ResourceManager->GetResource(1, 12, true));
	this->BT_CAName = new Button(this->m_game, this->TB_CAName->position.x, this->TB_CAName->position.y - 15, 0, 44, 149, 13,false, this->m_game->ResourceManager->GetResource(1, 12, true));
	this->BT_CACountry = new Button(this->m_game, this->TB_CACountry->position.x, this->TB_CACountry->position.y - 18, 0, 59, 149, 16,false, this->m_game->ResourceManager->GetResource(1, 12, true));
	this->BT_CAEmail = new Button(this->m_game, this->TB_CAEmail->position.x, this->TB_CAEmail->position.y - 16, 0, 76, 149, 14,false, this->m_game->ResourceManager->GetResource(1, 12, true));
	this->BT_CACreate = new Button(this->m_game, 341, 422, 0, 0, 120, 39,false, this->m_game->ResourceManager->GetResource(1, 14, true));
	this->BT_CACancel = new Button(this->m_game, 341 + 119 + 6, 421, 0, 40, 120, 39,false, this->m_game->ResourceManager->GetResource(1, 14, true));

	this->CCModel = new CharacterModel();
	this->CCModel->InitializeModel(this->m_game);
	for(int i = 0; i < 3; i++)
	{
		
		this->CSModels[i].InitializeModel(this->m_game);
	}
	this->deletetrue = false;
	this->LastDeleteRequest = -1;
	

	//this->DebugModel[i] = new CharacterModel();
	//this->DebugModel.InitializeModel(this->m_game);

	//randomizeppdoll();
};

void Menu::TabPressed()
{
	if(this->m_game->Stage == Game::PLogin)
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
	else if(this->m_game->Stage == Game::PCharacterChoose && this->m_game->SubStage == 2)
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
	else if(this->m_game->Stage == Game::PCreateAccount)
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
	
	if(LastDeleteRequest > -1 && this->m_game->MsgID == 1)
	{
		SCharacter::DeletePlayer(this->m_game->world->connection->ClientStream,LastDeleteRequest,(LPVOID*)this);
		LastDeleteRequest = -1;
		this->m_game->MsgID = 0;
	}

	if(this->m_game->Stage == 0 || this->m_game->Stage == 1|| this->m_game->Stage == 3)
	{
			this->BT_CreateAccount->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
			this->BT_PlayGame->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
			this->BT_ViewCredits->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
			this->BT_ExitGame->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);

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
					this->m_game->world->RawPacketCount = 0;
					this->world->CreateConnection();
				}
				else
				{
					this->SelectID = 0;
					this->m_game->Stage = this->m_game->PCreateAccount;
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
				this->m_game->Stage = this->m_game->PLogin;
			}
			this->BT_PlayGame->Deactivate();
			}
			else if(this->BT_ViewCredits->MouseClickedOnElement())
			{
				this->m_game->Stage = this->m_game->PViewCredits;
				this->BT_ViewCredits->Deactivate();
			}
			else if(this->BT_ExitGame->MouseClickedOnElement())
			{
				this->m_game->Close();
			}
	}

	switch(this->m_game->Stage)
	{
	
	case(this->m_game->PMenu):
		{
		this->m_game->SubStage = 0;
			break;
		};
	case(this->m_game->PLogin):
		{
			if(world->GetFocusedTextbox() != this->TB_AccNme && world->GetFocusedTextbox() != this->TB_PassWrd)
			{
				world->SetFocusedTextbox(this->TB_AccNme);
			}
			this->BT_LGPlayGame->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
			if(BT_LGPlayGame->MouseClickedOnElement() && this->m_game->MousePressed)
			{
				Login();
			}
			this->BT_LGCancel->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
			if(this->TB_AccNme->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
			{
				if(this->m_game->MousePressed)
				{
					world->SetFocusedTextbox(this->TB_AccNme);
					this->TB_AccNme->focused = true;
					this->TB_PassWrd->focused = false;
				}
			}
			else if(this->TB_PassWrd->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
			{
				if(this->m_game->MousePressed)
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
		case(this->m_game->PViewCredits):
		{
			break;
		};
		case(this->m_game->PCreateAccount):
		{
			if(world->GetFocusedTextbox()->Phase != this->m_game->PCreateAccount)
			{ world->SetFocusedTextbox(this->TB_CAAccNme); }
			this->BT_CACreate->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
			this->BT_CACancel->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
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
			if(this->TB_CAAccNme->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
			{
				if(this->m_game->MousePressed)
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
			else if(this->TB_CAPassWrdOne->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
			{
				if(this->m_game->MousePressed)
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
			else if(this->TB_CAPassWrdTwo->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
			{
				if(this->m_game->MousePressed)
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
			else if(this->TB_CAName->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
			{
				if(this->m_game->MousePressed)
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
			else if(this->TB_CACountry->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
			{
				if(this->m_game->MousePressed)
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
			else if(this->TB_CAEmail->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
			{
				if(this->m_game->MousePressed)
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
		case(this->m_game->PCharacterChoose):
		{
			switch(this->m_game->SubStage)
			{
			case(0):
				{
					this->BT_LGChangePass->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					this->BT_LGCreateChar->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					BT_CC_Login1->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					BT_CC_Delete1->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					if (BT_CC_Login1->MouseClickedOnElement() && CSModels[0].name != "")
					{
						World::WorldCharacterID = CSModels[0].Game_ID;
						SWelcome::LoginCharacter(world->connection->ClientStream, CSModels[0].Game_ID, this->m_game);
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
							SCharacter::RequestDeletePlayer(world->connection->ClientStream,0, this->m_game);
							World::ThrowMessage("Delete character","Character '" + CSModels[0].name + "' is going to be \ndeleted. Are you sure?", true);
						}
						BT_CC_Delete1->Deactivate();
					}
					BT_CC_Login2->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					BT_CC_Delete2->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					if (BT_CC_Login2->MouseClickedOnElement() && CSModels[1].name != "")
					{
						World::WorldCharacterID = CSModels[1].Game_ID;
						SWelcome::LoginCharacter(world->connection->ClientStream, CSModels[1].Game_ID, this->m_game);
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
							SCharacter::RequestDeletePlayer(world->connection->ClientStream,1, this->m_game);
							World::ThrowMessage("Delete character","Character '" + CSModels[1].name + "' is going to be \ndeleted. Are you sure?", true);
						}
						BT_CC_Delete2->Deactivate();
					}
					BT_CC_Login3->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					BT_CC_Delete3->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					if (BT_CC_Login3->MouseClickedOnElement() && CSModels[2].name != "")
					{
						World::WorldCharacterID = CSModels[2].Game_ID;
						SWelcome::LoginCharacter(world->connection->ClientStream, CSModels[2].Game_ID, this->m_game);
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
							SCharacter::RequestDeletePlayer(world->connection->ClientStream,2, this->m_game);
							World::ThrowMessage("Delete character","Character '" + CSModels[2].name + "' is going to be \ndeleted. Are you sure?", true);
						}
						BT_CC_Delete3->Deactivate();
					}
					this->TB_AccNme->focused = false;
					this->TB_PassWrd->focused = false;
					this->TB_CreateChar->focused = true;
					if(this->BT_LGCreateChar->MouseClickedOnElement())
					{
						SCharacter::RequestCreatePlayer(this->world->connection->ClientStream, this->m_game);

							world->MassTextBoxReset();
							this->CCModel->SetCharacter(0,0,0,0,0);
							this->BT_CCP_Gender->SetFrameID(0);
							this->BT_CCP_HairCol->SetFrameID(0);
							this->BT_CCP_HairMod->SetFrameID(0);
							this->BT_CCP_SkinCol->SetFrameID(0);
							world->SetFocusedTextbox(this->TB_CreateChar);

							this->BT_LGCreateChar->Deactivate();
							this->BT_LGCreateChar->Update(0, 0, this->m_game->MousePressed);

						this->BT_LGCreateChar->Deactivate();
					}
					if(this->BT_LGChangePass->MouseClickedOnElement())
					{
						world->MassTextBoxReset();
						world->SetFocusedTextbox(this->TB_MyAccNme);


						this->m_game->SubStage = 2;
						this->BT_LGChangePass->Deactivate();
						this->BT_LGChangePass->SetFrameID(0);  
						//this->BT_LGChangePass->Update(0, 0, this->m_game->MousePressed);
					}
					break;
				}
			case(1):
				{
					world->SetFocusedTextbox(this->TB_CreateChar);
					CCModel->UpdateAppearence();
					this->BT_CreateCharCancel->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					this->BT_CreateCharOK->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					this->BT_CC_Gender->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					this->BT_CC_HairCol->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					this->BT_CC_HairMod->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					this->BT_CC_SkinCol->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					if(this->BT_CreateCharCancel->MouseClickedOnElement())
					{
						this->m_game->SubStage = 0;
						this->BT_CreateCharCancel->Deactivate();
					}
					if(this->BT_CreateCharOK->MouseClickedOnElement())
					{
						std::string Accname(this->TB_CreateChar->text);
						CCModel->name = Accname;
						SCharacter::CreatePlayer(this->world->connection->ClientStream, this->m_game);
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
					this->BT_ChangePassCancel->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					this->BT_ChangePassOK->Update(this->m_game->MouseX, this->m_game->MouseY, this->m_game->MousePressed);
					if(this->BT_ChangePassCancel->MouseClickedOnElement())
					{
						this->m_game->SubStage = 0;
						this->BT_ChangePassCancel->Deactivate();
					}
					if(this->BT_ChangePassOK->MouseClickedOnElement())
					{
						this->ChangePass();
						this->BT_ChangePassOK->Deactivate();
					}
					if(this->TB_MyAccNme->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
					{
						if(this->m_game->MousePressed)
						{
							world->SetFocusedTextbox(this->TB_MyAccNme);
							this->TB_MyAccNme->focused = true;
							this->TB_MyPass->focused = false;
							this->TB_MyNewPass1->focused = false;
							this->TB_MyNewPass2->focused = false;
						}
					}
					else if(this->TB_MyPass->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
					{
						if(this->m_game->MousePressed)
						{
							world->SetFocusedTextbox(this->TB_MyPass);
							this->TB_MyAccNme->focused = false;
							this->TB_MyPass->focused = true;
							this->TB_MyNewPass1->focused = false;
							this->TB_MyNewPass2->focused = false;
						}
					}
					else if(this->TB_MyNewPass1->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
					{
						if(this->m_game->MousePressed)
						{
							world->SetFocusedTextbox(this->TB_MyNewPass1);
							this->TB_MyAccNme->focused = false;
							this->TB_MyPass->focused = false;
							this->TB_MyNewPass1->focused = true;
							this->TB_MyNewPass2->focused = false;
						}
					}
					else if(this->TB_MyNewPass2->CheckCollision(this->m_game->MouseX, this->m_game->MouseY))
					{
						if(this->m_game->MousePressed)
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

void Menu::randomizeppdoll()
{
	int SkinCol = rand() % 6;
	int HatID = rand() % 60;
	int HairID = rand() % 20;
	int HairCol = rand() % 20;
	int ArmorID = rand() % 60;
	int ShoeID = rand() % 40;
	int WeaponID = rand() % 70;
	int ShieldID = rand() % 20;
	int Gender = 0;

		//this->DebugModel[i] = new CharacterModel();
		this->DebugModel.SetCharacter(Gender, HairID, HairCol, SkinCol, 0, ArmorID, WeaponID, ShoeID,ShieldID);
		this->DebugModel.UpdateAppearence();

}
void Menu::Render()
{
	this->m_game->Draw(1, BgID, false, 0, 0);
	//this->m_game->Draw(this->m_game->Map_UserInterface->map_ChatBubbleHandler->ChatBoxBG, 0, 0, sf::Color::Black, 0, 0, 640, 480, sf::Vector2f(1, 1), 0.00f);

	//int direction = 0;

	//if (m_game->MousePressed)
	//{
		//randomizeppdoll();
	//}
	//for (int i = 0; i < 44; i++)
	//{
		/*int tileposx = 24 + (64 * (i % 9));
		int tileposy = 90 + (80 * (i / 9));
		this->m_game->Draw(this->m_game->ResourceManager->GetResource(3, 296, true), tileposx, tileposy, sf::Color::White, 0, 0, 64, 32, sf::Vector2f(1.0, 1.0), 0);
		this->DebugModel.direction = i / 11;
		int playerx = 50 + (64 * (i % 9));
		int playery = 50 + (80 * (i / 9));
		this->DebugModel.Render(i % 11, playerx, playery, 0, sf::Color::White);*/
	//}


		switch(this->m_game->Stage)
		{
			case(this->m_game->PMenu):
				{
				this->m_game->Draw(1, FgID, true, 230, 470 - this->m_game->ResourceManager->GetResource(1, FgID, true)->_height);
				
					this->BT_CreateAccount->Draw();
					this->BT_PlayGame->Draw();
					this->BT_ViewCredits->Draw();
					this->BT_ExitGame->Draw();
					break;
				}
			case(this->m_game->PLogin):
				{
				this->m_game->Draw(1, 2, false, 240, 280);
				this->m_game->Draw(Txbox_Texture, this->TB_AccNme->position.x - 5, this->TB_AccNme->position.y + 1);
				this->m_game->Draw(Txbox_Texture, this->TB_PassWrd->position.x - 5, this->TB_PassWrd->position.y);
					
					this->BT_CreateAccount->Draw();
					this->BT_PlayGame->Draw();
					this->BT_ViewCredits->Draw();
					this->BT_ExitGame->Draw();

					this->BT_LGPlayGame->Draw();
					this->BT_LGCancel->Draw();

					break;
				}
			case(this->m_game->PViewCredits):
				{
					this->BT_CreateAccount->Draw();
					this->BT_PlayGame->Draw();
					this->BT_ViewCredits->Draw();
					this->BT_ExitGame->Draw();
					break;
				}
			case(this->m_game->PCreateAccount):
				{
				this->m_game->Draw(1, LoginFgID, true, 30, 470 - this->m_game->ResourceManager->GetResource(1, LoginFgID, true)->_height);
				this->m_game->Draw(Txbox_Texture, this->TB_CAAccNme->position.x - 5, this->TB_CAAccNme->position.y + 1, sf::Color::White, 0, 0, -1, -1, sf::Vector2f(2, 1));
				this->m_game->Draw(Txbox_Texture, this->TB_CAPassWrdOne->position.x - 5, this->TB_CAPassWrdOne->position.y + 1, sf::Color::White, 0, 0, -1, -1, sf::Vector2f(2, 1));
					this->m_game->Draw(Txbox_Texture, this->TB_CAPassWrdTwo->position.x - 5, this->TB_CAPassWrdTwo->position.y + 1, sf::Color::White, 0, 0, -1, -1, sf::Vector2f(2, 1));
					this->m_game->Draw(Txbox_Texture, this->TB_CAName->position.x - 5, this->TB_CAName->position.y + 1, sf::Color::White, 0, 0, -1, -1, sf::Vector2f(2, 1));
					this->m_game->Draw(Txbox_Texture, this->TB_CACountry->position.x - 5, this->TB_CACountry->position.y + 1, sf::Color::White, 0, 0, -1, -1, sf::Vector2f(2, 1));
					this->m_game->Draw(Txbox_Texture, this->TB_CAEmail->position.x - 5, this->TB_CAEmail->position.y + 1, sf::Color::White, 0, 0, -1, -1, sf::Vector2f(2, 1));

					this->BT_CAAccNme->Draw();
					this->BT_CAPassWrdOne->Draw();
					this->BT_CAPassWrdTwo->Draw();
					this->BT_CAName->Draw();
					this->BT_CACountry->Draw();
					this->BT_CAEmail->Draw();
					this->BT_CACreate->Draw();
					this->BT_CACancel->Draw();
					break;
				}
			case(this->m_game->PCharacterChoose):
				{
				this->m_game->Draw(1, LoginFgID, true, 30, 470 - this->m_game->ResourceManager->GetResource(1, LoginFgID, true)->_height);
				this->m_game->Draw(1, 11, false, 338, 40);
				this->m_game->Draw(1, 11, false, 338, 165);
				this->m_game->Draw(1, 11, false, 338, 289);
					
					BT_CC_Login1->Draw(0.05f);
					BT_CC_Delete1->Draw(0.05f);
					BT_CC_Login2->Draw(0.05f);
					BT_CC_Delete2->Draw(0.05f);
					BT_CC_Login3->Draw(0.05f);
					BT_CC_Delete3->Draw(0.05f);
					for(int i =0; i < this->m_game->AccountCharacterSize;i++)
					{
						this->CSModels[i].Render(400,80+(i*125), 0.1f);
					}			
					if(this->CSModels[0].admin >0)
					{
						BT_CS_Adminone->Draw(0.05f);
					}
					if(this->CSModels[1].admin >0)
					{
						BT_CS_Admintwo->Draw(0.05f);
					}
					if(this->CSModels[2].admin >0)
					{
						BT_CS_Adminthree->Draw(0.05f);
					}
					for(int i = 0; i < this->m_game->AccountCharacterSize;i++)
					{
						RECT rct;
						rct.left= 547;
						rct.right= rct.left + 200;
						rct.top= 68 + (i*125);
						rct.bottom= rct.top + 30;

						this->m_game->DrawTextW(CSModels[i].name.c_str(), rct.left, rct.top, sf::Color::Color(240, 240, 240, 185), 13, true);
						
						rct.left= 368;
						rct.right= rct.left + 108;
						rct.top= 137 + (i*125);
						rct.bottom= rct.top + 30;
						std::basic_string<char> str = "";
						char* st = new char[8];
						_itoa((BYTE)CSModels[i].level, st, 10);
						str += st;
						this->m_game->DrawTextW(str.c_str(), rct.left, rct.top, sf::Color::Color(240, 240, 240, 185),13,false);
					}
					
					switch(this->m_game->SubStage)
					{
					case(0):
						 {
							break;
						 }
					case(1):
						 {
							this->m_game->Draw(1, 20, false, 158, 129, sf::Color::White, 0, 0, -1, -1, sf::Vector2f(1, 1), 0.04f);
							this->BT_CreateCharCancel->Draw();
							this->BT_CreateCharOK->Draw();
							this->BT_CC_Gender->Draw();
							this->BT_CC_HairCol->Draw();
							this->BT_CC_HairMod->Draw();
							this->BT_CC_SkinCol->Draw();

							this->BT_CCP_Gender->Draw();
							this->BT_CCP_HairCol->Draw();
							this->BT_CCP_HairMod->Draw();
							this->BT_CCP_SkinCol->Draw();

							this->CCModel->Render(430,225,0.03f);
							break;
						 }
					case(2):
						{
							this->m_game->Draw(1, 21, false, 158, 129, sf::Color::White, 0, 0, -1, -1, sf::Vector2f(1, 1), 0.04f);
							this->BT_ChangePassCancel->Draw();
							this->BT_ChangePassOK->Draw();
						}
					}


					this->BT_LGCreateChar->Draw();
					this->BT_LGChangePass->Draw();
					break;
				}
		}
	
		this->world->RenderTextBoxes(this->m_game->Stage, this->m_game->SubStage);
		//this->Sprite->End();
};

void Menu::Release()
{
	this->BgTex._Texture.reset();
}

void Menu::Login()
{
	if (this->TB_AccNme->text == "" || this->TB_PassWrd->text == "")
       { }
       else
		{
			SLogin::SendLoginRequest(this->m_game,world->connection->ClientStream, this->TB_AccNme->text, this->TB_PassWrd->text);
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
	SAccount::RequestAccountCreate(world->connection->ClientStream,(this->TB_CAAccNme->text), this->m_game);
	//SAccount::RequestAccountCreate(world->connection->ClientStream,WCharToCharStr(this->TB_CAAccNme->text),WCharToCharStr(this->TB_CAPassWrdOne->text),WCharToCharStr(this->TB_CAPassWrdTwo->text),WCharToCharStr(this->TB_CAName->text),WCharToCharStr(this->TB_CACountry->text),WCharToCharStr(this->TB_CAEmail->text),this->m_game);

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
		/*char ch[260];
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
		std::string NewPass(ch);*/
	    SAccount::ChangePass(world->connection->ClientStream, this->TB_MyAccNme->text, this->TB_MyPass->text, this->TB_MyNewPass1->text, this->m_game);
	}
}

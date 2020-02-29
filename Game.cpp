#include "Game_Stage\Menu.h"
#include "Game_Stage\Map_UI\Map_UI_Cursor.h"
#include "Game_Stage\Map_UI\Map_UI.h"
#include "Game_Stage\Map.h"
#include "Utilities/ConfigFile.h"
#include "stdafx.h"
#include "Resource_Manager.h"

sf::Sprite* sprite;
std::shared_ptr<sf::Texture> texture;
bool Game::CancelTrue;
bool exitinggame;
//Tempory font grabbing addon.
bool GetFontData(const HFONT fontHandle, std::vector<char>& data)
{
	bool result = false;
	HDC hdc = ::CreateCompatibleDC(NULL);
	if (hdc != NULL)
	{
		::SelectObject(hdc, fontHandle);
		const size_t size = ::GetFontData(hdc, 0, 0, NULL, 0);
		if (size > 0)
		{
			char* buffer = new char[size];
			if (::GetFontData(hdc, 0, 0, buffer, size) == size)
			{
				data.resize(size);
				memcpy(&data[0], buffer, size);
				result = true;
			}
			delete[] buffer;
		}
		::DeleteDC(hdc);
	}
	return result;
}

//This class handles all game content and chooses when to activate certain events (Menu stages etc).
void Game::Initialize(sf::RenderWindow*m_Device, World* _World)
{
		this->world = _World;
		this->MouseX,this->MouseY = 0;
		this->Device = m_Device;
		//D3DXCreateSprite(Device, &sprite);
		this->FPS = 60;

		this->DefaultFont = new sf::Font();
		HINSTANCE hResInstance = (HINSTANCE)GetModuleHandle(NULL);
		HRSRC res = FindResource(hResInstance, MAKEINTRESOURCE(IDR_FONT1), RT_FONT);
		HGLOBAL Handle = LoadResource(NULL, res);
		size_t sizeoffont = SizeofResource(NULL, res);
		this->DefaultFont->loadFromMemory(Handle, sizeoffont);
		
		sf::Text* sftxt = new sf::Text();
		this->rendertext = std::shared_ptr<sf::Text>(sftxt);
		this->rendertext->setFont(*this->DefaultFont);

		this->ResourceManager = new Resource_Manager();
		this->ResourceManager->Initialize(Device);

		menu = new Menu();
		map = new Map();

		this->BT_Message_OK = new Button(this, MessageX + 180, MessageY + 112, 0, 116, 91, 28, false, this->ResourceManager->GetResource(1, 15, true));
		this->BT_ExitGame = new Button(this, 640 - 53, -1, -1, -1, 50, 53, true, this->ResourceManager->GetResource(2, 39, true));
		this->BT_CharDeleteOK = new Button(this, MessageX + 180 - 92, MessageY + 112, 0, 116, 91, 28, false, this->ResourceManager->GetResource(1, 15, true));
		this->BT_CharDeleteCancel = new Button(this, MessageX + 180, MessageY + 112, 0, 29, 91, 28, false, this->ResourceManager->GetResource(1, 15, true));
		Map_UserInterface = new Map_UI();
		menu->Initialize(world, Device, this);
		map->Initialize(world, Device, this);
		Map_UserInterface->Initialize(world, Device, this);


		
		this->MessageDragging = false;
		this->MessageSelected = false;
		this->MessageX = 190;
		this->MessageY = 150;
		this->Closed = false;
		this->Stage = Game::PMenu;
		this->SubStage = 0;
		this->CancelTrue = false;
		this->MsgID = 0;

		this->MapCursor = Map_UI_Cursor(this, this->map, Device);

		this->ENF_File = new ENF("pub\\dtn001.enf");
		this->EIF_File = new EIF("pub\\dat001.eif");
		this->ESF_File = new ESF("pub\\dsl001.esf");
		this->ECF_File = new ECF("pub\\dat001.ecf");

		this->world->W_UI_Infobox = new UI_InformationBox(this);	
		#ifndef DEBUG
		this->world->W_UI_Infobox->NewBox();
		this->world->W_UI_Infobox->CreateMessage("EODEV Version 0.8", "Welcome to EODev; Gantic's hobby project!");
		this->world->W_UI_Infobox->AddMessage("Be prepared for bugs - It's held together by scotch tape and zip ties in here!");
		this->world->W_UI_Infobox->AddMessage("If you don't believe me you can browse through\n the source code and cry yourself to sleep at \ngithub/GanticsAntics/Endless-Online-Development. \nCredits go to the original Endless Online \ndevelopers, and to Sausage & Sordie. \n\nFinally I'd like to thank the remaining EOCommunity who have faithfully stuck to endless after all these years. :)");
		//this->world->W_UI_Infobox->AddMessage("Welcome to my shop, this is a generic client-sided debug block of text to demonstrate the ability for text to exist with a shop.");
		//this->world->W_UI_Infobox->AddShopBuyItem(3, 131, 1091,34);
		this->world->W_UI_Infobox->SetLocation(256, 90);
		#endif
}	

void World::ThrowMessage(std::string Title, std::string Message)
{
	World::MBTitle = Title;
	World::MBMessage = Message;
	World::MBHidden = false;
}

void World::DebugPrint(pt::string Message)
{
#ifdef DEBUG
	std::printf(Message + '\n');
#endif
	
}
void World::ThrowMessage(std::string Title, std::string Message, bool Okay)
{
	World::MBTitle = Title;
	World::MBMessage = Message;
	World::MBHidden = false;
	Game::CancelTrue = Okay;
}
float timerrender;
std::chrono::time_point<std::chrono::high_resolution_clock> init, final;
void Game::Update()
{

	init = std::chrono::high_resolution_clock::now();
	if(!world->Connected && Stage != Game::PViewCredits)
	{
		Stage = Game::GameStage::PMenu;
	}
	if(World::MBHidden)
	{
		if (this->Stage < 5)
		{
			menu->Update();
			this->world->W_UI_Infobox->Update();
		}
		else
		{
			this->MapCursor.Update();
			//if (World::UIBox_Hidden)
			{
				map->Update();
			}
			this->world->W_UI_Infobox->Update();
			Map_UserInterface->Update();
		}

		if(this->Stage > 1)
		{ this->BT_ExitGame->Update(this->MouseX,this->MouseY,this->MousePressed); }
		
		if(this->BT_ExitGame->MouseClickedOnElement())
		{ 
			if(Stage == this->PViewCredits)
			{
				world->DropConnection();
				this->Stage = Game::PMenu;
				this->SubStage = 0;
				exitinggame = false;
				this->BT_ExitGame->MouseClickProccessed();
			}
			else
			{
				World::ThrowMessage("Return to menu","Are you sure you want to return to the \nmain menu?",true);
				exitinggame = true;
				this->BT_ExitGame->MouseClickProccessed();
			}

		}
	}
	else
	{
		menu->BT_CC_Delete1->SetFrameID(0);
		menu->BT_CC_Delete2->SetFrameID(0);
		menu->BT_CC_Delete3->SetFrameID(0);
		menu->BT_CC_Login1->SetFrameID(0);
		menu->BT_CC_Login2->SetFrameID(0);
		menu->BT_CC_Login3->SetFrameID(0);
		menu->BT_ChangePassCancel->SetFrameID(0);
		menu->BT_ChangePassOK->SetFrameID(0);
		menu->BT_CreateAccount->SetFrameID(0);
		menu->BT_CreateCharCancel->SetFrameID(0);
		menu->BT_CreateCharOK->SetFrameID(0);
		menu->BT_ExitGame->SetFrameID(0);
		menu->BT_LGCancel->SetFrameID(0);
		menu->BT_LGChangePass->SetFrameID(0);
		menu->BT_LGCreateChar->SetFrameID(0);
		menu->BT_LGPlayGame->SetFrameID(0);
		menu->BT_PlayGame->SetFrameID(0);
		menu->BT_ViewCredits->SetFrameID(0);
		if(!CancelTrue)
		{
			if (this->BT_Message_OK->GetFrameID() == 0 && this->MouseX > this->MessageX && this->MouseX < this->MessageX + 290 && this->MouseY > this->MessageY  && this->MouseY < this->MessageY  + 157)
			   {
				 if (this->RAWMousePressed)
					{
					   this->MessageSelected = true;
					}
			   }
		}
		else
		{
			if (this->BT_CharDeleteOK->GetFrameID() == 0  && this->BT_CharDeleteCancel->GetFrameID() == 0 && this->MouseX > this->MessageX && this->MouseX < this->MessageX + 290 && this->MouseY > this->MessageY  && this->MouseY < this->MessageY  + 157)
			   {
				 if (this->RAWMousePressed)
					{
					   this->MessageSelected = true;
					}
			   }
		}
        if (this->MessageSelected == true)
           {
             if (this->RAWMousePressed)
                {
                  if (this->MessageDragging == false)
                     {
                      DragX = this->MouseX - this->MessageX;
                      DragY = this->MouseY - this->MessageY ;
                      this->MessageDragging = true;
                     }
                  this->MessageX = this->MouseX - DragX;
                  this->MessageY  = this->MouseY - DragY;
                }
                else
                {
                 this->MessageDragging = false;
                 this->MessageSelected = false;
                }
           }
			this->BT_Message_OK->SetPosition(std::pair<int,int>(MessageX + 181,MessageY+ 113));
			this->BT_CharDeleteOK->SetPosition(std::pair<int, int>(MessageX + 180 - 92,MessageY+ 112));
			this->BT_CharDeleteCancel->SetPosition(std::pair<int, int>(MessageX + 181,MessageY+ 113));
			if(!this->MessageDragging)
			{
				if(!CancelTrue)
				{
					this->BT_Message_OK->Update(MouseX,MouseY,MousePressed);
					if(this->BT_Message_OK->MouseClickedOnElement())
					{
						World::MBHidden = true;
						this->BT_Message_OK->MouseClickProccessed();
					}
				}
				else
				{
					this->BT_CharDeleteOK->Update(MouseX,MouseY,MousePressed);
					this->BT_CharDeleteCancel->Update(MouseX,MouseY,MousePressed);
					if(this->BT_CharDeleteOK->MouseClickedOnElement())
					{
						if(exitinggame)
						{	
							this->Stage = Game::PMenu;
							exitinggame = false;
							world->DropConnection();
						}	
						MsgID = 1;	
						World::MBHidden = true;
						this->BT_CharDeleteOK->MouseClickProccessed();
						CancelTrue = false;
					}
					if(this->BT_CharDeleteCancel->MouseClickedOnElement())
					{
						MsgID = 0;
						World::MBHidden = true;
						this->BT_CharDeleteCancel->MouseClickProccessed();
						CancelTrue = false;
					}

				}

			}
	}
	this->MouseWheelVal = 0;
}
long timerrecorder;
std::string fpsstring;
int Game_FPSCounter = 0;
void Game::Render()
{
	this->map->FinalizeMapState();
	this->RenderList.clear();
	Game_FPSCounter++;
	Device->clear(sf::Color::Black);

	if (this->Stage <= 4)
	{
		this->menu->Render();
	}
	else
	{
		this->map->Render();
		Map_UserInterface->Render();
	
		//this->map->ThreadLock.lock();
		RECT rct;

		rct.left = 20;
		rct.right = 300;
		rct.top = 32;
		rct.bottom = 300;

		//this->map->Sprite->Begin(D3DXSPRITE_ALPHABLEND);
		//this->DefaultFont->DrawTextW(this->map->Sprite, this->MapCursor.cur_istring.c_str(), -1, &rct, DT_LEFT, sf::Color::Color(255, 255, 255, 255));
		//this->map->Sprite->End();
		//this->map->ThreadLock.unlock();
	}

	if (this->Stage > 1)
	{
		this->BT_ExitGame->Draw();
	}
	world->W_UI_Infobox->Draw(0.001f);
	if (!World::MBHidden)
	{
		this->Draw(this->ResourceManager->GetResource(1, 18, false), this->MessageX - 1, this->MessageY - 1, sf::Color::Color(255, 255, 255, 255), 0,0,-1,-1, sf::Vector2f(1,1),0);
		if (!this->CancelTrue)
		{
			this->BT_Message_OK->Draw();
		}
		else
		{
			this->BT_CharDeleteOK->Draw();
			this->BT_CharDeleteCancel->Draw();
		}
		RECT rct;
		rct.left = this->MessageX + 60;
		rct.right = rct.left + 270;
		rct.top = this->MessageY + 25;
		rct.bottom = rct.top + 30;
		this->DrawTextW(World::MBTitle.c_str(), rct.left, rct.top, sf::Color::Color(240, 240, 199, 255),  11, false, 0);
		rct.left = this->MessageX + 20;
		rct.right = rct.left + 270;
		rct.top = this->MessageY + 60;
		rct.bottom = rct.top + 130;
		this->DrawTextW(World::MBMessage.c_str(), rct.left, rct.top, sf::Color::Color(240, 240, 199,255), 11, false, 0);
	}


	timerrender = clock();
	if (timerrender - timerrecorder > 100)
	{
		fpsstring = to_string((int)FPS);
		fpsstring += " fps";

		timerrecorder = timerrender;
	}

	this->DrawTextW(fpsstring.c_str(), 33, 14, sf::Color(240, 240, 199, 255), 16, false,0,1);
	this->FinalizeRender();
	//this->menu->Render();
	Device->display();


	//Device->Present( NULL, NULL, NULL, NULL );
	final = std::chrono::high_resolution_clock::now();
	//if (final - init > 0)
	{//this->FPS =
		std::chrono::duration<double> diff = final - init;
		this->FPS = 1 / diff.count();
	}


	//World::DebugPrint(std::to_string(FPS).c_str());
}
void Game::Unload()
{
	//if(this->DefaultFont){this->DefaultFont->Release();}
	//this->DefaultFont = NULL;
	if(this->menu){this->menu->Release();}
	if(this->ResourceManager){this->ResourceManager->Release();}
	//this->ResourceManager = NULL;

	//if(sprite){sprite->Release();}
	//sprite = NULL;
	if(texture){texture.reset();}

	while(true)
	{
	}
}
void Game::ResetDevice()
{
		//D3DXCreateSprite(Device,&sprite);
}
void Game::Draw(Resource_Manager::TextureData* dat, int x, int y, sf::Color Color, int imgx, int imgy, int imgw, int  imgh, sf::Vector2f scale, float _Depth)
{
	RenderInfo newinfo = RenderInfo(dat, x, y, Color, imgx, imgy, imgw, imgh, scale);
	this->RenderList.insert(std::pair<float,RenderInfo>(_Depth, newinfo));
}

void Game::Draw(DWORD ModuleID, int GFXID, bool BlackIsTransparent, int x, int y, sf::Color Color, int imgx, int imgy, int imgw, int  imgh, sf::Vector2f scale, float _Depth)
{
	Resource_Manager::TextureData* _dat = this->ResourceManager->GetResource(ModuleID, GFXID, BlackIsTransparent);
	RenderInfo newinfo = RenderInfo(_dat, x, y, Color, imgx, imgy, imgw, imgh, scale);
	this->RenderList.insert(std::pair<float, RenderInfo>(_Depth, newinfo));
}
void Game::Draw(std::shared_ptr<sf::Sprite>* _RenderSprite, std::shared_ptr<sf::RenderTexture>*  Rendertex, int x, int y, sf::Color Color, int imgx, int imgy, int imgw, int  imgh, sf::Vector2f Scale, float Depth )
{
	RenderInfo newinfo = RenderInfo(_RenderSprite, Rendertex, x, y, Color, imgx, imgy, imgw, imgh, Scale);
	this->RenderList.insert(std::pair<float, RenderInfo>(Depth, newinfo));
}
void Game::DrawText(std::string str, int x, int y, sf::Color Color, int height, bool centered, float _Depth, int outlinethickness, int bottomx, int bottomy)
{
	RenderInfo newinfo = RenderInfo(str, x, y, Color, bottomx, bottomy, NULL, height, sf::Vector2f(1,1),centered, outlinethickness);
	this->RenderList.insert(std::pair<float, RenderInfo>(_Depth, newinfo));

}
sf::Vector2f Game::GetFontSize(std::string _Message, int fontsize)
{
	RenderTextLock.lock();
	this->rendertext->setString(_Message);
	this->rendertext->setScale(0.5, 0.5);
	this->rendertext->setCharacterSize(fontsize * 2);
	sf::Vector2f returnval = sf::Vector2f(this->rendertext->getGlobalBounds().width, this->rendertext->getGlobalBounds().height);
	RenderTextLock.unlock();
	return returnval;
}
void Game::FinalizeRender()
{
	for (auto const& entry : this->RenderList)
	{
		switch (entry.second.ResourceType)
		{
			case(RenderInfo::DrawType::Texture):
			{
				if (entry.second._TextureData != NULL)
				{
					int imgw = entry.second.imgw - entry.second.imgx;
					int imgh = entry.second.imgh - entry.second.imgy;
					entry.second._TextureData->_Sprite->setScale(entry.second.Scale);
					entry.second._TextureData->_Sprite->setPosition(entry.second.x + (entry.second.Scale.x == -1 ? ((imgw + imgh < 0) ? entry.second._TextureData->_width : imgw) : 0), entry.second.y + (entry.second.Scale.y == -1 ? ((imgw + imgh < 0) ? entry.second._TextureData->_height : imgh) : 0));
					if (imgw + imgh < 0)
					{
						entry.second._TextureData->_Sprite->setTextureRect(sf::IntRect(0, 0, entry.second._TextureData->_width, entry.second._TextureData->_height));
					}
					else
					{
						entry.second._TextureData->_Sprite->setTextureRect(sf::IntRect(entry.second.imgx, entry.second.imgy, imgw, imgh));
					}
					entry.second._TextureData->_Sprite->setColor(entry.second.Color);

					Device->draw(*entry.second._TextureData->_Sprite);
				}
				break;
			}
			case(RenderInfo::DrawType::Text):
			{
				this->RenderTextLock.lock();
				rendertext->setColor(entry.second.Color);
				rendertext->setString(entry.second._Message);
				rendertext->setOutlineThickness(entry.second.borderthickness);
				rendertext->setOutlineColor(sf::Color::Black);
				rendertext->setScale(0.5, 0.5);
				rendertext->setCharacterSize(entry.second.imgh * 2);
				if (entry.second.textcentered)
				{
					sf::FloatRect textRect = rendertext->getGlobalBounds();
					rendertext->setPosition(entry.second.x - (textRect.width / 2), entry.second.y);
				}
				else
				{
					rendertext->setPosition(entry.second.x, entry.second.y);
				}
				if (entry.second.imgx > 0 || entry.second.imgy > 0)
				{
					//rendertext->
				}
				Device->draw(*rendertext.get());
				this->RenderTextLock.unlock();
				break;
			}
			case(RenderInfo::DrawType::MergedTexture):
			{	
				sf::RenderTexture* txturhandle = entry.second.RenderTextureTarget->get();
				sf::Sprite* sptehndle = entry.second.RenderTargetSprite->get();
				
				if (txturhandle != nullptr)
				{
					int imgw = entry.second.imgw - entry.second.imgx;
					int imgh = entry.second.imgh - entry.second.imgy;
					int txturew = txturhandle->getSize().x;
					int txtureh = txturhandle->getSize().y;
					entry.second.RenderTargetSprite->get()->setScale(entry.second.Scale);
					entry.second.RenderTargetSprite->get()->setPosition(entry.second.x + (entry.second.Scale.x == -1 ? ((imgw + imgh < 0) ? txturew : imgw) : 0), entry.second.y);
					if (imgw + imgh < 0)
					{
						entry.second.RenderTargetSprite->get()->setTextureRect(sf::IntRect(0, 0, txturew, txtureh));
					}
					else
					{
						entry.second.RenderTargetSprite->get()->setTextureRect(sf::IntRect(entry.second.imgx, entry.second.imgy, imgw, imgh));
					}
					entry.second.RenderTargetSprite->get()->setColor(entry.second.Color);

					Device->draw(*entry.second.RenderTargetSprite->get());	
				}
				break;
			}
		}
	}
}
void Game::SetStage(GameStage _Stage)
{
	this->Stage = _Stage;
}

Game::~Game()
{
	this->Map_UserInterface->~Map_UI();
}

void Game::Close()
{
	Device->close();
}
#include "..\..\stdafx.h"
#include "Map_UI.h"
#include "..\..\game.h"
#include "..\..\Packet_Handler\Send\STalk.h"

Map_UI::Map_UI()
{
	sf::Vector2f Pos;
	Pos.x = 380;
	Pos.y = 313;

	sf::Vector2f Size;
	Size.x = 140;
	Size.y = 30;
}
CBitmapEx UI_Mask;

void Map_UI::UI_SendMessage()
{
	if (this->ChatTextbox->text != "")
	{
		std::string message = (this->ChatTextbox->text);
		if (message[0] == '~')
		{
			message.erase(0,1);
			STalk::SendGlobal(this->m_game->world->connection->ClientStream, message, this->m_game);
			this->ChatTextbox->Reset();
			std::string playername = this->m_game->map->m_Players[World::WorldCharacterID]->name;
			playername[0] = std::toupper(playername[0]);
			TextTools::AppendChat(TextTools::ChatIndex::Global, 420, 10, 4, playername, message, this->m_game);
			this->m_game->Map_UserInterface->map_talk->UI_ChatScrollbars[TextTools::ChatIndex::Global]->BottomLineIndex();
		}
		else
		{
			STalk::SendTalk(this->m_game->world->connection->ClientStream, message, this->m_game);
			this->ChatTextbox->Reset();
			std::string playername = this->m_game->map->m_Players[World::WorldCharacterID]->name;
			playername[0] = std::toupper(playername[0]);
			TextTools::AppendChat(TextTools::ChatIndex::Public, 420, 10, 0, playername, message, this->m_game,sf::Color::Black);
			this->m_game->Map_UserInterface->map_talk->UI_ChatScrollbars[0]->BottomLineIndex();
		}
	}
}
LPDIRECT3DTEXTURE9 TX_UI_Mask = NULL;
void Map_UI::Initialize(World* _world, sf::RenderWindow*m_Device, Game* p_game)
{
	this->m_game = p_game;
	PlayerSelect = new Map_UI_SelectPlayer(this, m_game);
	///D3DXIMAGE_INFO info = D3DXIMAGE_INFO();
	this->m_world = _world;
	this->m_Device = m_Device;
	//D3DXCreateSprite(this->m_Device, &this->Sprite);
	
	this->map_news = new Map_UI_News(this, m_game);
	this->map_inventory = new Map_UI_Inventory(this, m_game);
	this->map_characterstats = new Map_UI_CharacterStats(this, m_game);
	this->map_gamehelp = new Map_UI_GameHelp(this, m_game);
	this->map_gamesettings = new Map_UI_GameSettings(this, m_game);
	this->map_macro = new Map_UI_KeyboardMacros(this, m_game);
	this->map_mapUI = new Map_UI_Map(this, m_game);
	this->map_party = new Map_UI_Party(this, m_game);
	this->map_passiveskills = new Map_UI_PassiveSkills(this, m_game);
	this->map_skills = new Map_UI_Skills(this, m_game);
	this->map_talk = new Map_UI_Talk(this, m_game);
	this->map_whoisonline = new Map_UI_WhoIsOnline(this, m_game);
	this->map_ChatBubbleHandler = new Map_UI_ChatBubbleHandler(this, m_game);
	sf::Vector2f Pos;
	Pos.x = 107;
	Pos.y = 306;

	sf::Vector2f Size;
	Size.x = 275;
	Size.y = 30;
	Textbox m_ChatTextbox =  Textbox(this->m_game, Pos, Size, sf::Color(0, 0, 0, 255), this->m_game->MessageFont, Game::GameStage::PInGame, 0);
	m_ChatTextbox.blinkhidden = false;
	m_ChatTextbox.MaxLen = 100;
	m_ChatTextbox.nonAcceptedKeyEntered = true;
	m_ChatTextbox.acceptspace = true;
	m_ChatTextbox.acceptsReturn = true;
	m_ChatTextbox.SetKeyMask(Textbox::KeyType::None);
	this->ChatTextbox = this->m_game->world->RegisterTextBox(m_ChatTextbox);


	UI_Mask.Create(640, 480);
	UI_Mask.Clear(_RGB(100,0,0));
	UI_Mask.MakeTransparent(_RGB(100, 0, 0));
	for (int i = 0; i < UI_Mask.GetWidth(); i++)
	{
		for (int ii = 308; ii < UI_Mask.GetHeight(); ii++)
		{
			UI_Mask.SetPixel(i, ii, _RGB(1, 0, 0));
		}
	}
	for (int i = 0; i < 11; i++)
	{
		for (int ii = 0; ii < UI_Mask.GetHeight(); ii++)
		{
			UI_Mask.SetPixel(i, ii, _RGB(1, 0, 0));
			UI_Mask.SetPixel(i + 629, ii, _RGB(1, 0, 0));
		}
	}
	for (int i = 0; i < UI_Mask.GetWidth(); i++)
	{
		for (int ii = 0; ii < 9; ii++)
		{
			UI_Mask.SetPixel(i, ii, _RGB(1, 0, 0));
		}
	}
	for (int i = 49; i < 99; i++)
	{
		for (int ii = 0; ii < 11; ii++)
		{
			UI_Mask.SetPixel(i, ii, _RGB(1, 0, 0));
			UI_Mask.SetPixel(i + 494, ii, _RGB(1, 0, 0));
		}
	}
	
	DWORD dwBufferSize = UI_Mask.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
	
	LPBYTE buffer;
	buffer = (LPBYTE)malloc(dwBufferSize);
	
	UI_Mask.Save(buffer);
	sf::Image resimage;
	resimage.loadFromMemory(buffer, dwBufferSize);
	resimage.createMaskFromColor(sf::Color::Black);
	
	TxBG = new Resource_Manager::TextureData();
	TxBG->_Sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	TxBG->_Texture = std::shared_ptr<sf::Texture>(new sf::Texture());

	TxBG->_Texture->create(640, 480);
	TxBG->_Texture->loadFromImage(resimage);

	TxBG->_TextureID = 0;
	TxBG->_height = UI_Mask.GetHeight();
	TxBG->_width = UI_Mask.GetWidth();
	TxBG->_Sprite->setTexture(*TxBG->_Texture);
	
	free(buffer);

	HudStatsTexture = this->m_game->ResourceManager->CreateTexture(2, 58, true)._Texture;
}

void Map_UI::Update()
{
	this->m_game->map->ThreadLock.lock();
	this->MouseX = this->m_game->MouseX;
	this->MouseY = this->m_game->MouseY;
	this->FPS = this->m_game->FPS;
	this->MousePressed = this->m_game->MousePressed;
	this->MouseHeld = this->m_game->RAWMousePressed;
	this->map_news->Update();
	this->map_inventory->Update();
	this->map_characterstats->Update();
	this->map_gamehelp->Update();
	this->map_gamesettings->Update();
	this->map_macro->Update();
	this->map_mapUI->Update();
	this->map_party->Update();
	this->map_passiveskills->Update();
	this->map_skills->Update();
	this->map_talk->Update();
	this->map_whoisonline->Update();
	this->map_ChatBubbleHandler->Update();
	PlayerSelect->Update();
	if (this->isactive)
	{
		this->m_game->world->SetFocusedTextbox(this->ChatTextbox);
	}
	this->m_game->map->ThreadLock.unlock();
}

void Map_UI::Render()
{
	this->m_game->map->ThreadLock.lock();

	this->m_game->Draw(TxBG, 0, 0, sf::Color::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), 0.01f);
	this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 1, true), 0, 0, sf::Color::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), 0.01);
	//this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 1, true), 0, 0, sf::Color::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), 0.04);
	this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 21, true), 0, 0, sf::Color::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), 0.009);
	this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 20, true), 17, 309, sf::Color::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), 0.009);

	this->map_news->Render(0.008);
	this->map_inventory->Render(0.008);
	this->map_characterstats->Render(0.008);
	this->map_gamehelp->Render(0.008);
	this->map_gamesettings->Render(0.008);
	this->map_macro->Render(0.008);
	this->map_mapUI->Render(0.008);
	this->map_party->Render(0.008);
	this->map_passiveskills->Render(0.008);
	this->map_skills->Render(0.008);
	this->map_talk->Render(0.008);
	this->map_whoisonline->Render(0.008);
	this->map_ChatBubbleHandler->Render(0.008);
	PlayerSelect->Render(0.008);
	ChatTextbox->Render();
	
	DrawHUDStats();
	
	if (this->HelpMessageTitle != "")
	{
		time_t curtime = clock();
		if (curtime - this->HelpMessageTimer < 2000)
		{
			//sf::Color col = D3DCOLOR_XRGB(0, 0, 0);
			RECT BoxRect = { 0,0 ,0,0 };
			BoxRect.left = 70;
			BoxRect.top = 455;
			BoxRect.bottom = BoxRect.top + 30;
			BoxRect.right = BoxRect.left + 400;
			std::string drawmessage = this->HelpMessageTitle+ " " + this->HelpMessage;
			this->m_game->DrawText(drawmessage, BoxRect.left, BoxRect.top, sf::Color::White, 9, false, 0, 1);
		}
		else
		{
			this->HelpMessageTitle = "";
			this->HelpMessage != "";
		}
	}
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	
	//sf::Color col = D3DCOLOR_XRGB(0, 0, 0);
	RECT BoxRect = { 0,0 ,0,0 };
	BoxRect.left = 572;
	BoxRect.top = 454;
	BoxRect.bottom = BoxRect.top + 30;
	BoxRect.right = BoxRect.left + 400;

	std::ostringstream oss;
	oss << std::put_time(&tm, "%H-%M-%S");
	auto str = oss.str();

	//this->m_game->MessageFont->DrawTextA(this->Sprite, str.c_str(), -1, &BoxRect, NULL, col);
	//this->Sprite->End();

	this->m_game->map->ThreadLock.unlock();
}
void Map_UI::DrawHUDStats()
{
	RECT IconSrcRect;
	IconSrcRect.left = 0;
	IconSrcRect.top = 0;
	IconSrcRect.bottom = 14;
	IconSrcRect.right = 439;
	sf::Vector3f* IconPos = new sf::Vector3f(105,8, 0.1f);
	sf::Vector3f* IconCentre = new sf::Vector3f(0, 0, 0);
	this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color(255, 255, 255, 255), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), 0.02f);

	//this->Sprite->Draw(HudStatsTexture.get(), &IconSrcRect, IconCentre, IconPos, sf::Color::Color(255, 255, 255, 255));
	//this->m_game->map->ThreadLock.lock();
	float hp = (float)this->m_game->map->m_Players[World::WorldCharacterID]->hp;
	float maxhp = (float)this->m_game->map->m_Players[World::WorldCharacterID]->maxhp;
	IconSrcRect.left = 0;
	IconSrcRect.top = 14;
	IconSrcRect.bottom = IconSrcRect.top + 14;

	IconSrcRect.right = 25 + (hp / maxhp)*85;
	this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color(255, 255, 255, 255), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), 0.02f);

	float tp = (float)this->m_game->map->m_Players[World::WorldCharacterID]->tp;
	float maxtp = (float)this->m_game->map->m_Players[World::WorldCharacterID]->maxtp;
	IconSrcRect.left = 110;
	IconSrcRect.top = 14;
	IconSrcRect.bottom = IconSrcRect.top + 14;
	IconSrcRect.right = IconSrcRect.left  + 25 + (tp / maxtp) * 85;
	IconPos->x = IconSrcRect.left + 105;
	this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color(255, 255, 255, 255), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), 0.02f);
	

	float sp = 100;
	float maxsp = 100;
	IconSrcRect.left = 110*2;
	IconSrcRect.top = 14;
	IconSrcRect.bottom = IconSrcRect.top + 14;
	IconSrcRect.right = IconSrcRect.left + 25 + (sp / maxsp) * 85;
	IconPos->x = IconSrcRect.left + 105;
	this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color(255, 255, 255, 255), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), 0.02f);


	float exp = (float)this->m_game->map->m_Players[World::WorldCharacterID]->exp - (std::round(std::pow(double(this->m_game->map->m_Players[World::WorldCharacterID]->level + 0), 3.0) * 133.1));
	float exptnl = std::round(std::pow((this->m_game->map->m_Players[World::WorldCharacterID]->level + 1), 3.0) * 133.1)- std::round(std::pow((this->m_game->map->m_Players[World::WorldCharacterID]->level), 3.0) * 133.1);
	IconSrcRect.left = 110 * 3;
	IconSrcRect.top = 14;
	IconSrcRect.bottom = IconSrcRect.top + 14;
	IconSrcRect.right = IconSrcRect.left + 25 + (exp / exptnl) * 85;
	IconPos->x = IconSrcRect.left + 105;
	this->m_game->Draw(this->m_game->ResourceManager->GetResource(2, 58, true), IconPos->x, IconPos->y, sf::Color(255, 255, 255, 255), IconSrcRect.left, IconSrcRect.top, IconSrcRect.right, IconSrcRect.bottom, sf::Vector2f(1, 1), 0.02f);
	delete IconPos;
	delete IconCentre;
	//this->m_game->map->ThreadLock.unlock();
}

void Map_UI::DrawHelpMessage(std::string title, std::string Message)
{
	this->HelpMessageTimer = clock();
	this->HelpMessageTitle = "["+title+"]";
	this->HelpMessage = Message;
}
Map_UI::~Map_UI()
{

}

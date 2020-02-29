#pragma once
#include "Utilities/UI_Element.h"
#include "Game_Stage/Map_UI/Map_UI_Cursor.h"
#include "Game_Stage/Map_UI/Map_UI.h"
#include "Game_Stage/Menu.h"
class Game
{
private:
	std::shared_ptr<sf::Text> rendertext;
	std::mutex RenderTextLock;
	struct RenderInfo
	{
	public:
		Resource_Manager::TextureData* _TextureData;
		int x; 
		int y;
		sf::Color Color;
		int imgx = 0;
		int imgy = 0;
		int imgw = -1; 
		int  imgh = -1;
		sf::Vector2f Scale;
		float depth;
		bool textcentered = false;
		std::shared_ptr<sf::RenderTexture>* RenderTextureTarget;
		std::shared_ptr<sf::Sprite>* RenderTargetSprite;
		int borderthickness;
		
		enum DrawType
		{
			Texture = 0,
			Text,
			MergedTexture,
		};
		DrawType ResourceType;
		std::string _Message;
		
		RenderInfo(Resource_Manager::TextureData* dat, int _x, int _y, sf::Color _Color , int _imgx , int _imgy , int _imgw , int  _imgh , sf::Vector2f _Scale)
		{
			this->_TextureData = dat;
			this->x = _x;
			this->y = _y;
			this->Color = _Color;
			this->imgx = _imgx;
			this->imgy = _imgy;
			this->imgw = _imgw;
			this->imgh = _imgh;
			this->Scale = _Scale;
			this->ResourceType = DrawType::Texture;
		}			
		RenderInfo(std::string _message, int _x, int _y, sf::Color _Color , int _imgx , int _imgy , int _imgw , int  _imgh , sf::Vector2f _Scale, bool iscentered, int _borderthickness = 0)
		{
			this->_Message = _message;
			this->x = _x;
			this->y = _y;
			this->Color = _Color;
			this->imgx = _imgx;
			this->imgy = _imgy;
			this->imgw = _imgw;
			this->imgh = _imgh;
			this->Scale = _Scale;
			this->textcentered = iscentered;
			this->borderthickness = _borderthickness;
			this->ResourceType = DrawType::Text;
		}	
		RenderInfo(std::shared_ptr<sf::Sprite>* _RenderSprite, std::shared_ptr<sf::RenderTexture>*  _RenderTextureTarget, int _x, int _y, sf::Color _Color, int _imgx, int _imgy, int _imgw, int  _imgh, sf::Vector2f _Scale)
		{
			this->RenderTargetSprite = _RenderSprite;
			this->RenderTextureTarget = _RenderTextureTarget;
			this->x = _x;
			this->y = _y;
			this->Color = _Color;
			this->imgx = _imgx;
			this->imgy = _imgy;
			this->imgw = _imgw;
			this->imgh = _imgh;
			this->Scale = _Scale;
			
			this->ResourceType = DrawType::MergedTexture;
		}


	};
	std::multimap<float,RenderInfo, std::greater<float>> RenderList;
	void FinalizeRender();

public:
	sf::RenderWindow* Device;
	IniConfiguration* Config;
	enum GameStage
	{
		PMenu = 0,
		PLogin,
		PCreateAccount,
		PViewCredits,
		PCharacterChoose,
		PInGame,
	};
	Button* BT_CharDeleteOK;
	Button* BT_CharDeleteCancel;
	Map_UI* Map_UserInterface;
	static bool CancelTrue;
	int MsgID;
	Map_UI_Cursor MapCursor;
	ENF* ENF_File;
	ECF* ECF_File;
	ESF* ESF_File;
	EIF* EIF_File;

	int GameID;
	int PlayerID;
	int AccountCharacterSize;
	int MessageX;
	int MessageY;
	int DragX;
	int DragY;
	int MouseWheelVal = 0;
	Button* BT_Message_OK;
	bool MessageDragging;
	bool MessageSelected;
	unsigned char SendMulti;
	unsigned char RecvMulti;
	int SubStage;
	Resource_Manager::TextureData GLoginButtonTexture;
	Resource_Manager::TextureData ExitGameTxt;
	Resource_Manager::TextureData MessageBoxTexture;
	Resource_Manager::TextureData ScrollBarTexture;
	Resource_Manager::TextureData TextIconTexture;
	Button* BT_ExitGame;
	sf::Font* DefaultFont;
	sf::Font* MessageFont;
	double FPS;
	int Counter;
	World* world;
	GameStage Stage;
	Resource_Manager* ResourceManager;
	sf::Sprite RenderSprite;
	Menu* menu;
	Map* map;
	bool Closed;
	bool MouseRightPressed;
	bool MousePressed;
	bool RAWMousePressed;
	float  MouseX,MouseY;
	sf::Vector2f GetFontSize(std::string _Message, int fontsize = 14);

	void SetStage(GameStage stage);
	void Initialize(sf::RenderWindow*Device, World* _world);
	void Update();
	void Render();
	void Draw(DWORD ModuleID, int GFXID, bool BlackIsTransparent, int x, int y, sf::Color Color = sf::Color::Color::White, int imgx = 0, int imgy = 0, int imgw = -1, int  imgh = -1, sf::Vector2f Scale = sf::Vector2f(1,1), float Depth = 1);
	void Draw(Resource_Manager::TextureData* dat, int x, int y, sf::Color Color = sf::Color::Color::White, int imgx = 0, int imgy = 0, int imgw = -1, int  imgh = -1, sf::Vector2f Scale = sf::Vector2f(1, 1), float Depth = 1);
	void Draw(std::shared_ptr<sf::Sprite>* _RenderSprite, std::shared_ptr<sf::RenderTexture>* Rendertex, int x, int y, sf::Color Color = sf::Color::Color::White, int imgx = 0, int imgy = 0, int imgw = -1, int  imgh = -1, sf::Vector2f Scale = sf::Vector2f(1, 1), float Depth = 1);
	void ClearDrawOrder() { this->RenderList.clear(); }
	void Close();

	void DrawText(std::string str, int x, int y, sf::Color Color, int height = 14, bool centered = false, float Depth = 1.0f, int outlinethickness = 0, int bottomx = -1, int bottomy = -1);

	void Unload();
	~Game();
	void ResetDevice();
};

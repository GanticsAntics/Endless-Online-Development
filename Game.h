#ifndef Game_h
#define Game_h
#include "Game_Stage\Menu.h"
#include "Game_Stage\Map_UI\Map_UI_Cursor.h"
#include "Game_Stage\Map_UI\Map_UI.h"
#include "Game_Stage\Map.h"
class Map_UI;
class Game
{
	
public:

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
	Button* BT_Message_OK;
	bool MessageDragging;
	bool MessageSelected;
	byte SendMulti;
	byte RecvMulti;
	byte SubStage;
	std::shared_ptr<IDirect3DTexture9> GLoginButtonTexture;
	Resource_Manager::TextureData ExitGameTxt;
	Resource_Manager::TextureData MessageBoxTexture;
	Resource_Manager::TextureData ScrollBarTexture;
	Resource_Manager::TextureData TextIconTexture;
	Button* BT_ExitGame;
	ID3DXFont* DefaultFont;
	ID3DXFont* MessageFont;
	double FPS;
	int Counter;
	World* world;
	GameStage Stage;
	Resource_Manager* ResourceManager;
	Menu* menu;
	Map* map;
	bool Closed;
	bool MouseRightPressed;
	bool MousePressed;
	bool RAWMousePressed;
	float  MouseX,MouseY;

	void SetStage(GameStage stage);
	void Initialize(IDirect3DDevice9Ptr Device, World* _world);
	void Update();
	void Render();
	void Draw(ID3DXSprite* Sprite,std::shared_ptr<IDirect3DTexture9> Texture, int x, int y, int Imgw, int Imgh, float Angle, D3DXCOLOR Color);
	void Draw(ID3DXSprite* Sprite, std::shared_ptr<IDirect3DTexture9> Texture, int x, int y, D3DXCOLOR Color);
	void Draw(ID3DXSprite* Sprite, std::shared_ptr<IDirect3DTexture9> Texture, int x, int y, float depth, D3DXCOLOR Color);
	void Draw(ID3DXSprite* Sprite,IDirect3DTexture9* Texture, int x, int y, D3DXCOLOR Color);
	void DrawText(LPCWSTR str, int x, int y, D3DXCOLOR Color);
	void DrawText(LPCSTR str, int x, int y, D3DXCOLOR Color);

	void DrawText(ID3DXSprite* Sprite,LPCWSTR str, int x, int y, D3DXCOLOR Color);
	void DrawText(ID3DXSprite* Sprite,LPCSTR str, int x, int y, D3DXCOLOR Color);
	void Unload();
	~Game();
	void ResetDevice();
};
#endif //Game_h
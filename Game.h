#ifndef Game_h
#define Game_h
#include <time.h>
#include "Menu.h"
#include "UI_Cursor.h"
#include "include/EOServ/eodata.hpp"
#include "Map_UI.h"

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
	UI_Cursor MapCursor;
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
	Resource::TextureData ExitGameTxt;
	Resource::TextureData MessageBoxTexture;
	Resource::TextureData ScrollBarTexture;

	Button* BT_ExitGame;
	ID3DXFont* DefaultFont;
	ID3DXFont* MessageFont;
	double FPS;
	int Counter;
	World* world;
	GameStage Stage;
	Resource* resource;
	Menu* menu;
	Map* map;
	bool Closed;
	bool MousePressed;
	bool RAWMousePressed;
	float  MouseX,MouseY;

	void SetStage(GameStage stage);
	void Initialize(IDirect3DDevice9Ptr Device, World* _world);
	void Update();
	void Render();
	void Draw(ID3DXSprite* Sprite,boost::shared_ptr<IDirect3DTexture9> Texture, int x, int y, int Imgw, int Imgh, float Angle, D3DXCOLOR Color);
	void Draw(ID3DXSprite* Sprite, boost::shared_ptr<IDirect3DTexture9> Texture, int x, int y, D3DXCOLOR Color);
	void Draw(ID3DXSprite* Sprite, boost::shared_ptr<IDirect3DTexture9> Texture, int x, int y, float depth, D3DXCOLOR Color);
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
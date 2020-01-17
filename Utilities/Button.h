#include "..\stdafx.h"
#ifndef Button_h
#define Button_h
#include "..\Utilities\UI_Element.h"
class Button : public UI_Element
{
public:
	Button(VOID* m_game, int _X, int _Y, int _ImgX, int _ImgY, int _ImgWidth, int _ImgHeight, bool _ClipDown, std::shared_ptr<IDirect3DTexture9> _Texture);
	Button(VOID* m_game, int _X, int _Y, int _ImgWidth, int _ImgHeight, std::shared_ptr<IDirect3DTexture9> _Texture_1, std::shared_ptr<IDirect3DTexture9> _Texture_2);
	int ImgX,ImgY;

	void Update(int MouseX, int MouseY, bool MousePressed);
	void Draw(ID3DXSprite* _Sprite);
	void Deactivate();
	void Release();
};
#endif // Button_h